
#ifndef TIMER_H_
#define TIMER_H_

#include <iostream>
#include <chrono>
#include <ctime>


using namespace std::chrono;

// Declaraçoes da parte de temporização
class Timer{
    public:
    void start();
   
    
    void stop();
   
    
    double elapsedMilliseconds();
    
    
    double elapsedSeconds();
   
   
    private:
    std::chrono::time_point<std::chrono::system_clock> m_StartTime;
    std::chrono::time_point<std::chrono::system_clock> m_EndTime;
    bool                                               m_bRunning = false;
};



#endif