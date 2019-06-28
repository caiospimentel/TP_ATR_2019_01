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

using namespace std;
int main(){
	
float H = 1;
float qin = 2;
char *t1, *t2;
            cout <<"colé\n";
            //carregamento dos valores atuais num buffer
	        ostringstream ss;
            stringstream a;
            ss << H << " " << qin;
            string temp = ss.str();

            char* buffer  = new char[temp.length()+1];
            char* buff2 = new char[temp.length()+1];

            strcpy(buffer, temp.c_str()); //buffer carregado com os valores atuais das variáveis
            strcpy(buff2, temp.c_str());

            t2 = strtok (buff2," ");
            t2 = strtok (NULL, " ");
             

            t1 = strtok(buffer, " ");


            printf("%s \n", t1);
            printf("%s \n", t2);
return 0;
}
