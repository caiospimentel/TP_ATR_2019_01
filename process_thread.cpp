	// C program to implement Runge Kutta method 
#include <thread>
#include <stdio.h> 
#include <math.h>
#include <iostream>
#include <mutex>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sstream>
#include <cstring>
#include <thread>


int a;
  
// A sample differential equation "dy/dx = (x - y)/2" 



  using namespace std;

int main(int argc, char const *argv[]) 
        {
    
          int porta_servidor = atoi(argv[1]);
      //inicializar socket
    struct sockaddr_in endereco_servidor;
	
	int socket_cliente;


	//Criação de socket para o cliente
	socket_cliente = socket(AF_INET, SOCK_STREAM, 0);
  endereco_servidor.sin_family = AF_INET;
	endereco_servidor.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	endereco_servidor.sin_port = htons(porta_servidor);


    //conexão com o servidor
    if(connect(socket_cliente, (struct sockaddr*) &endereco_servidor, sizeof(endereco_servidor))){
		printf("Servidor não encontrado.");
		close(socket_cliente);
        //inserir um fork aqui;
    	}

  //tudo funciona até aqui
  
    while(true){
      cout << "Enviando valores...\n";
        //enivar valores do buffer
float H = 1;
float qin = 2;	

            ostringstream ss;
            ss << H << " " << qin;
            string temp = ss.str();
            char* buffer  = new char[temp.length()+1];
            strcpy(buffer, temp.c_str()); //buffer carregado com os valores atuais das variáveis

        send(socket_cliente, buffer, strlen(buffer), 0);

        cout << "Valores enviados\n";


        cout << "Rebendo HREF do servidor\n";

      char recv_buffer[100];
        int tamanho_resposta_recebida;
	      do{
		      tamanho_resposta_recebida = recv(socket_cliente, recv_buffer, strlen(recv_buffer), 0);
        	}while(tamanho_resposta_recebida < 0);

      cout << "Valor recebido do servidor:" << recv_buffer;












    }

























}




    //int a = (R1-R0)/H;

    //float dh = ( (-Cv * sqrt(H) ) / (M_PI * exp2(R0+a*H) ) ) + (qin / ( M_PI * exp2(R0+a*H) ) ) ; //equação dinâmica do reservatório



	



