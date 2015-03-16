/*
 * Transition.cc
 *
 *  Created on: Mar 12, 2015
 *      Author: rdl8212
 */

#include "State.h"
#include "Transition.h"
#include "common.h"
#include<iostream>

/*class Transition{
public:*/


	bool Transition::checkAccept(event e){
		return e == triggerEvent && guard();
	}
	//virtual StateNode* accept() = 0;

/*protected:
	event triggerEvent;*/
	bool Transition::guard(){
		return true;
	}
//};

/*class Tran1 : public Transition{
public:*/
	Tran1::Tran1(){
		Transition::triggerEvent = E;
	}
	StateNode* Tran1::accept(){
		std::cout << "accepting transistion" << std::endl;
		StateNode* returnState;
		State1 state;
		state.entry();
		returnState = &state;
		return returnState;
	}
//protected:
//};


/*class DefaultTran : public Transition{
public:*/
	DefaultTran::DefaultTran(){

	}
	bool DefaultTran::checkAccept(event e){
		return true;
	}
	StateNode* DefaultTran::accept(){
		StateNode* returnState;
		State1 state;
		state.entry();
		returnState = &state;
		return returnState;
	}
//};
