/*
 * Transition.h
 *
 *  Created on: Mar 16, 2015
 *      Author: rdl8212
 */

#ifndef TRANSITION_H_
#define TRANSITION_H_

#include "common.h"

class StateNode;

//***************Prototype Class************
class Transition{
public:
	virtual bool checkAccept(event e){
	}
	virtual StateNode* accept(){
	}
};

//***************Concrete Instantiations************

class DefaultTran : public Transition{
public:
	bool checkAccept(event e);
	StateNode* accept();
};

class Tran1 : public Transition{
public:
	bool checkAccept(event e);
	StateNode* accept();
};

#endif /* TRANSITION_H_ */
