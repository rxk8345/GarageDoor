#include <cstdlib>
#include <iostream>

typedef enum {E, B, C} event;
typedef enum {STATE1, STATE2} state;

class StateNode;
	class State1;
class Transition;
	class Tran1;
	class DefaultTransition;

class Transition{
public:
	bool checkAccept(event e){
		return e == triggerEvent && guard();
	}
	virtual StateNode* accept() = 0;

protected:
	event triggerEvent;
	bool guard(){

	}
};

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
};

class Tran1 : public Transition{
public:
	Tran1(){
		Transition::triggerEvent = E;
	}
	StateNode* accept(){
		StateNode* returnState;
		State1 state;
		returnState = &state;
		return returnState;
	}
protected:
};




class State1 : public StateNode{
public:
	void entry(){
		std::cout << "Hello! Welcome to State One!" << std::endl;
	}
	void exit(){
		std::cout << "Leaving State One!" << std::endl;
	}
	StateNode* accept(event e){
		if(transition.checkAccept(e)){
			exit();
			return transition.accept();
		}

	}
protected:
	Tran1 transition;

};

class DefaultTran : public Transition{
public:
	DefaultTran(){

	}
	bool checkAccept(event e){
		return true;
	}
	StateNode* accept(){
		StateNode* returnState;
		State1 state;
		state.entry();
		returnState = &state;
		return returnState;
	}
};


class StateWalker{
public:
	StateWalker(){
		currentState = defaultTransition.accept();
	}
	void accept(event e){
		currentState = currentState->accept(e);
	}
	StateNode *currentState;
protected:
	DefaultTran defaultTransition;
};

int main(int argc, char *argv[]) {
	std::cout << "Welcome to my statemachine" << std::endl;
	StateWalker skyWalker;
	
	skyWalker.accept(E);
	

	//for(;;){

	//}
	return EXIT_SUCCESS;
}