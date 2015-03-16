/*
 * State.h
 *
 *  Created on: Mar 16, 2015
 *      Author: rdl8212
 */

#ifndef STATE_H_
#define STATE_H_

#include "common.h"

//**********Prototype*************

class StateNode{
public:
	virtual void entry(){
	}
	virtual void exit(){
	}
	virtual StateNode* accept(event e){
	}
};

//*********Concrete Instantiations******

class State1 : public StateNode{
public:
	void entry();
	void exit();
	StateNode* accept(event e);
};

class State2 : public StateNode{
public:
	void entry();
	void exit();
	StateNode* accept(event e);
};

#endif /* STATE_H_ */
