/*
 * State.cc
 *
 *  Created on: Mar 16, 2015
 *      Author: rdl8212
 */
#include "State.h"
#include "Transition.h"
#include "common.h"
#include<iostream>


//***************StoppedOpening**************
void StoppedOpening::entry(){
	std::cout << "Entering StoppedOpening" << std::endl;
}

void StoppedOpening::exitState(){
	std::cout << "Exiting StoppedOpening" << std::endl;
}

StateNode* StoppedOpening::accept(event e){
	//std::cout << "Attempting to accept an event in StoppedOpening" << std::endl;
	TranBPFromSO tran;
	if(tran.checkAccept(e)){
		StoppedOpening::exitState();
		return tran.accept();
	}
	else{
		StateNode* returnState;
		StoppedOpening state;
		returnState = &state;
		return returnState;
	}
}


//***************Opening**************
void Opening::entry(){
	std::cout << "Entering Opening" << std::endl;
}

void Opening::exitState(){
	std::cout << "Exiting Opening" << std::endl;
}

StateNode* Opening::accept(event e){
	//std::cout << "Attempting to accept an event in Opening" << std::endl;
	TranBPFromO tran;
	TranFOFromO tran2;
	TranOCFromO tran3;//If we had more than four transitions off of a state
	//we would make this into a list and loop through it, however, this is
	//fine and it compiles and it's simple, so shhhhhh
	if(tran.checkAccept(e)){
		Opening::exitState();
		return tran.accept();
	}
	else if(tran2.checkAccept(e)){
		Opening::exitState();
		return tran2.accept();
	}
	else if(tran3.checkAccept(e)){
		Opening::exitState();
		return tran3.accept();
	}
	else{
		StateNode* returnState;
		Opening state;
		returnState = &state;
		return returnState;
	}
}

//***************StoppedClosing**************
void StoppedClosing::entry(){
	std::cout << "Entering StoppedClosing" << std::endl;
}

void StoppedClosing::exitState(){
	std::cout << "Exiting StoppedClosing" << std::endl;
}

StateNode* StoppedClosing::accept(event e){
	//std::cout << "Attempting to accept an event in StoppedOpening" << std::endl;
	TranBPFromSC tran;
	if(tran.checkAccept(e)){
		StoppedClosing::exitState();
		return tran.accept();
	}
	else{
		StateNode* returnState;
		StoppedClosing state;
		returnState = &state;
		return returnState;
	}
}

//***************Closing**************
void Closing::entry(){
	std::cout << "Entering Closing" << std::endl;
}

void Closing::exitState(){
	std::cout << "Exiting Closing" << std::endl;
}

StateNode* Closing::accept(event e){
	TranIRFromC tran;
	TranFCFromC tran2;
	TranOCFromC tran3;
	TranBPFromC tran4;
	//If we had more than three transitions off of a state
	//we would make this into a list and loop through it, however, this is
	//fine and it compiles and it's simple, so shhhhhh
	if(tran.checkAccept(e)){
		Closing::exitState();
		return tran.accept();
	}
	else if(tran2.checkAccept(e)){
		Closing::exitState();
		return tran2.accept();
	}
	else if(tran3.checkAccept(e)){
		Closing::exitState();
		return tran3.accept();
	}
	else if(tran4.checkAccept(e)){
		Closing::exitState();
		return tran4.accept();
	}//unrolled loop
	else{
		StateNode* returnState;
		Closing state;
		returnState = &state;
		return returnState;
	}
}
