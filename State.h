/*
 * State.h
 *
 *  Created on: Mar 16, 2015
 *      Author: rdl8212
 */

#ifndef STATE_H_
#define STATE_H_

#include "common.h"

class Transistion;

//**********Prototype*************

class StateNode{
public:
	virtual void entry(){
	}
	virtual void exitState(){
	}
	virtual StateNode* accept(event e){
	}
};

//*********Concrete Instantiations******

class StoppedOpening : public StateNode{
public:
	void entry();
	void exitState();
	StateNode* accept(event e);
};

class Opening : public StateNode{
public:
	void entry();
	void exitState();
	StateNode* accept(event e);
};

class StoppedClosing : public StateNode{
public:
	void entry();
	void exitState();
	StateNode* accept(event e);
};

class Closing : public StateNode{
public:
	void entry();
	void exitState();
	StateNode* accept(event e);
};




#endif /* STATE_H_ */
