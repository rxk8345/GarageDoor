/*
 * MotorController.cc
 *
 *  Created on: Mar 17, 2015
 *      Author: rdl8212
 */
#include<stdio.h>
#include "HAL.h"
#include "common.h"
//Port A as output
//Port B as input
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <unistd.h>

#include <hw/inout.h>     /* for in*() and out*() functions */
#include <sys/mman.h>     /* for mmap_device_io() */
#include <sys/iofunc.h>

#define DAQBASEADDR 0x280
#define DIOCR (0x28B)
#define PORTA (0x288)
#define PORTB (0x289)

#define DIRB 0b00000010 //Write 1 for input, 0 for output
#define DIRA 0b00010000


//#############################Output Mask
#define MOTORUP 	0b00000001//pin naught
#define MOTORDOWN 	0b00000100
#define IRON 		0b00010000
#define SIMRESET	0b00100000//pin three


//##############################Input Masks
#define FULLOPEN	0b00000001
#define FULLCLOSED	0b00000010
#define IRBROKEN	0b01000000
#define OVERCURRENT	0b00001000
#define BUTTON		0b00100000

uintptr_t portA;
uintptr_t portB;

void setUpHardware(){
	int privity_err;
	/* Give this thread root permissions to access the hardware */
	privity_err = ThreadCtl( _NTO_TCTL_IO, NULL );
	if ( privity_err == -1 )
	{
		fprintf( stderr, "can't get root permissions\n" );
	}
	uintptr_t controlPort = mmap_device_io(1, DIOCR);
	out8(controlPort, DIRA);//Set the direction of the Digital I/O

	//map the ports to pointers
	portA = mmap_device_io(1, PORTA);
	portB = mmap_device_io(1, PORTB);
	out8(portB, (0x00));
	sleep(1);
	out8(portB, SIMRESET);
	//out8(portB, (0x00));
	//set up interrupt handler


}

event lastEvent;

event pollInputs(){
	int input;
	//printf("Hello from pollInputs!\n");
	//for(int x = 0; x<9; x++){
		input = in8(portA);
		event returnEvent = NAE;
		if(input & BUTTON){
			returnEvent =  BP;
		}
		else if(input & OVERCURRENT){
			returnEvent = OC;
		}
		else if(input & IRBROKEN){
			returnEvent = IR;
		}
		else if(input & FULLCLOSED){
			returnEvent = FC;
		}
		else if(input & FULLOPEN){
			returnEvent = FO;
		}

		if(lastEvent != returnEvent){
			lastEvent = returnEvent;
			return returnEvent;
		}
		else{
			return NAE;
		}
	//}
	//return BP;
}

void motorUp(){
	int portb = in8(portB);
	portb |= MOTORUP;				//Turn on Motor Up
	portb = ~(MOTORDOWN) & portb;	//Turn off Motor Down
	out8(portB, portb);
	printf("Motor going up\n");
}
void motorDown(){
	int portb = in8(portB);
	portb |= MOTORDOWN;				//Turn on Motor Down
	portb = ~(MOTORUP) & portb;	//Turn off Motor Up
	out8(portB, portb);
	printf("Motor going down\n");
}
void motorStop(){
	int portb = in8(portB);
	portb = ~(MOTORUP) & portb;	//Turn off Motor Up
	portb = ~(MOTORDOWN) & portb;	//Turn off Motor Down
	out8(portB, portb);
	printf("Motor stopping\n");
}

void turnIROn(){
	int portb = in8(portB);
	portb |= IRON;	//Turn on IR
	out8(portB, portb);
	printf("IR on");
}

void turnIROff(){
	int portb = in8(portB);
	portb = ~(IRON) & portb;	//Turn off IR
	out8(portB, portb);
	printf("IR Off");
}
