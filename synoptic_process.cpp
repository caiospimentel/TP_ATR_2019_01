#include <stdio.h> 
#include <iostream>
#include <stdlib.h>
#include <chrono>
 

 class Timer //transformar em .hpp posteriormente
{

public:
    void start()
    {
        m_StartTime = std::chrono::system_clock::now();
        m_bRunning = true;
    }
    
    void stop()
    {
        m_EndTime = std::chrono::system_clock::now();
        m_bRunning = false;
    }
    
    double elapsedMilliseconds()
    {
        std::chrono::time_point<std::chrono::system_clock> endTime;
        
        if(m_bRunning)
        {
            endTime = std::chrono::system_clock::now();
        }
        else
        {
            endTime = m_EndTime;
        }
        
        return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count();
    }
    
    double elapsedSeconds()
    {
        return elapsedMilliseconds() / 1000.0;
    }

private:
    std::chrono::time_point<std::chrono::system_clock> m_StartTime;
    std::chrono::time_point<std::chrono::system_clock> m_EndTime;
    bool                                               m_bRunning = false;
};


//TODO: Aqruivo historiador
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
 
    do{
    
    t.start();
    cout << "----------------------------------------------------------------------------------\n";
    cout << "Tela Supervisória do Processo\n";
    cout << "Nível do Tanque : " << nivel << "      Vazão de Entrada:" << qin << "      Vazão de Saída:" << qout << "\n";
    cout << "Setpoint atual: " << href <<"\n";
    cout << "----------------------------------------------------------------------------------\n";
    cout <<"Setpoint atualizado a cada ciclo de 50ms" <<"\n";
    cout << "Entrada de Setpoint (ou pressione s para encerrar):\n";
    cin >> href;
    
    
    
    while(t.elapsedMilliseconds() < 50.0);
    t.stop();
    //Clear screen
    for (int cls = 0; cls <100; cls++){
        cout << "\n";
    }
   
    } while(true);


}