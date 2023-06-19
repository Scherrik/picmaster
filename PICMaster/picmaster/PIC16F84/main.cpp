#include "instruction_decoder.cpp"
#include "scanner.cpp"
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <list>
extern int inst[];
using namespace std;
using namespace System::Collections::Generic;

bool interruptActive = false;
int interruptMemory;
extern int interruptList;
int wRegister;
string arr[1000];
//extern List<int> breakpointLines;


bool checkForInterrupt(){
    bool wasInterrupt;
    if(ram.getGIE()==1 &&! interruptActive){
        if(ram.getT0IF()==1 && ram.getT0IE()==1){
            interruptMemory = ram.getPCL();
            ram.setPCL(4);
            interruptActive = true;
            wasInterrupt = true;
        }
    }
    if (wasInterrupt){
        cout << "Interrupt" << endl;
    }
    return wasInterrupt;
};

//bool checkForBreakpoint(int value){
//    return breakpointLines->contains(value);
//


int runtime(bool step){
    interpreter();
    while(ram.getPCL() <= sizeof(inst)){
        if(inst[ram.getPCL()] == 0x3FFF){
            break;
        }
        //if (checkForBreakpoint(ram.getPCL()) && !step) {
        //    break;
        //}
        checkForInterrupt();
        cout <<" prog_conter: " << ram.getPCL() << endl;
        cout << ram.getPCL() << " : " << arr[ram.getPCL()] << endl;
        get_function(inst[ram.getPCL()]);
        cout <<"W: " << std::hex << wRegister;
        cout <<",   wert1: " << std::hex << ram.memory[0xc][0];
        cout <<",   wert2: " << std::hex << ram.memory[0xd][0];
        cout <<",   fsr: " << std::hex << ram.memory[0x4][0];
        cout <<",   counter: " << std::hex << ram.memory[0x10][0];
        cout <<",   timer: " << std::hex << ram.memory[0x1][0];
        cout <<",   DC: " << ram.getDigitCarry();
        cout <<",   C: " << ram.getCarryFlag();
        cout <<",   Z: " << ram.getZeroBit() << endl;
        //cout <<"wert1: "<< ram.memory[0xc][0] <<"   " << ram.memory[0xc][1] << endl;
        //cout <<"wert2: "<< ram.memory[0xd][0] <<"   " << ram.memory[0xd][1] << endl;
        //cout <<"erg: "<< ram.memory[0xe][0] <<"   " << ram.memory[0xe][1] << endl;
        cout << "-----------------------------"<<endl;
        ram.incrementPCL();
        ram.addTimerPS();

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
};