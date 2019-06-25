#include <stdio.h> 
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <fstream>
#include "customLibraries.h"



using namespace std;



int main(){

    //qout é Cv*sqrt(nivel), mas Cv foi definido como 1
     
    
    float nivel = 1, qout = sqrt(nivel), qin = 0; // variáveis do processo
    float href = 0;
    float old_href = 0; //variável auxiliar
    Timer t;
    int i = 1; //contagem das iterações do código
    ofstream mfile;
    char input;


    mfile.open("historiador.txt"); //limpa o arquivo historiador de execuções passadas
    mfile << "\n";
    mfile.close();
 
    while (true){
    old_href = href;//salva o valor anterior de href, para recuperar caso o valor novo seja inválido
    t.start();
    cout << "--------------------------------------------------------------------------------\n";
    cout << "Tela Supervisória do Processo\n";
    cout << "Nível do Tanque : " << nivel << "      Vazão de Entrada:" << qin << "      Vazão de Saída:" << qout << "\n";
    cout << "Setpoint atual: " << old_href <<"\n";
    cout << "--------------------------------------------------------------------------------\n";
    cout <<"Setpoint atualizado a cada ciclo de 50ms" <<"\n";
    cout << "Deseja colocar um novo setpoint ou encerrar a execução? [S/C]:\n";
    

    cin >> input;
    cout <<"\n";
    if(input == 'S' || input == 's' ){
        cout << "Insira o valor de Setpoint\n";
        cin >> href;
        if(href>10 || href <0){ //tratamento de href dentro das dimensões do tanque
            cout <<"\n";
            cout << "Valor fora das dimensões do tanque, tente novamente. pressione qualquer tecla e enter para retornar ao início \n";
            cin >> input;
            href = old_href; //caso sejá inválido, mantém o setpoint inalterado;

        }


    }
    else if (input == 'C' || input == 'c' ){
        exit(1);
    }
    else{
        cout << "entrada inválida, tente novamente\n";
    }

    
    
    
    
    while(t.elapsedMilliseconds() < 50.0); //aguarda 50ms no mínimo
    t.stop();
    mfile.open("historiador.txt", ios_base::app); //abre o arquivo historiador e salva os dados atuais
    mfile << i << ") h = "<< nivel << " Qin = " << qin << " Qout = " << qout << " href = " << href <<"\n";
    mfile.close();
    i++;

    //Clear screen
    for (int cls = 0; cls <100; cls++){
        cout << "\n";
    }
   
    }



}