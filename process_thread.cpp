// C program to implement Runge Kutta method 
#include <stdio.h> 
#include <math.h>
#include "customLibraries.hpp"
  
// A sample differential equation "dy/dx = (x - y)/2" 

//o valor de qin vai ser recebido do controlador.

  using namespace std;


int main() 
{ 
    Timer t;
    float H;
    do{
    t.start();
    float x0 = 0, y = 1, x = 3, h = 0.2; 
    
    H = rungeKutta(x0, y, x, h); //nivel calculado pela variação total


    while(t.elapsedMilliseconds() < 50.0);
    t.stop();
    }while (true);

    return 0;
} 



    //int a = (R1-R0)/H;

    //float dh = ( (-Cv * sqrt(H) ) / (M_PI * exp2(R0+a*H) ) ) + (qin / ( M_PI * exp2(R0+a*H) ) ) ; //equação dinâmica do reservatório



	



