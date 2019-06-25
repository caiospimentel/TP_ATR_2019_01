#include <thread>
#include <stdio.h> 
#include <math.h>
#include "customLibraries.h"


// utilizar o valor de h gerado pela função runge kutta, comparado com a referência href recebida do sinoptico, atuar na vazão de entrada do tanque.


int main (){


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


return 0;
}