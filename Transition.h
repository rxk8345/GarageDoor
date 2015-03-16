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


class TranBPFromSO : public Transition{//Button Press from Stopped Closing State
public:
	bool checkAccept(event e);
	StateNode* accept();
};

class TranOCFFromO : public Transition{//Overcurrent Fault from Opening State
public:
	bool checkAccept(event e);
	StateNode* accept();
};

class TranFCFromO : public Transition{//Fully Closed from Opening
public:
	bool checkAccept(event e);
	StateNode* accept();
};

class TranBPFFromO : public Transition{//Button Press from Opening
public:
	bool checkAccept(event e);
	StateNode* accept();
};

class TranBPFFromSC : public Transition{//Button Press from Stopped Closing
public:
	bool checkAccept(event e);
	StateNode* accept();
};

class TranOCFFromC : public Transition{//Overcurrent Fault from Closing
public:
	bool checkAccept(event e);
	StateNode* accept();
};

class TranIRFFromC : public Transition{//IRFault from Closing
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
