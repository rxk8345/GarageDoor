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
	return true;
}
StateNode* DefaultTran::accept(){

	StateNode* returnState;
	State1 state;
	returnState = &state;

	returnState->entry();

	return returnState;
}


//****************Tran1*************

bool Tran1::checkAccept(event e){
	return e == E;
}
StateNode* Tran1::accept(){
	StateNode* returnState;
	State2 state;
	returnState = &state;

	returnState->entry();

	return returnState;
}
