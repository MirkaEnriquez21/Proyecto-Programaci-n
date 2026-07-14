#include <iostream>
#include "arreglos.h"

using namespace std;

int Ejercicio3(){
	
	char variables[] = {'x', 'y', 'z', 'w'};

    while(true){

        int incognitas = menu();

        if(incognitas == 0){
        	cout << "\n*****************************************************\n";
		    cout << "\n       Saliendo al menu principal...\n";
		    cout << "\n*****************************************************\n";
		    return 0;
		}

        double matriz[4][5];
        double solucion[4];

        ingresarDatos(matriz, incognitas, variables);

        eliminacionGauss(matriz, incognitas);

        int tipo = verificarSistema(matriz, incognitas);

        cout << "********************* SOLUCION *********************\n";

        if(tipo == 1){
            cout << " El sistema tiene infinitas soluciones.\n";
            cout << "****************************************************\n";
            continue;
        }

        if(tipo == 2){
            cout << " El sistema no tiene solucion.\n";
            cout << "****************************************************\n";
            continue;
        }

        sustitucionAtras(matriz, solucion, incognitas);

        mostrarSolucion(solucion, incognitas, variables);

        cout << endl;
        cout << "****************************************************\n";
    }
}

// MENU
int menu(){

    int option;

    cout << "+---------------------------------------------------+\n";
    cout << "|    Escoja la forma de su sistema de ecuaciones    |\n";
    cout << "+---------------------------------------------------+\n";
    cout << "|  1. ax + by = c                                   |\n";
    cout << "|  2. ax + by + cz = d                              |\n";
    cout << "|  3. ax + by + cz + dw = e                         |\n";
    cout << "|  4. Regresar al Menu Principal                    |\n";
    cout << "+---------------------------------------------------+\n";

    while(true){

        cout << " Seleccione una opcion [1-4]: \n";
        cout << " -> ";
        cin >> option;

        if(cin.fail()){
    		cout << "+---------------------------------------------------+\n";
            cout << "|    Entrada invalida. Debe ingresar un numero.     |\n";
    		cout << "+---------------------------------------------------+\n";

            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if(option >= 1 && option <= 3){
			int incognitas = option + 1;
            return incognitas;  
        }
        else if(option == 4){
    		return 0;
		}
        else{
    		cout << "+---------------------------------------------------+\n";
            cout << "|       Opcion invalida. Intente nuevamente.        |\n";
    		cout << "+---------------------------------------------------+\n";
		}
    }
}

// INGRESO DE DATOS
void ingresarDatos(double matriz[][5], int incognitas, char variables[]){

    cout << "+---------------------------------------------------+\n";

    for(int i = 0; i < incognitas; i++){

        // Mostrar forma de la ecuación
        cout << "***************** ECUACION #" << i+1 << " ******************\n";
		cout << "              ";
		
        for(int j = 0; j < incognitas; j++){

            cout << " (_)" << variables[j];

            if(j < incognitas - 1)
                cout << " +";
        }

        cout << " = (_)\n";

        // Ingresar coeficientes
        for(int j = 0; j < incognitas; j++){

            while(true){

                cout << "Coeficiente de " << variables[j] << ": ";
                cin >> matriz[i][j];

                if(cin.fail()){
            		cout << "+---------------------------------------------------+\n";
            		cout << "|        Entrada invalida. Ingrese un numero.       |\n";
    				cout << "+---------------------------------------------------+\n";

                    cin.clear();
                    cin.ignore(1000, '\n');
                    
                }else break;
            }
        }

        // Ingresar término independiente
        while(true){

            cout << "Termino independiente: ";
            cin >> matriz[i][incognitas];

            if(cin.fail()){
                cout << "+---------------------------------------------------+\n";
            	cout << "|        Entrada invalida. Ingrese un numero.       |\n";
    			cout << "+---------------------------------------------------+\n";

                cin.clear();
                cin.ignore(1000, '\n');
                
            } else break;
        }

        cout << endl;
    }
}

// VERIFICAR PIVOTE SEA 0
void verificarPivote(double matriz[][5], int incognitas, int fila){

    if(matriz[fila][fila] == 0){
        for(int i = fila + 1; i < incognitas; i++){
            if(matriz[i][fila] != 0){
            	//intercambiar filas 
                for(int j = 0; j <= incognitas; j++){
                    double aux = matriz[fila][j];
                    matriz[fila][j] = matriz[i][j];
                    matriz[i][j] = aux;
                }
                return;
            }
        }
        exit(0);
    }
}

//ELIMINACION GAUSS
void eliminacionGauss(double matriz[][5], int incognitas){

    for(int i = 0; i < incognitas - 1; i++){

        verificarPivote(matriz, incognitas, i);

        for(int j = i + 1; j < incognitas; j++){
            double factor = matriz[j][i] / matriz[i][i];
            for(int k = i; k <= incognitas; k++) matriz[j][k] -= factor * matriz[i][k];
        }
    }
}

//IDENTIFICAR SISTEMA
int verificarSistema(double matriz[][5], int incognitas){

    for(int i = 0; i < incognitas; i++){

        bool todosCeros = true;
		//comprobar que exista una fila de 0
        for(int j = 0; j < incognitas; j++){
            if(matriz[i][j] != 0){
                todosCeros = false;
                break;
            }
        }
        
        if(todosCeros){
            if(matriz[i][incognitas] == 0) return 1;   // Infinitas soluciones
            else return 2;   // Sin solución
        }
    }

    return 0;   // Solución única
}

// SUSTITUCION HACIA ATRAS
void sustitucionAtras(double matriz[][5], double solucion[], int incognitas){

    for(int i = incognitas-1; i >= 0; i--){

        solucion[i] = matriz[i][incognitas];

        for(int j = i+1; j < incognitas; j++){
            solucion[i] -= matriz[i][j] * solucion[j];
        }

        solucion[i] /= matriz[i][i];
    }
}

// MOSTRAR SOLUCION
void mostrarSolucion(double solucion[], int incognitas, char variables[]){

    for(int i = 0; i < incognitas; i++) cout << " " << variables[i] << " = " << solucion[i] << endl;

}
