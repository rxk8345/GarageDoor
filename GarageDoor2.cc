#include <cstdlib>
#include <cstdio>
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
#include "common.h"

//*****************Messaging Code
#define CHANNELNAME "frontdoor"

typedef struct _pulse msg_header_t;


typedef struct{
	msg_header_t hdr ;		// standard QNX header
	event triggeredEvent;
}Message;

//*****************End of Messaging Code

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


//*****************Polling Code

void* ClientThread(void* args){
	std::cout << "Client has started\n" << std::endl;
	Message sendingMessage;
	Message replyMessage;
	sendingMessage.hdr.type = 0 ;
	sendingMessage.hdr.subtype = 0 ;
	sendingMessage.triggeredEvent = BP;//This is where you send the event that you trigger
	int connectionID = name_open( CHANNELNAME, 0 ) ;
	sleep(1);

	char inChar;
	for(;;){
		std::cin >> inChar;
		switch(inChar){
		case 'r' :
			sendingMessage.triggeredEvent = BP;
			break;
		case 'm':
			sendingMessage.triggeredEvent = OC;
			break;
		case 'i':
			sendingMessage.triggeredEvent = IR;
			break;
		}

		MsgSend( connectionID, &sendingMessage, sizeof(sendingMessage), &replyMessage, sizeof(replyMessage) );
	}
}

//*****************End of Polling Code

//*****************Start of Door Timing Thread
void* DoorTimerThread(void* args){
	std::cout << "Hello from Door Timer" << std::endl;
	Message sendingMessage;
	Message replyMessage;
	sendingMessage.hdr.type = 0 ;
	sendingMessage.hdr.subtype = 0 ;
	sendingMessage.triggeredEvent = FC;//This is where you send the event that you trigger
	int connectionID = name_open( CHANNELNAME, 0 ) ;

	int relativePosition = 0;
	for(;;){
		sleep(1);
		if(skyWalker.is_in() == O){
			std::cout << "Opening" << std::endl;
			relativePosition++;
		}
		else if(skyWalker.is_in() == C){
			std::cout << "Closing" << std::endl;
			relativePosition--;
		}

		if(relativePosition == 10){
			sendingMessage.triggeredEvent = FO;
			MsgSend( connectionID, &sendingMessage, sizeof(sendingMessage), &replyMessage, sizeof(replyMessage) );
		}
		else if(relativePosition == 0){
			sendingMessage.triggeredEvent = FC;
			MsgSend( connectionID, &sendingMessage, sizeof(sendingMessage), &replyMessage, sizeof(replyMessage) );
		}


	}
}
//*****************End of Door Timing Thread



int main(int argc, char *argv[]) {//Compilers are stupid and why

	//**************Polling Thread
	pthread_t Client;
	Client = pthread_create(&Client, NULL, ClientThread, NULL);
	if (Client) {
		std::cerr << "Error - pthread_create returned error\n" << std::endl;
	}

	pthread_t doorTimer;
	doorTimer = pthread_create(&doorTimer, NULL, DoorTimerThread , NULL);
	if (doorTimer) {
		std::cerr << "Error - pthread_create returned error\n" << std::endl;
	}

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
				std::cout << "Demo Server is started\n" << std::endl;
			else
				std::cout << "Named Channel was not created\n" << std::endl;
	//***************Mailbox Main Loop

	std::cout << "Welcome to my Statemachine" << std::endl;

	skyWalker.defaultTran();//Stopped Opening

	/*
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
	//All Transitions
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

	std::cout << "Made it to the end" << std::endl;
	return EXIT_SUCCESS;
}
