#include "timer.cpp"
#include <math.h>
using namespace std;

class RandomAccessMemory{
    public:
        Timer timer;
        int memory[128][2];
        int getDataFromAddress(int address){
            int data = memory[address][getCurrentBank()];
            cout << "GET Address: " << hex << address << "   Data: " << data << "   From: " << getCurrentBank()<< endl;
            return data;
        };
        void setDataToAddress(int address, int data){
            switch (address)
            {
            case 0:
                setIndirekt(data);
                break;
            case 1:
                if (getCurrentBank()==0){
                    changeTMR0(data);
                }else{
                    setOption(data);
                }break;
            case 3:
                setStatus(data);
                break;
            case 4:
                setFSR(data);
                break;
            case 0xb:
                setIntcon(data);
                break;
            default:
                std::cout << "SET Address: " << std::hex << address << "   Data: " << data << "   From: " << getCurrentBank()<< endl;
                memory[address][getCurrentBank()] = data;
                break;
            }
        };
        int getStatus(){
            return memory[3][0];
        };
        void setStatus(int value){
            memory[3][0] = value;
            memory[3][1] = value;
        };

        int getPCL(){
            return getDataFromAddress(2);
        }
        void setPCL(int value){
            memory[2][0] = value;
            memory[2][1] = value;
        }
        void incrementPCL(){
            memory[2][0] = memory[2][0] + 1;
            memory[2][1] = memory[2][1] + 1;
        }

        int getCurrentBank(){
            int currentBank = 0;
            switch (getStatus() & 0b01100000){
            case 0b00000000:
                currentBank = 0;
                break;
            case 0b00100000:
                currentBank = 1;
                break;
            case 0b01000000:
                currentBank = 2;
                break;
            case 0b01100000:
                currentBank = 3;
                break;
            }
            return currentBank;
        };

        void setIndirekt(int value){
            int fsr = getFSR();
            if (fsr == 0){
                this->memory[0][0] = value;
                this->memory[0][1] = value;
            }else{
                setDataToAddress(fsr,value);
            }
        }


        void setCarryFlag(bool isCarry){
            int status = getStatus() & 0b11111110;
            if (isCarry){
                status |= 0b00000001;
            }
            setStatus(status);
        };
        int getCarryFlag(){
            int carry = getStatus() & 0b00000001;
            return carry;
        }

        void setDigitCarryFlag(bool isDigitCarry){
            int status = getStatus() & 0b11111101;
            if(isDigitCarry){
                status |= 0b00000010;
            }
            setStatus(status);
        };
        int getDigitCarry(){
            int digitCarry = getStatus() & 0b00000010;
            return digitCarry>>1;
        }
        void setZeroBit(bool isZero){
            int status = getStatus() & 0b11111011;
            if(isZero){
                status |= 0b00000100;
            }
            setStatus(status);
        }
        int getZeroBit(){
            int zeroBit = getStatus() & 0b00000100;
            return zeroBit>>2;
        }
        void checkZero(int value){
            if(value == 0){
                this->setZeroBit(true);
            }else{
                this->setZeroBit(false);
            }
        }
        int getPowerDownFlag(){
            return ((getStatus() & 0b00001000)>>3);
        }
        void setPowerDownFlag(bool isPDF){
            int status = getStatus() & 0b11110111;
            if(isPDF){
                status |= 0b00001000;
            }
        }
        int getTimeOutFlag(){
            return ((getStatus() & 0b00010000)>>3);
        }
        void setTimeOutFlag(bool isTOF){
            int status = getStatus() & 0b11101111;
            if(isTOF){
                status |= 0b00010000;
            }
        }

        int getPortA(){
            return this->memory[5][0];
        }
        void setPortA(int value){
            this->memory[5][0] = value;
        }

        int getTrisA(){
            return this->memory[5][1];
        }
        void setTrisA(int value){
            this->memory[5][1] = value;
        }

        int getPortB(){
            return this->memory[6][0];
        }
        void setPortB(int value){
            this->memory[6][0] = value;
        }

        int getTrisB(){
            return this->memory[6][1];
        }
        void setTrisB(int value){
            this->memory[6][1] = value;
        }

        int getFSR(){
            return getDataFromAddress(4);
        }
        void setFSR(int value){
            this->memory[4][0] = value;
            this->memory[4][1] = value;
        }
        
        int getIntcon(){
            return getDataFromAddress(11);
        }
        void setIntcon(int value){
            this->memory[11][0] = value;
            this->memory[11][1] = value;
        }

        void changeTMR0(int value){
            timer.setTimer(value);
            setTMR0(value);
        }
        void addTimer(float value){
            timer.addTimer(value);
            setTMR0(timer.getTimer());
        }
        
        void setTMR0(int value){
            this->memory[1][0] = value;
            if (value > 0xFF){
                this->memory[1][0] = 0;
                setT0IF();
            }
        }

        int getT0IF(){
            return (getIntcon() & 0b100)>>2;
        }
        void setT0IF(){
            setIntcon(getIntcon() | 0b100);
        }

        int getOption(){
            return this->memory[1][1];
        }
        void setOption(int value){
            this->memory[1][1] = value;
        }

        int getTimerPreScaler(int value){
            int prescaler = getOption() & 0x7;
            prescaler = pow(2,(prescaler + 1));
            return prescaler;
        } 
        void addTimerPS(){
            addTimer(1.0/getTimerPreScaler(getOption()));
        }

        int getGIE(){
            return (getIntcon() & 0b10000000)>>7;
        }
        void setGIE(bool value){
            setIntcon(getIntcon() | 0b10000000);
        }

        int getT0IE(){
            return (getIntcon() & 0b100000)>>5;
        }
};
