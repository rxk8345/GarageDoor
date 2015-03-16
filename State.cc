/*
 * State.cc
 *
 *  Created on: Mar 16, 2015
 *      Author: rdl8212
 */
#include "State.h"
#include "Transition.h"
#include<iostream>

//**************State1***************
void State1::entry(){
	std::cout << "Entering State 1" << std::endl;
}

void State1::exit(){
	std::cout << "Exiting State 1" << std::endl;
}

StateNode* State1::accept(event e){
	Tran1 tran;
	if(tran.checkAccept(e)){
		this->exit();
		return tran.accept();
	}
	else{
		State1 newMe;
		return &newMe;
	}

}


//***************State2**************
void State2::entry(){
	std::cout << "Entering State 2" << std::endl;
}

void State2::exit(){
	std::cout << "Exiting State 2" << std::endl;
}

StateNode* State2::accept(event e){
	std::cout << "Attempting to accept an event in State 2" << std::endl;
	return (StateNode*) 0;
}
