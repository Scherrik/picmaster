#include <iostream>
#include <stdlib.h>
#include "alu.cpp"
using namespace std;
extern int wRegister;
extern int interruptMemory;
extern bool interruptActive;

ALU Operation;

int get_7th_bit(int command){
    if((command & 0x80) == 0x80){
        return true;
    }else{
        return false;
    }
}

void addwf(int command) {
    int address = command & 0x7F;
    int literal = ram.getDataFromAddress(address);
    int result = Operation.ADD(wRegister,literal);
    if (get_7th_bit(command)){
        ram.setDataToAddress(address,result);
    }else{
        wRegister = result;
    }
}

void andwf(int command) {
    int address = command & 0x7F;
    int literal = ram.getDataFromAddress(address);
    int result = Operation.AND(wRegister,literal);
    if (get_7th_bit(command)){
        ram.setDataToAddress(address,result);
    }else{
        wRegister = result;
    }
    ram.checkZero(result);
}

void clrf(int command) {
    int address = command & 0x7F;
    ram.setDataToAddress(address,0);
    ram.setZeroBit(true);
}

void clrw(int command) {
    wRegister = 0;
    ram.setZeroBit(true);
}

void comf(int command) {
    int address = command & 0x7F;
    cout << "addr: "<< address << endl;
    int fReg = ram.getDataFromAddress(address);
    cout << "before comf" << fReg << endl;
    int result = Operation.getCompliment(fReg);
    if (get_7th_bit(command)){
        ram.setDataToAddress(address,result);
    }else{
        wRegister = result;
    }
    ram.checkZero(result);
}

void decf(int command) {
    int address = command & 0x7F;
    int fReg = ram.getDataFromAddress(address);
    int result = Operation.SUB(fReg,0b1);
    if (get_7th_bit(command)){
        ram.setDataToAddress(address,result);
    }else{
        wRegister = result;
    }
    ram.checkZero(result);
}

void decfsz(int command) {
    int address = command & 0x7F;
    int fReg = ram.getDataFromAddress(address);
    int result = Operation.SUB(fReg,0b1);
    if (get_7th_bit(command)){
        ram.setDataToAddress(address,result);
    }else{
        wRegister = result;
    }
    if (result == 0){
        ram.incrementPCL();
        ram.addTimerPS();
    }
}

void incf(int command) {
    int address = command & 0x7F;
    int fReg = ram.getDataFromAddress(address);
    int result = Operation.ADD(fReg,0b1);
    if (get_7th_bit(command)){
        ram.setDataToAddress(address,result);
    }else{
        wRegister = result;
    }
    ram.checkZero(result);
}

void incfsz(int command) {
    int address = command & 0x7F;
    int fReg = ram.getDataFromAddress(address);
    int result = Operation.ADD(fReg,0b1);
    if (get_7th_bit(command)){
        ram.setDataToAddress(address,result);
    }else{
        wRegister = result;
    }
    if (result == 0){
        ram.incrementPCL();
        ram.addTimerPS();
    }
}

void iorwf(int command) {
    int address = command & 0x7F;
    int fReg = ram.getDataFromAddress(address);
    int result = Operation.OR(fReg,wRegister);
    if (get_7th_bit(command)){
        ram.setDataToAddress(address,result);
    }else{
        wRegister = result;
    }
    ram.checkZero(result);
}

void movf(int command) {
    int address = command & 0x7F;
    int fReg = ram.getDataFromAddress(address);
    if (get_7th_bit(command)){
        ram.setDataToAddress(address,fReg);
    }else{
        wRegister = fReg;
    }
    ram.checkZero(fReg);
}

void movwf(int command) {
    int address = command & 0x7F;
    ram.setDataToAddress(address,wRegister);
}

void nop(int command) {
}

void rlf(int command) {
    int address = command & 0x7F;
    int fReg = ram.getDataFromAddress(address);
    int carryBit = (fReg & 0x80)>>7;
    fReg = (fReg << 1) + carryBit;
    fReg = fReg & 0xFF;
    ram.setDataToAddress(address,fReg);
     if(carryBit == 1){
        ram.setCarryFlag(true);
    }else{
        ram.setCarryFlag(false);
    }
}

