using namespace std;

class Timer{
    private:
        float timer = 0;
        bool flankUp;
    public:
        void addTimer(float value){
            this->timer += value;
        }
        void setTimer(float value){
            this->timer = value;
        }
        float getTimer(){
            return timer;
        }
        void setFlankUp(bool flankUp){
            this->flankUp = flankUp;
        }
};