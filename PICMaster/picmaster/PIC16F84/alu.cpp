#include "RandomAccessMemory.cpp"
RandomAccessMemory ram;
using namespace std;
class ALU{
    public:
        int ADD(int num1, int num2){
            ram.setCarryFlag(false);
            ram.setDigitCarryFlag(false);
            ram.setCarryFlag(isCarry(num1,num2));
            ram.setDigitCarryFlag(isDigitCarry(num1,num2));
            int result = (num1 + num2) & 0xFF;
            ram.checkZero(result);
            return result;
        };
        int SUB(int num1, int num2){
            int comp2 = getTwoCompliment(num2);
            //cout << "sub: " << num1 << "," << num2 << "," << comp2 << endl;
            return ADD(num1,comp2);
        };
        int AND(int num1, int num2){
            return (num1 & num2);
        };
        int OR(int num1, int num2){
            return (num1 | num2);
        };
        int XOR(int num1, int num2){
            return (num1 ^ num2);
        };

        bool isCarry(int num1, int num2){
            return num1 + num2 > 0xFF;
        };
        bool isDigitCarry(int num1, int num2) {
            int carryCheck = (num1 & 0xF) + (num2 & 0xF);
            return carryCheck > 0xF;
        };
        int getCompliment(int value){
            return (~value & 0xFF);
        }
        int getTwoCompliment(int value){
            value = getCompliment(value);
            value += 1;
            value &= 0xFF;
            return value;
        }
};