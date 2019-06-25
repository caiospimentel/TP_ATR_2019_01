#include <thread>
#include <stdio.h> 
#include <math.h>
#include <iostream>
#include <mutex>
#include "customLibraries.h"

using namespace std;

    float H; //altura em função do tempo, maiúsculo para diferenciar do stepsize da integração
    float href; //setpoint
    float qin; //vazão de entrada
    mutex mH; //mutex para proteção de H
    mutex mQ; //mutex para a proteção de qin

void process_thread() { 
   Timer t;
   float qin_inicial = 0;
    
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


} 

void softPLC_thread(){

    

    float error, output_H ;
    Timer t;

    //declaração e inicialização do PID
    pid_ctrl_t pid;
    pid_init(&pid);

    //configuração dos parâmetros do PID
    pid_set_gains(&pid, 5, 0.5, 3);

    //loop de execução
        while(true){

          



            t.start();
            mH.lock();
            error = H-href;
            output_H = pid_process(&pid, error); //calculo do valor de altura de saida desejado


           
            //ação de controle no atuador
            if(output_H > H){
                mQ.lock();
                qin += 1;
                mQ.unlock();
            }
            else{
                mQ.lock();
                qin -= 1;
                mQ.unlock();
            }
            mH.unlock();
            while(t.elapsedMilliseconds() < 50.0); //aguarda 50ms no mínimo
            t.stop();

            



        }

}

int main()
{
    
    cout << "Inicio do programa";
    
    thread pt (process_thread);
    thread plct (softPLC_thread);

    cout << "Rodando as threads";

    pt.join();
    plct.join();





    return 0;
}
