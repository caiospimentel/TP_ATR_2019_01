#ifndef CUSTOMLIBRARIES_H_
#define CUSTOMLIBRARIES_H_


using namespace std;

#include <iostream>
#include <chrono>
#include <ctime>
#include <cmath>
#include <stdlib.h>
#include <math.h>


//definição da estrutura de dados do controlador
typedef struct {
    float kp;
    float ki;
    float kd;
    float integrator;
    float previous_error;
    float integrator_limit;
    float frequency;
} pid_ctrl_t;


void pid_init(pid_ctrl_t *pid); //inicialização do PID

void pid_set_gains(pid_ctrl_t *pid, float kp, float ki, float kd); //definição dos ganhos

void pid_get_gains(const pid_ctrl_t *pid, float *kp, float *ki, float *kd); //retorno dos ganhos

float pid_process(pid_ctrl_t *pid, float error); //função de execução do PID



// Declarações do método de integração

float dif(float qin, float h);

float rungeKutta(float x0, float y0, float x, float h);



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

