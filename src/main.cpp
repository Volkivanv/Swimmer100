#include <iostream>
#include <string>
#include <thread>
#include <ctime>
#include <chrono>
#include <vector>

class Swimmer{
    double distance = 100;
    std::string name;
    double speed;
    double swimTime;
    std::thread mThread;
public:
    void setName(std::string inName){
        name = inName;
    }
    std::string getName(){
        return name;
    }
    void setSpeed(double inSpeed){
        speed = inSpeed;
    }
    double getSpeed(){
        return speed;
    }
    double getSwimTime(){
        return swimTime;
    }

    Swimmer(std::string inName, double inSpeed):name(inName),speed(inSpeed){


    }
    ~Swimmer(){
        if(mThread.joinable()) mThread.join();
        std::cout << name << " finished with time "<< swimTime <<std::endl;
    }

    void run(){
        mThread = std::thread(&Swimmer::swimmingInfo,this);
    }
    void finish(){
        mThread = std::thread(&Swimmer::swimmingInfo,this);
    }

    void swimmingInfo(){
        std::time_t beginTime = std::time(nullptr);
        std::time_t realTime;
        do{
            std::this_thread::sleep_for(std::chrono::seconds(1));
            realTime = std::time(nullptr);
            if((realTime - beginTime)*speed <= distance) {
                std::cout << "swimmer " << name << " swam " << (realTime - beginTime) * speed << std::endl;
            }
        }while(speed*(realTime - beginTime) <= distance);

        swimTime = distance/speed;
        std::cout << name << " finished with time "<< swimTime <<std::endl;

    }
};



int main() {
    std::vector<Swimmer*> swimmers(6);


    for(int i = 0; i < swimmers.size(); i++) {
        std::cout << "input name and speed of swimmer" << std::endl;
        std::string inName;
        double inSpeed;
        std::cin >> inName >> inSpeed;
        swimmers[i] = new Swimmer(inName, inSpeed);
    }

    for(int i = 0; i < swimmers.size(); i++){
        swimmers[i]->run();
    }





   // for(int i = 0; i < swimmers.size(); i++){
   //     std::cout << swimmers[i]->getName() << " finished with time " << swimmers[i]->getSwimTime()<<
   //     " seconds " <<std::endl;
   // }


    for(int i = 0; i < swimmers.size(); i++){
        delete swimmers[i];
    }


    return 0;
}
