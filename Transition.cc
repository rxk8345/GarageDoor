/*
 * Transition.cc
 *
 *  Created on: Mar 16, 2015
 *      Author: rdl8212
 */

#include "Transition.h"
#include "State.h"
#include "common.h"

class State1;


//*****************DefaultTran*******

bool DefaultTran::checkAccept(event e){
	return false;
}
StateNode* DefaultTran::accept(){
	StateNode* returnState;
	StoppedOpening state;//The initial state
	returnState = &state;

	//Action lists happen here

	returnState->entry();

	return returnState;
}


//****************TranBPFromSO*************
bool TranBPFromSO::checkAccept(event e){
	return e == BP;
}
StateNode* TranBPFromSO::accept(){
	StateNode* returnState;
	Opening state;//The initial state
	returnState = &state;

	//Action lists happen here

	returnState->entry();

	return returnState;
}



//****************TranOCFromO *************
bool TranOCFromO::checkAccept(event e){
	return e == OC;
}
StateNode* TranOCFromO::accept(){
	StateNode* returnState;
	StoppedOpening state;//The initial state
	returnState = &state;

	//Action lists happen here

	returnState->entry();

	return returnState;
}

//****************TranFOFromO *************
bool TranFOFromO::checkAccept(event e){
	return e == FO;
}
StateNode* TranFOFromO::accept(){
	StateNode* returnState;
	StoppedClosing state;//The initial state
	returnState = &state;

	//Action lists happen here

	returnState->entry();

	return returnState;
}

//****************TranBPFromO *************
bool TranBPFromO::checkAccept(event e){
	return e == BP;
}
StateNode* TranBPFromO::accept(){
	StateNode* returnState;
	StoppedClosing state;//The initial state
	returnState = &state;

	//Action lists happen here

	returnState->entry();

	return returnState;
}

//****************TranBPFromSC *************
bool TranBPFromSC::checkAccept(event e){
	return e == BP;
}
StateNode* TranBPFromSC::accept(){
	StateNode* returnState;
	Closing state;//The initial state
	returnState = &state;

	//Action lists happen here

	returnState->entry();

	return returnState;
}

//****************TranOCFromC *************
bool TranOCFromC::checkAccept(event e){
	return OC == e;
}
StateNode* TranOCFromC::accept(){
	StateNode* returnState;
	Opening state;//The initial state
	returnState = &state;

	//Action lists happen here

	returnState->entry();

	return returnState;
}

//****************TranIRFromC *************
bool TranIRFromC::checkAccept(event e){
	return IR == e;
}
StateNode* TranIRFromC::accept(){
	StateNode* returnState;
	Opening state;//The initial state
	returnState = &state;

	//Action lists happen here

	returnState->entry();

	return returnState;
}

//****************TranBPFromC *************
bool TranBPFromC::checkAccept(event e){
	return BP == e;
}
StateNode* TranBPFromC::accept(){
	StateNode* returnState;
	StoppedOpening state;//The initial state
	returnState = &state;

	//Action lists happen here

	returnState->entry();

	return returnState;
}

//****************TranFCFromC *************
bool TranFCFromC::checkAccept(event e){
	return FC == e;
}
StateNode* TranFCFromC::accept(){
	StateNode* returnState;
	StoppedOpening state;//The initial state
	returnState = &state;

	//Action lists happen here

	returnState->entry();

	return returnState;
}
