/*
 * State.cc
 *
 *  Created on: Mar 12, 2015
 *      Author: rdl8212
 */

#include "Transition.h"
#include "State.h"
#include "common.h"
/*
class StateNode{
public:
	virtual void entry() = 0;
	virtual void exit() = 0;
	virtual StateNode* accept(event e) = 0;
	state is_in(){
		return currentState;
	}
protected:
	state currentState;
};*/
state StateNode::is_in(){
	return currentState;
}


/*class State1 : public StateNode{
public:*/
	State1::State1(){
		Tran1 tran;
		State1::tran = &tran;
	}
	void State1::entry(){
		std::cout << "Hello! Welcome to State One!" << std::endl;
	}
	void State1::exit(){
		std::cout << "Leaving State One!" << std::endl;
	}
	StateNode* State1::accept(event e){
		std::cout << "Checking for event" << std::endl;
		if(State1::tran->checkAccept(e)){
			exit();
			StateNode* returnTran = State1::tran->accept();
			return returnTran;
		}
		else{
			return this;
		}
	}
//};
