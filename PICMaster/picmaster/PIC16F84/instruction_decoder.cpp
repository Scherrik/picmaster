#include "functions.cpp"
#include <iostream>
#include <stdlib.h>
using namespace std;
extern string arr[];

void get_function(int command) {
	switch (command) {
	case 0x63:sleep();arr[ram.getPCL()]="sleep";break;
	case 0x8:_return();arr[ram.getPCL()]="return";break;
	case 0x9:retfie(command);arr[ram.getPCL()]="retfie";break;
    case 0x64:clrwdt();arr[ram.getPCL()]="clrwdt";break;
    case 0x0: nop(command);arr[ram.getPCL()]="nop";break;
    case 0x100: clrw(command);arr[ram.getPCL()]="clrw";break;
	default:break;
	}

	//3bit command
	int bit3 = command & 0x3800;

    switch (bit3){
        case 0x2800:_goto(command);arr[ram.getPCL()]="goto";break;
        case 0x2000:call(command);arr[ram.getPCL()]="call";break;
        default:break;
    }

    //4bit command
    int bit4 = command & 0x3c00;

    switch (bit4){
        case 0x1000:bcf(command);arr[ram.getPCL()]="bcf";break;
        case 0x1400:bsf(command);arr[ram.getPCL()]="bsf";break;
        case 0x1800:btfsc(command);arr[ram.getPCL()]="btfsc";break;
        case 0x1c00:btfss(command);arr[ram.getPCL()]="btfss";break;
        default:break;
    }

    //6bit command
    int bit6 = command & 0x3f00;

    switch (bit6){
        case 0x3a00:xorlw(command);arr[ram.getPCL()]="xorlw";break;
        case 0x3c00:sublw(command);arr[ram.getPCL()]="sublw";break;
        case 0x3400:retlw(command);arr[ram.getPCL()]="retlw";break;
        case 0x3000:movlw(command);arr[ram.getPCL()]="movlw";break;
        case 0x3800:iorlw(command);arr[ram.getPCL()]="iorlw";break;
        case 0x3900:andlw(command);arr[ram.getPCL()]="andlw";break;
        case 0x3e00:addlw(command);arr[ram.getPCL()]="addlw";break;
        case 0x600:xorwf(command);arr[ram.getPCL()]="xorwf";break;
        case 0xe00:swapf(command);arr[ram.getPCL()]="swapf";break;
        case 0x200:subwf(command);arr[ram.getPCL()]="subwf";break;
        case 0xc00:rrf(command);arr[ram.getPCL()]="rrf";break;
        case 0xd00:rlf(command);arr[ram.getPCL()]="rlf";break;
        case 0x0:if(get_7th_bit(command)){
                    movwf(command);arr[ram.getPCL()]="movwf";
                }break;
        case 0x800:movf(command);arr[ram.getPCL()]="movf";break;
        case 0x400:iorwf(command);arr[ram.getPCL()]="iorwf";break;
        case 0xf00:incfsz(command);arr[ram.getPCL()]="incfsz";break;
        case 0xa00:incf(command);arr[ram.getPCL()]="incf";break;
        case 0xb00:decfsz(command);arr[ram.getPCL()]="decfsz";break;
        case 0x300:decf(command);arr[ram.getPCL()]="decf";break;
        case 0x900:comf(command);arr[ram.getPCL()]="comf";break;
        case 0x100:if(get_7th_bit(command)){
                        clrf(command);arr[ram.getPCL()]="clrf";
                    }break;
        case 0x500:andwf(command);arr[ram.getPCL()]="andwf";break;
        case 0x700:addwf(command);arr[ram.getPCL()]="addwf";break;
        default:break;
    }
}