#include "functions.cpp"
#include <iostream>
#include <stdlib.h>
using namespace std;

void get_function(int command) {
	switch (command) {
	case 0x63:sleep();break;
	case 0x8:_return();break;
	case 0x9:retfie();break;
    case 0x64:clrwdt();break;
    case 0x0: nop();break;
    case 0x100: clrw();break;
	default:break;
	}

	//3bit command
	int bit3 = command & 0x3800;

    switch (bit3){
        case 0x2800:_goto();break;
        case 0x2000:call();break;
        default:break;
    }

    //4bit command
    int bit4 = command & 0x3c00;

    switch (bit4){
        case 0x1000:bcf();break;
        case 0x1400:bsf();break;
        case 0x1800:btfsc();break;
        case 0x1c00:btfss();break;
        default:break;
    }

    //6bit command
    int bit6 = command & 0x3f00;

    switch (bit6){
        case 0x3a00:xorlw();break;
        case 0x3c00:sublw();break;
        case 0x3400:retlw();break;
        case 0x3000:movlw(bit6);break;
        case 0x3800:iorlw();break;
        case 0x3900:andlw();break;
        case 0x3e00:addlw();break;
        case 0x600:xorwf();break;
        case 0xe00:swapf();break;
        case 0x200:subwf();break;
        case 0xc00:rrf();break;
        case 0xd00:rlf();break;
        case 0x0:movwf();break;
        case 0x800:movf();break;
        case 0x400:iorwf();break;
        case 0xf00:incfsz();break;
        case 0xa00:incf();break;
        case 0xb00:decfsz();break;
        case 0x300:decf();break;
        case 0x900:comf();break;
        case 0x100:clrf();break;
        case 0x500:andwf();break;
        case 0x700:addwf();break;
        default:break;
    }
}