#include <iostream>
#include <chrono>
#include <ctime>
#include <cmath>
#include <stdlib.h>
#include <math.h>
#include "customLibraries.h"

using namespace std;



//Implementação do PID
void pid_init(pid_ctrl_t *pid)
{
    pid_set_gains(pid, 1., 0., 0.);
    pid->integrator = 0.;
    pid->previous_error = 0.;
    pid->integrator_limit = INFINITY;
    pid->frequency = 1.;
}

void pid_set_gains(pid_ctrl_t *pid, float kp, float ki, float kd)
{
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
}

void pid_get_gains(const pid_ctrl_t *pid, float *kp, float *ki, float *kd)
{
    *kp = pid->kp;
    *ki = pid->ki;
    *kd = pid->kd;
}



float pid_process(pid_ctrl_t *pid, float error)
{
    float output;
    pid->integrator += error;

    if (pid->integrator > pid->integrator_limit) {
        pid->integrator = pid->integrator_limit;
    } else if (pid->integrator < -pid->integrator_limit) {
        pid->integrator = -pid->integrator_limit;
    }

    output  = - pid->kp * error;
    output += - pid->ki * pid->integrator / pid->frequency;
    output += - pid->kd * (error - pid->previous_error) * pid->frequency;

    pid->previous_error = error;
    return output;
}




//Implementação do método de integração Runge Kutta

float dif(float qin, float h) 

{ 
    
    int R1 = 5;
    int R0 = 2;
    int H = 10;
    int Cv = 1;

    int a = (R1-R0)/H;

    return ( (-Cv * sqrt(h) ) / (M_PI * exp2(R0+a*h) ) ) + (qin / ( M_PI * exp2(R0+a*h) ) ) ; //equação dinâmica do reservatório





} 
  
//Para um dado qin ele retorna h

float rungeKutta(float x0, float y0, float x, float h) 
{ 
    
    int n = (int)((x - x0) / h); //calcula o número de passos dado o intervalo
  
    float k1, k2, k3, k4; 
  
    
    float y = y0; 
    for (int i=1; i<=n; i++) 
    { 
        //aplicação do método
        k1 = h*dif(x0, y); 
        k2 = h*dif(x0 + 0.5*h, y + 0.5*k1); 
        k3 = h*dif(x0 + 0.5*h, y + 0.5*k2); 
        k4 = h*dif(x0 + h, y + k3); 
  
        //Novo valor de H
        y = y + (1.0/6.0)*(k1 + 2*k2 + 2*k3 + k4);; 
  
        // Novo valor de qin
        x0 = x0 + h; 
    } 
  
    return y; 
} 



//Implementaçaõ do Timer


   
    void Timer::start()
    {
        m_StartTime = std::chrono::system_clock::now(); //Encontra o temoo atual e o coloca como início da contagem
        m_bRunning = true;
    }
    
    void Timer::stop()
    {
        m_EndTime = std::chrono::system_clock::now(); //Encontra o temoo atual e o coloca como fim da contagem
        m_bRunning = false;
    }
    
    double Timer::elapsedMilliseconds()
    {
        std::chrono::time_point<std::chrono::system_clock> endTime;
        
        if(m_bRunning)
        {
            endTime = std::chrono::system_clock::now();
        }
        else
        {
            endTime = m_EndTime;
        }
        
        return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count(); //calcula a diferença entre o início e o fim da contagem
    }
    
    double Timer::elapsedSeconds()
    {
        return elapsedMilliseconds() / 1000.0; //transforma o intervalo de tempo de milissegundos para segundos
    }

   

