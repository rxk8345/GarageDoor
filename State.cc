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
		StateNode* returnState;
		State1 state;
		returnState = &state;
		return returnState;
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
	StateNode* returnState;
	State2 state;
	returnState = &state;
	return returnState;
}

//***************StoppedOpening**************
void StoppedOpening::entry(){
	std::cout << "Entering State 2" << std::endl;
}

void StoppedOpening::exit(){
	std::cout << "Exiting State 2" << std::endl;
}

StateNode* StoppedOpening::accept(event e){
	std::cout << "Attempting to accept an event in State 2" << std::endl;
	StateNode* returnState;
	StoppedOpening state;
	returnState = &state;
	return returnState;
}


//***************Opening**************
void Opening::entry(){
	std::cout << "Entering State 2" << std::endl;
}

void Opening::exit(){
	std::cout << "Exiting State 2" << std::endl;
}

StateNode* Opening::accept(event e){
	std::cout << "Attempting to accept an event in State 2" << std::endl;
	StateNode* returnState;
	Opening state;
	returnState = &state;
	return returnState;
}

//***************StoppedClosing**************
void StoppedClosing::entry(){
	std::cout << "Entering State 2" << std::endl;
}

void StoppedClosing::exit(){
	std::cout << "Exiting State 2" << std::endl;
}

StateNode* StoppedClosing::accept(event e){
	std::cout << "Attempting to accept an event in State 2" << std::endl;
	StateNode* returnState;
	StoppedClosing state;
	returnState = &state;
	return returnState;
}

//***************Closing**************
void Closing::entry(){
	std::cout << "Entering State 2" << std::endl;
}

void Closing::exit(){
	std::cout << "Exiting State 2" << std::endl;
}

StateNode* Closing::accept(event e){
	std::cout << "Attempting to accept an event in State 2" << std::endl;
	StateNode* returnState;
	Closing state;
	returnState = &state;
	return returnState;
}
