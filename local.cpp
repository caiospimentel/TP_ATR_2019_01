#include <thread>
#include <stdio.h> 
#include <math.h>
#include <iostream>
#include <mutex>
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <string.h> 
#include "customLibraries.h"

using namespace std;

    float H;
    float href;
    float qin;
    mutex mH;
    mutex mQ;

void process_thread() { 
   Timer t;
   float qin_inicial = 0;
    
    do{
    t.start();

    float h = 0.2; 
    
    mH.lock();
    H = rungeKutta(qin_inicial, H, qin, h); //nivel calculado pela variação total
    mH.unlock();

    while(t.elapsedMilliseconds() < 50.0);
    t.stop();
    mQ.lock();
    qin_inicial = qin;
    mQ.unlock();
    }while (true);


} 

void softPLC_thread(){

    

    float error, output_H ;
    Timer t;

    //declaração e inicialização do PID
    pid_ctrl_t pid;
    pid_init(&pid);

    //configuração dos parâmetros do PID
    pid_set_gains(&pid, 10., 0, 4.);

    //loop de execução
        while(true){

            //receber parâmetros TCP --href



            t.start();
            mH.lock();
            error = H-href;
            output_H = pid_process(&pid, error); //calculo do valor de altura de saida desejado


            //daqui pra baixo mt provavelmente errado
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
            while(t.elapsedMilliseconds() < 50.0);
            t.stop();

            //Inserir envio TCP

            

        }

}

int main(int argc, char const *argv[])
{
    
    thread pt (process_thread);
    thread plct (softPLC_thread);

    cout << "Rodando as threads";

    pt.join();
    plct.join();





    return 0;
}
