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

class TranBPFromSO : public Transition{//Button Press from Stopped Closing State
public:
	bool checkAccept(event e);
	StateNode* accept();
};

class TranOCFromO : public Transition{//Overcurrent Fault from Opening State
public:
	bool checkAccept(event e);
	StateNode* accept();
};

class TranFOFromO : public Transition{//Fully Opening from Opening
public:
	bool checkAccept(event e);
	StateNode* accept();
};

class TranBPFromO : public Transition{//Button Press from Opening
public:
	bool checkAccept(event e);
	StateNode* accept();
};

class TranBPFromSC : public Transition{//Button Press from Stopped Closing
public:
	bool checkAccept(event e);
	StateNode* accept();
};

class TranOCFromC : public Transition{//Overcurrent Fault from Closing
public:
	bool checkAccept(event e);
	StateNode* accept();
};

class TranIRFromC : public Transition{//IRFault from Closing
public:
	bool checkAccept(event e);
	StateNode* accept();
};

class TranBPFromC : public Transition{//Button Press from Closing
public:
	bool checkAccept(event e);
	StateNode* accept();
};
class TranFCFromC : public Transition{//Fully Closed from Closing
public:
	bool checkAccept(event e);
	StateNode* accept();
};

#endif /* TRANSITION_H_ */
