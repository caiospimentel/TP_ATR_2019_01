#include <stdio.h> 
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <fstream>
#include <sys/socket.h> 
#include <string.h> 
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <unistd.h>
#include <cstdlib>
#include <errno.h>
#include "customLibraries.h"

 #define print_error_and_exit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0);

using namespace std;



int main(int argc, char const *argv[]){
    int porta_servidor = atoi(argv[1]);
    float nivel = 0, qout = 0, qin = 0; //variáveis do processo
    char *href;
    Timer t;
    int i = 1;
    ofstream mfile;
    char new_values_1[100];
    char new_values_2[100];

    cout << porta_servidor <<"\n";
   
    //inicialização da estrutura de socket

    struct sockaddr_in endereco_servidor;
    struct sockaddr_in  endereco_cliente;

	socklen_t size = sizeof(endereco_cliente);


    int socket_servidor, socket_cliente;

    socket_servidor = socket(AF_INET, SOCK_STREAM, 0);

	if(socket_servidor == -1){
		printf("Erro na criação do socket.");
		
		return 0;
	}

  
    endereco_servidor.sin_family = AF_INET;
	endereco_servidor.sin_port = htons(porta_servidor);	
    endereco_servidor.sin_addr.s_addr = INADDR_ANY; 
	memset(endereco_servidor.sin_zero, 0, 8);

	int erro_bind = bind(socket_servidor, (struct sockaddr*) &endereco_servidor, sizeof(endereco_servidor)); 

	if (erro_bind == -1){
		 print_error_and_exit("bind");
	}

 
     cout <<"Início do listen\n";

    listen(socket_servidor, 1); //O segundo parâmetro diz quantas conexões são aceitas
	socket_cliente = accept(socket_servidor, (struct sockaddr*) &endereco_cliente, &size);


	if(socket_cliente == -1){
		printf("Erro ao aceitar conexão.\n");
		close(socket_servidor);
		
		return 0;
	}


    do{
    
    t.start();

    //inicia a conexão do servidor

   

    int tamanho_resposta_recebida;
	do{
		tamanho_resposta_recebida = recv(socket_cliente, new_values_1, 100, 0);
	}while(tamanho_resposta_recebida < 0);
        
       
        strcpy(new_values_2, new_values_1);

        //tratar new values;
       //tokenizer e colocar direatmente dentro do strtok
       char* t2 = strtok(new_values_2, " ");
       t2 = strtok(NULL, " "); //pega o valor de qin

       char* t1 = strtok(new_values_1, " "); //pega o valor de H/nível

       nivel = atof(t1);
       qin = atof (t2);
       qout = sqrt(qin);

       



    cout << "--------------------------------------------------------------------------------\n";
    cout << "Tela Supervisória do Processo\n";
    cout << "Nível do Tanque : " << nivel << "      Vazão de Entrada:" << qin << "      Vazão de Saída:" << qout << "\n";
    cout << "Setpoint atual: " << href <<"\n";
    cout << "--------------------------------------------------------------------------------\n";
    cout <<"Setpoint atualizado a cada ciclo de 50ms" <<"\n";
    cout << "Entrada de Setpoint:\n";
    cin >> href;

    cout <<"\n";
    cout << "Valor de href:" << href << "\n";
    
    
    
    while(t.elapsedMilliseconds() < 50.0); //aguarda 50ms no mínimo
    t.stop();
    mfile.open("historiador.txt", ios_base::app);
    mfile << i << ") h = "<< nivel << " Qin = " << qin << " Qout = " << qout << " href = " << href <<"\n";
    mfile.close();
    i++;

    


   send(socket_cliente, href, strlen(href), 0); //enviar href

    //Clear screen
    for (int cls = 0; cls <100; cls++){
        cout << "\n";
    }
   
    } while(true);


}
