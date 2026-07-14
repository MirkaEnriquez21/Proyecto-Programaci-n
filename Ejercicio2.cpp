#include <iostream>
#include "arreglos.h"
#include <cmath>

using namespace std;

int Ejercicio2(){
    int opcion;

    do{
    	cout << "+---------------------------------------------------+\n";
        cout << "|               METODO NEWTON-RAPHSON               |\n"; 
    	cout << "+---------------------------------------------------+\n";
        cout << "|  1. tan(x) + x^2 - 1 = 0                          |\n"; 
        cout << "|  2. cos(x) - x = 0                                |\n";
        cout << "|  3. e^x - 3x = 0                                  |\n";
        cout << "|  4. x^3 - x - 2 = 0                               |\n";
        cout << "|  5. sin(x) + x^2 - 2 = 0                          |\n";
        cout << "|  6. ln(x) + x - 2                                 |\n";
        cout << "|  7. log10(x) - x + 1                              |\n";
        cout << "|  8. x*ln(x) - 1                                   |\n";
        cout << "|  9. x^4 - 10                                      |\n";
        cout << "| 10. e^(-x) - x                                    |\n";
        cout << "| 11. Regresar al Menu Principal                    |\n";
    	cout << "+---------------------------------------------------+\n";

        cout << " Seleccione una opcion [1-11]: \n";
        cout << " -> ";

        // Validar que se ingrese un número
        while (!(cin >> opcion)){
            cout << "\n[ERROR] Debe ingresar un numero entre 1 y 11.\n";

            cin.clear();
            cin.ignore(1000, '\n');

            cout << "\nOpcion: ";
        }

        // Limpiar el salto de línea
        cin.ignore(1000, '\n');

        // Salir
        if (opcion == 11){
            cout << "\n*****************************************************\n";
		    cout << "\n       Saliendo al menu principal...\n";
		    cout << "\n*****************************************************\n";
            break;
        }

        // Validar rango
        if (opcion < 1 || opcion > 11){
            cout << "\n[ERROR] Opcion no valida.\n";
            cout << "\nPresione Enter para volver al menu...";
            cin.get();
            continue;
        }

        bool raiz;
        double x0 = buscarValorInicial(opcion, raiz);

        if (!raiz){
            cout << "\nNo se encontro una raiz en el intervalo.\n";
            cout << "\nPresione Enter para volver al menu...";
            cin.get();
            continue;
        }

        cout << "\nValor inicial encontrado: " << x0 << endl;

        newtonRaphson(x0, opcion);

        cout << "\nPresione Enter para volver al menu...";
        cin.get();

    } while (true);

    return 0;
}

// Funcion de cada ecuacion
double f(double x, int opcion){
    switch(opcion){
        case 1:
            return tan(x) + x*x - 1;

        case 2:
            return cos(x) - x;

        case 3:
            return exp(x) - 3*x;

        case 4:
            return x*x*x - x - 2;

        case 5:
            return sin(x) + x*x - 2;

        case 6:
            return log(x) + x - 2;

        case 7:
            return log10(x) - x + 1;

        case 8:
            return x*log(x) - 1;

        case 9:
            return pow(x,4) - 10;

        case 10:
            return exp(-x) - x;

        default:
            return 0;
    }
}

// Derivada numerica
double derivada(double x, int opcion){
    double h = 0.000001;

    return (f(x+h,opcion)-f(x-h,opcion))/(2*h);
}

// Busca automaticamente un valor inicial
double buscarValorInicial(int opcion, bool &raiz){
    double inicio = -2;
    double fin = 2;

    if(opcion >= 6 && opcion <= 8){
        inicio = 0.1;
        fin = 5;
    }

    for(double x=inicio; x<fin; x+=0.1){
        if(f(x,opcion)*f(x+0.1,opcion) < 0){
            raiz = true;
            return x;
        }
    }

    raiz = false;
    return 0;
}

// Metodo de Newton-Raphson
double newtonRaphson(double x0, int opcion){
    double x1;
    double error;
    int iteracion = 0;

    cout << "\nIteraciones\n";

    do{
        x1 = x0 - (f(x0,opcion)/derivada(x0,opcion));

        error = fabs(x1-x0);

        cout << "Iteracion " << iteracion+1 << ": x = " << x1 << endl;

        x0 = x1;

        iteracion++;

    }while(error > 0.000001);

    cout << "\nRaiz aproximada: " << x1 << endl;

    cout << "Iteraciones realizadas: " << iteracion << endl;

    return x1;
}
