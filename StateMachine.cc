#include <cstdlib>
#include <iostream>

#include "State.h"
#include "Transition.h"



class StateWalker{
public:
	StateNode *currentState;
	StateWalker(){
		currentState = defaultTransition.accept();
	}
	void accept(event e){
		currentState = currentState->accept(e);
	}

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
