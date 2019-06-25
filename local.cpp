#include <thread>
#include <stdio.h> 
#include <math.h>
#include <iostream>
#include <mutex>
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>
#include "customLibraries.h"

using namespace std;


    //variáveis globais
    float H; //altura em função do tempo, maiúsculo para diferenciar do stepsize da integração
    float qin; //vazão de entrada
    mutex mH; //mutex para proteção de H
    mutex mQ; //mutex para a proteção de qin

void process_thread() { 
   Timer t;
   float qin_inicial = 0;
    
    do{
    t.start();

    float h = 0.2; //step size da integração
    
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

    
    float href; //setpoint
    float error, output_H ; 
    Timer t;
    char *buffer = malloc(100);
    memset(buffer, 0, tamanho_buffer);
    int porta_servidor = atoi(argv[1]);


    //declaração e inicialização do PID
    pid_ctrl_t pid;
    pid_init(&pid);

    //configuração dos parâmetros do PID
    pid_set_gains(&pid, 5, 0.5, 3);

    //inicializar socket
    struct sockaddr_in endereco_servidor;
	
	int socket_cliente;


	//Criação de socket para o cliente
	socket_cliente = socket(AF_INET, SOCK_STREAM, 0);
    endereco_servidor.sin_family = AF_INET;
	endereco_servidor.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	endereco_servidor.sin_port = htons(porta_servidor);
	memset(&endereco_servidor.sin_zero, 0, 8);


    //conexão com o servidor
    connect(socket_cliente, (struct sockaddr*) &endereco_servidor, sizeof(endereco_servidor));


    //loop de execução
        while(true){

            //enviar parâmetros atuais: -- converter de float para caracter
            


            snprintf(buffer, sizeof buffer, "%f", H);
            snprintf(buffer, sizeof buffer, "%f", qin);

            cout << buffer;

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

            //Inserir envio TCP



        }
        free(buffer);

}

int main(int argc, char const *argv[]){
    
    cout << "Início da função main\n" ;
    thread pt (process_thread);
    thread plct (softPLC_thread);

    cout << "Rodando as threads";

    pt.join();
    plct.join();





    return 0;
}
