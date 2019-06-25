#include <thread>
#include <stdio.h> 
#include <math.h>
#include <iostream>
#include <mutex>
#include "customLibraries.h"
  

//o valor de qin vai ser recebido do controlador.

  using namespace std;


int main() 
{ 


    Timer t;
    float qin_inicial = 0;
    float H; //altura em função do tempo, maiúsculo para diferenciar do stepsize da integração
    float href; //setpoint
    float qin; //vazão de entrada
    mutex mH; //mutex para proteção de H
    mutex mQ; //mutex para a proteção de qin

    cout << "Uepa";
    do{
    t.start();

    float h = 0.2; //step size da integração
    
    //mutexes de proteção das variáveis globais
    mH.lock();
    mQ.lock();
    H = rungeKutta(qin_inicial, H, qin, h); //nivel calculado pela variação total
    mQ.unlock();
   

    while(t.elapsedMilliseconds() < 50.0); //aguarda 50ms no mínimo
    t.stop();

    mQ.lock();
    qin_inicial = qin;
    mQ.unlock();
    mH.unlock();
    }while (true);

    return 0;
} 



    //int a = (R1-R0)/H;

    //float dh = ( (-Cv * sqrt(H) ) / (M_PI * exp2(R0+a*H) ) ) + (qin / ( M_PI * exp2(R0+a*H) ) ) ; //equação dinâmica do reservatório



	



