#include <stdio.h> 
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <fstream>
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <unistd.h>
#include <cstdlib>
#include "customLibraries.h"


//tratamento do range de input
using namespace std;


//se sobrar tempo, fazer uma thread pra cuidar do input do teclado, comunicando com a principal quando isso ocorrer
//dessa forma, é possível manter o sistema atualizado, checando sempre no início de houve um novo input
int main(int argc, char const *argv[]){
    cout << "uepa\n" ;
    int porta_servidor = atoi(argv[1]);
    float nivel = 0, qout = 0, qin = 0; //variáveis do processo
    float href = 0; //setpoint
    Timer t;
    int i = 1;
    ofstream mfile;
    char *buffer;


    snprintf(buffer, sizeof buffer, "%f", href);

    cout << "valor convertido de href para caracter" << buffer << "\n";
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
	memset(endereco_servidor.sin_zero, 0, 8);

	int erro_bind = bind(socket_servidor, (struct sockaddr*) &endereco_servidor, sizeof(endereco_servidor)); 

	if (erro_bind == -1){
		printf("Erro no bind.\n");
		close(socket_servidor);
		
		return 0;
	}

 
    do{
    
    t.start();

    //inicia a conexão do servidor

    listen(socket_servidor, 1); //O segundo parâmetro diz quantas conexões são aceitas
	socket_cliente = accept(socket_servidor, (struct sockaddr*) &endereco_cliente, &size);


	if(socket_cliente == -1){
		printf("Erro ao aceitar conexão.\n");
		close(socket_servidor);
		
		return 0;
	}

    cout << "--------------------------------------------------------------------------------\n";
    cout << "Tela Supervisória do Processo\n";
    cout << "Nível do Tanque : " << nivel << "      Vazão de Entrada:" << qin << "      Vazão de Saída:" << qout << "\n";
    cout << "Setpoint atual: " << href <<"\n";
    cout << "--------------------------------------------------------------------------------\n";
    cout <<"Setpoint atualizado a cada ciclo de 50ms" <<"\n";
    cout << "Entrada de Setpoint:\n";
    cin >> href;
    
    
    
    while(t.elapsedMilliseconds() < 50.0); //aguarda 50ms no mínimo
    t.stop();
    mfile.open("historiador.txt", ios_base::app);
    mfile << i << ") h = "<< nivel << " Qin = " << qin << " Qout = " << qout << " href = " << href <<"\n";
    mfile.close();
    i++;

    snprintf(buffer, sizeof buffer, "%f", href);

    cout << "valor convertido de href para caracter" << buffer ;
    send(socket_cliente, buffer, strlen(buffer), 0); //enviar href

    //Clear screen
    for (int cls = 0; cls <100; cls++){
        cout << "\n";
    }
   
    } while(true);


}