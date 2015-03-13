/*
 * State.h
 *
 *  Created on: Mar 12, 2015
 *      Author: rdl8212
 */

#ifndef STATE_H_
#define STATE_H_

#include "common.h"
//#include "Transition.h"

class StateNode{
public:
		void entry();
		void exit();
		StateNode* accept(event e);
		state is_in();
protected:
	state currentState;
};

class State1 : public StateNode{
public:
	State1();
	void entry();
	void exit();
	StateNode* accept(event e);
private:
	//Transition* transition;
};

#endif /* STATE_H_ */
