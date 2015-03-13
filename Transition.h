/*
 * Transition.h
 *
 *  Created on: Mar 12, 2015
 *      Author: rdl8212
 */



#ifndef TRANSITION_H_
#define TRANSITION_H_

#include "common.h"
#include "State.h"

class Transition{
public:
	bool checkAccept(event e);
	StateNode* accept();

protected:
	event triggerEvent;
	bool guard();
};

class Tran1 : public Transition{
public:
	Tran1();
	bool checkAccept(event e);
	StateNode* accept();

protected:
	bool guard();
};

class DefaultTran : public Transition{
public:
	DefaultTran();
	bool checkAccept(event e);
	StateNode* accept();

protected:
	bool guard();
};

#endif /* TRANSITION_H_ */
