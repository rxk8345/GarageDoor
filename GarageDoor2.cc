#include <cstdlib>
#include <cstdio>
#include<stdio.h>
#include <iostream>


#include <unistd.h>
#include <pthread.h>
#include <sys/iofunc.h>			// used by name_open()
#include <sys/dispatch.h>		// used by name_open()
#include <assert.h>
#include <sys/syspage.h>
#include <sys/time.h>
#include <time.h>
#include <fcntl.h>
#include <semaphore.h>
#include <errno.h>			// defines EOK


#include "State.h"
#include "Transition.h"
#include "HAL.h"
#include "common.h"

//*****************Messaging Code
//Defines some things for the messaging system
#define CHANNELNAME "frontdoor"
typedef struct _pulse msg_header_t;
typedef struct{
	msg_header_t hdr ;
	event triggeredEvent;
}Message;

//*****************State Walker Class Definition
class StateWalker{
public:
	StateNode *currentState;
	void defaultTran(){
		currentState = defaultTransition.accept();
	}
	void accept(event e){
		currentState = currentState->accept(e);//ask the current state to accept this event
	}
	state is_in(){
		return currentState->is_in();
	}

protected:
	DefaultTran defaultTransition;
};

StateWalker skyWalker;


//*****************Polling Thread
//The polling thread listens for input type events and sends them to the state machine controller thread(main)
void* PollingThread(void* args){
	//Seting up the channel to send events to
	std::cout << "Polling Thread has started\n" << std::endl;
	Message sendingMessage;
	Message replyMessage;
	sendingMessage.hdr.type = 0 ;
	sendingMessage.hdr.subtype = 0 ;
	sendingMessage.triggeredEvent = BP;
	int connectionID = name_open( CHANNELNAME, 0 ) ;
	sleep(1);//ensure that the server channel has been created before we continue

	for(;;){
		sendingMessage.triggeredEvent = pollInputs();

		if(sendingMessage.triggeredEvent != NAE){
			MsgSend( connectionID, &sendingMessage, sizeof(sendingMessage), &replyMessage, sizeof(replyMessage) );
		}
		//send the message to the State Machine Controller
		usleep(10000);
	}
	return 0;
}

/*****************Door Timing Thread
 * this thread checks the state of the state machine and handles generating the Fully Open and
 * Fully closed events at appropriate times. If the door has been closing for 3 seconds, and it
 * it is switched to the opening state, it will take 3 seconds for the Fully Open State to be
 * generated. The relative position of the door is how this is calculated.
 *
 * Every second, this thread polls the state machine for the current state. If the state is opening,
 * it will increase the count of the relativePosition, if it is closing it will decrease it. When
 * the count is either 0 or 10, the thread will send a Fully Closed or Fully Open event
 */
void* DoorTimerThread(void* args){
	std::cout << "Door Timer Thread has Started" << std::endl;
	Message sendingMessage;
	Message replyMessage;
	sendingMessage.hdr.type = 0 ;
	sendingMessage.hdr.subtype = 0 ;
	sendingMessage.triggeredEvent = FC;//This is where you send the event that you trigger
	int connectionID = name_open( CHANNELNAME, 0 ) ;

	int relativePosition = 0;
	for(;;){
		sleep(1);
		if(skyWalker.is_in() == O){//If the state machine is in the opening state
			relativePosition++;
		}
		else if(skyWalker.is_in() == C){//If the state machine is in the closing state
			relativePosition--;
		}

		if(relativePosition == 10){//If the relative position is all the way to the top
			sendingMessage.triggeredEvent = FO;
			MsgSend( connectionID, &sendingMessage, sizeof(sendingMessage), &replyMessage, sizeof(replyMessage) );
		}
		else if(relativePosition == 0){//If the relative position is all the way to the bottom
			sendingMessage.triggeredEvent = FC;
			MsgSend( connectionID, &sendingMessage, sizeof(sendingMessage), &replyMessage, sizeof(replyMessage) );
		}


	}
	return 0;
}

int main(int argc, char *argv[]) {
	setUpHardware();

	//**************Create Polling Thread
	pthread_t Polling;
	Polling = pthread_create(&Polling, NULL, PollingThread, NULL);
	if (Polling) {
		std::cerr << "Error - pthread_create returned error\n" << std::endl;
	}

	//*************Create Door Timer Thread
	//pthread_t doorTimer;
	//doorTimer = pthread_create(&doorTimer, NULL, DoorTimerThread , NULL);
	//if (doorTimer) {
	//	std::cerr << "Error - pthread_create returned error\n" << std::endl;
	//}

	//**************Mailbox Code
	name_attach_t *channel_id;
	int receiveID;
	Message recievedMessage;
	Message replyMessage;
	replyMessage.hdr.type = 0 ;
	replyMessage.hdr.subtype = 0 ;
	replyMessage.triggeredEvent = BP;

	channel_id = name_attach( NULL, CHANNELNAME, 0 );

	if ( channel_id )
				std::cout << "Event Server is started\n" << std::endl;
			else
				std::cout << "Event Server was not created\n" << std::endl;
	//***************Mailbox Main Loop

	std::cout << "System Initialized" << std::endl;

	skyWalker.defaultTran();//Stopped Opening

	for(;;){
			receiveID = MsgReceive(channel_id->chid, &recievedMessage, sizeof(recievedMessage), NULL);
		    if (recievedMessage.hdr.type == _IO_CONNECT){
		    	MsgReply(receiveID, EOK, NULL, 0);
		    }
		    else{
		    	MsgReply(receiveID, EOK, &replyMessage, sizeof(replyMessage));
		    	skyWalker.accept(recievedMessage.triggeredEvent);
		    }
	}
	/*
	 *
	 * "Unit" Testing
	 *
	 * Try all ignored events
		skyWalker.accept(IR);
		skyWalker.accept(OC);
		skyWalker.accept(FO);
		skyWalker.accept(FC);

		skyWalker.accept(BP);//Opening
		skyWalker.accept(IR);
		skyWalker.accept(FC);

		skyWalker.accept(BP);//Stopped Closing
		skyWalker.accept(IR);
		skyWalker.accept(FC);
		skyWalker.accept(FO);
		skyWalker.accept(OC);

		skyWalker.accept(BP);//Closing
		skyWalker.accept(FO);

		skyWalker.accept(BP);//Stopped Opening

		//So for some reason when we put a print statement in here and
		//had all of this uncommented, it segfaulted in skyWalker.accept(),
		//but without the print it didn't and we are not sure why


		//Try All Transitions
							 //SO
		skyWalker.accept(BP);//O
		skyWalker.accept(OC);//SO
		skyWalker.accept(BP);//O
		skyWalker.accept(FO);//SC
		skyWalker.accept(BP);//C
		skyWalker.accept(OC);//O
		skyWalker.accept(BP);//SC
		skyWalker.accept(BP);//C
		skyWalker.accept(IR);//O
		skyWalker.accept(BP);//SC
		skyWalker.accept(BP);//C
		skyWalker.accept(FC);//SO
		skyWalker.accept(BP);//O
		skyWalker.accept(BP);//SC
		skyWalker.accept(BP);//C
		skyWalker.accept(BP);//SO
		*/

//	std::cout << "Made it to the end" << std::endl;
	return EXIT_SUCCESS;
}
