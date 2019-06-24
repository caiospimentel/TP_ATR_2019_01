#include <iostream>
#include <chrono>
#include <ctime>
#include <cmath>
#include <stdlib.h>
#include <math.h>
#include "customLibraries.h"

using namespace std;




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

float pid_get_integral_limit(const pid_ctrl_t *pid)
{
    return pid->integrator_limit;
}

float pid_get_integral(const pid_ctrl_t *pid)
{
    return pid->integrator;
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

void pid_set_integral_limit(pid_ctrl_t *pid, float max)
{
    pid->integrator_limit = max;
}

void pid_reset_integral(pid_ctrl_t *pid)
{
    pid->integrator = 0.;
}

void pid_set_frequency(pid_ctrl_t *pid, float frequency)
{
    pid->frequency = frequency;
}

float pid_get_frequency(const pid_ctrl_t *pid)
{
    return pid->frequency;
}



float dydx(float qin, float h) 

{ 
    
    int R1 = 5;
    int R0 = 2;
    int H = 10;
    int Cv = 1;

    int a = (R1-R0)/H;

    return ( (-Cv * sqrt(h) ) / (M_PI * exp2(R0+a*h) ) ) + (qin / ( M_PI * exp2(R0+a*h) ) ) ; //equação dinâmica do reservatório





} 
  
// Finds value of y for a given x using step size h -- para dado qin ele retorna h
// and initial value y0 at x0. 
float rungeKutta(float x0, float y0, float x, float h) 
{ 
    // Count number of iterations using step size or 
    // step height h 
    int n = (int)((x - x0) / h); 
  
    float k1, k2, k3, k4, k5; 
  
    // Iterate for number of iterations 
    float y = y0; 
    for (int i=1; i<=n; i++) 
    { 
        // Apply Runge Kutta Formulas to find 
        // next value of y 
        k1 = h*dydx(x0, y); 
        k2 = h*dydx(x0 + 0.5*h, y + 0.5*k1); 
        k3 = h*dydx(x0 + 0.5*h, y + 0.5*k2); 
        k4 = h*dydx(x0 + h, y + k3); 
  
        // Update next value of y 
        y = y + (1.0/6.0)*(k1 + 2*k2 + 2*k3 + k4);; 
  
        // Update next value of x 
        x0 = x0 + h; 
    } 
  
    return y; 
} 



//parte de timer


   
    void Timer::start()
    {
        m_StartTime = std::chrono::system_clock::now();
        m_bRunning = true;
    }
    
    void Timer::stop()
    {
        m_EndTime = std::chrono::system_clock::now();
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
        
        return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count();
    }
    
    double Timer::elapsedSeconds()
    {
        return elapsedMilliseconds() / 1000.0;
    }

   