void rrf(int command) {
    int address = command & 0x7F;
    int fReg = ram.getDataFromAddress(address);
    int carryBit = fReg & 0x1;
    fReg = (fReg >> 1) + (carryBit << 7);
    fReg = fReg & 0xFF;
    ram.setDataToAddress(address,fReg);
    if(carryBit == 1){
        ram.setCarryFlag(true);
    }else{
        ram.setCarryFlag(false);
    }
}

void subwf(int command) {
    int address = command & 0x7F;
    int fReg = ram.getDataFromAddress(address);
    int result = Operation.SUB(fReg,wRegister);
    if (get_7th_bit(command)){
        ram.setDataToAddress(address,result);
    }else{
        wRegister = result;
    }
}

void swapf(int command) {
    int address = command & 0x7F;
    int fReg = ram.getDataFromAddress(address);
    int lNibble = (fReg & 0xF)<<4;
    int hNibble = (fReg & 0xF0)>>4;
    int result = hNibble + lNibble;
    if (get_7th_bit(command)){
        ram.setDataToAddress(address,result);
    }else{
        wRegister = result;
    }
}

void xorwf(int command) {
    int address = command & 0x7F;
    int fReg = ram.getDataFromAddress(address);
    int result = Operation.XOR(wRegister,fReg);
    if (get_7th_bit(command)){
        ram.setDataToAddress(address,result);
    }else{
        wRegister = result;
    }
    ram.checkZero(result);
}

void bcf(int command) {
    int address = command & 0x7F;
    int fReg = ram.getDataFromAddress(address);
    int bitShift = (command & 0x380) >> 7;
    int result = fReg &~ (1<<bitShift);
    ram.setDataToAddress(address,result);
}

void bsf(int command) {
    int address = command & 0x7F;
    int fReg = ram.getDataFromAddress(address);
    int bitShift = (command & 0x380) >> 7;
    int result = fReg | (1<<bitShift);
    ram.setDataToAddress(address,result);
}

void btfsc(int command) {
    int address = command & 0x7F;
    int fReg = ram.getDataFromAddress(address);
    int bitShift = (command & 0x380) >> 7;
    int bit = (fReg & (1<<bitShift)) >> bitShift;
    if(bit != 0b1){
        ram.incrementPCL();
        ram.addTimerPS();
    };
}

void btfss(int command) {
    int address = command & 0x7F;
    int fReg = ram.getDataFromAddress(address);
    int bitShift = (command & 0x380) >> 7;
    int bit = (fReg & (1<<bitShift)) >> bitShift;
    if(bit == 0b1){
        ram.incrementPCL();
        ram.addTimerPS();
    };
}

void addlw(int command) {
    int literal = command & 0xFF;
    int result = Operation.ADD(wRegister,literal);
    wRegister = result;
}

void andlw(int command) {
    int literal = command & 0xFF;
    int result = Operation.AND(wRegister,literal);
    wRegister = result;
}

void call(int command) {
    int address = command & 0x7FF;
    ram.addTimerPS();
}

void clrwdt() {
}

void _goto(int command) {
    int address = command & 0x7FF;
    ram.setPCL(address-1);
    ram.addTimerPS();
}

void iorlw(int command) {
    int literal = command & 0xFF;
    int result = Operation.OR(literal,wRegister);
    cout << wRegister << ":" << literal << endl;
    wRegister = result;
    ram.checkZero(result);
}

void movlw(int command) {
    int literal = command & 0xFF;
    //cout << command << ":" << literal << endl;
    wRegister = literal;
}

void retfie(int command) {
    ram.addTimerPS();
    ram.setPCL(interruptMemory);
    ram.setGIE(true);
    interruptActive = false;
}

void retlw(int command) {
    ram.addTimerPS();
}

void _return() {
    ram.addTimerPS();
}

void sleep() {
}

void sublw(int command) {
    int literal = command & 0xFF;
    cout << wRegister << ":" << literal << endl;
    int result = Operation.SUB(literal,wRegister);
    wRegister = result;
}

void xorlw(int command) {
    int literal = command & 0xFF;
    int result = Operation.XOR(wRegister,literal);
    wRegister = result;
    ram.checkZero(result);
}
