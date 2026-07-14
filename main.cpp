#include <iostream>
#include "arreglos.h"

using namespace std;

int main(){

    char sma = '0';
	
	while (sma != '4'){
		cout << "+--------------------------------------------------------------+\n";
	    cout << "|            A continuacion escoja el ejercicio                |\n";
	    cout << "+--------------------------------------------------------------+\n";
	    cout << "|  1. Ejercicio1: RED NEURONAL                                 |\n";
	    cout << "|  2. Ejercicio2: ECUACIONES COMPLEJAS                         |\n";
	    cout << "|  3. Ejercicio3: SISTEMA ECUACIONES LINEALES                  |\n";
	    cout << "|  4. SALIR                                                    |\n";
	    cout << "+--------------------------------------------------------------+\n";
	    
	    cout << " Seleccione una opcion [1-4]: \n";
	    cout << " -> ";
	    cin >> sma;
		
		switch(sma){
			case '1':
				Ejercicio1();
				break;
				
			case '2':
				Ejercicio2();
				break;
				
			case '3':
				Ejercicio3();
				break;
				
			case '4':
				cout << "\n       Saliendo del programa...\n";
                break;
                
            default:
                cout << " [ERROR] '" << sma << "' no es una opcion valida. Intente de nuevo.\n";
                break;
				
		}
	}
}
