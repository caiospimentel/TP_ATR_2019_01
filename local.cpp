#include <thread>
#include <stdio.h> 
#include <math.h>
#include <iostream>
#include "customLibraries.hpp"

using namespace std;

void process_thread() { 
   Timer t;
    float H;
    do{
    t.start();
    float x0 = 0, y = 1, x = 3, h = 0.2; 
    
    H = rungeKutta(x0, y, x, h); //nivel calculado pela variação total


    while(t.elapsedMilliseconds() < 50.0);
    t.stop();
    }while (true);


} 

void softPLC_thread(){

    float H;
    float href;
    float qin;

    float error, output_H ;
    Timer t;

    //declaração e inicialização do PID
    pid_ctrl_t pid;
    pid_init(&pid);

    //configuração dos parâmetros do PID
    pid_set_gains(&pid, 10., 0, 4.);

    //loop de execução
        while(true){
            t.start();
            error = H-href;
            output_H = pid_process(&pid, error); //calculo do valor de altura de saida desejado


            //daqui pra baixo mt provavelmente errado
            //ação de controle no atuador
            if(output_H > H){
                qin += 1;
            }
            else{
                qin -= 1;
            }
            while(t.elapsedMilliseconds() < 50.0);
            t.stop();
        }

}

int main(int argc, char const *argv[])
{
    
    thread pt (process_thread);
    thread plct (softPLC_thread);

    cout << "Rodando as threads";





    return 0;
}
