#include <stdio.h> 
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <fstream>
#include "customLibraries.hpp"



//TODO: Comunicação socket tcp
//a comunicação ocorre sempre dentro do main, toda vez que ele abre. Temporização de 50s pode ser um problema

using namespace std;


//se sobrar tempo, fazer uma thread pra cuidar do input do teclado, comunicando com a principal quando isso ocorrer
//dessa forma, é possível manter o sistema atualizado, checando sempre no início de houve um novo input
int main(){

 
    
    float nivel = 0, qout = 0, qin = 0;
    float href = 0;
    char input = 'a';
    Timer t;
    int i = 1;
    ofstream mfile;
 
    do{
    
    t.start();
    cout << "--------------------------------------------------------------------------------\n";
    cout << "Tela Supervisória do Processo\n";
    cout << "Nível do Tanque : " << nivel << "      Vazão de Entrada:" << qin << "      Vazão de Saída:" << qout << "\n";
    cout << "Setpoint atual: " << href <<"\n";
    cout << "--------------------------------------------------------------------------------\n";
    cout <<"Setpoint atualizado a cada ciclo de 50ms" <<"\n";
    cout << "Entrada de Setpoint (ou pressione s para encerrar):\n";
    cin >> href;
    
    
    
    while(t.elapsedMilliseconds() < 50.0);
    t.stop();
    mfile.open("historiador.txt", ios_base::app);
    mfile << "Iteracao " << i << ") h = "<< nivel << " Qin = " << qin << " Qout = " << qout << " href = " << href <<"\n";
    mfile.close();
    i++;

    //Clear screen
    for (int cls = 0; cls <100; cls++){
        cout << "\n";
    }
   
    } while(true);


}