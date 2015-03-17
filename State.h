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
	virtual state is_in(){
	}
};

//*********Concrete Instantiations******

class StoppedOpening : public StateNode{
public:
	void entry();
	void exitState();
	StateNode* accept(event e);
	state is_in(){
		return SO;
	}
};

class Opening : public StateNode{
public:
	void entry();
	void exitState();
	StateNode* accept(event e);
	state is_in(){
		return O;
	}
};

class StoppedClosing : public StateNode{
public:
	void entry();
	void exitState();
	StateNode* accept(event e);
	state is_in(){
		return SC;
	}
};

class Closing : public StateNode{
public:
	void entry();
	void exitState();
	StateNode* accept(event e);
	state is_in(){
		return C;
	}
};




#endif /* STATE_H_ */
