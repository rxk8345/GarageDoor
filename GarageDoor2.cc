#include <cstdlib>
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

name_attach_t *channel_id;
typedef struct{
	msg_header_t hdr ;		// standard QNX header
	event triggeredEvent;
}Message;

//*****************End of Messaging Code

//*****************Polling Code

void* ClientThread(void* args){
	std::cout << "Client has started\n" << std::endl;
	Message sendingMessage;
	Message replyMessage;
	sendingMessage.hdr.type = 0 ;
	sendingMessage.hdr.subtype = 0 ;
	sendingMessage.triggeredEvent = E;//This is where you send the event that you trigger
	int connectionID = name_open( CHANNELNAME, 0 ) ;
	sleep(1);
	for(;;){
		MsgSend( connectionID, &sendingMessage, sizeof(sendingMessage), &replyMessage, sizeof(replyMessage) );
		usleep(500000);
	}
}


//*****************End of Polling Code

class StateWalker{
public:
	StateNode *currentState;
	StateWalker(){
		currentState = defaultTransition.accept();
	}
	void accept(event e){
		currentState = currentState->accept(e);//ask the current state to accept this event
	}

protected:
	DefaultTran defaultTransition;
};

int main(int argc, char *argv[]) {

	//**************Polling Thread
	pthread_t Client;
	Client = pthread_create(&Client, NULL, ClientThread, NULL);
	if (Client) {
		std::cerr << "Error - pthread_create returned error\n" << std::endl;
	}

	//**************Mailbox Code
	int receiveID;
	Message recievedMessage;
	Message replyMessage;
	long value;
	replyMessage.hdr.type = 0 ;
	replyMessage.hdr.subtype = 0 ;
	replyMessage.triggeredEvent = E;

	channel_id = name_attach( NULL, CHANNELNAME, 0 );

	if ( channel_id )
				std::cout << "Demo Server is started\n" << std::endl;
			else
				std::cout << "Named Channel was not created\n" << std::endl;
	//***************Mailbox Main Loop

	std::cout << "Welcome to my Statemachine" << std::endl;
	StateWalker skyWalker;
	skyWalker.accept(E);

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
	return EXIT_SUCCESS;
}
