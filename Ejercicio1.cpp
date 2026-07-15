#include <iostream>
#include "arreglos.h"

using namespace std;

void Ejercicio1(){
	cout << "+---------------------------------------------------+" << endl;
    cout << "|        CONFIGURACION INICIAL DE LA NEURONA        |" << endl;
    cout << "+---------------------------------------------------+" << endl;

    int totalDatos = solicitarTotalDatos();
    cout << "-----------------------------------------------------" << endl;
	
	double peso = solicitarParametro("el PESO inicial (w)");
    double sesgo = solicitarParametro("el SESGO inicial (b)");
    double tasaAprendizaje = solicitarParametro("la TASA DE APRENDIZAJE (n)");
    cout << "-----------------------------------------------------" << endl;

    double pesoInicial = peso;
    double sesgoInicial = sesgo;
    
    double datosX[100];
    double datosY[100];
    capturarDatos(datosX, datosY, totalDatos);

	int contadorIteraciones = entrenarRed(datosX, datosY, totalDatos, peso, sesgo, tasaAprendizaje);

    char opcionMenu = '0';

    while (opcionMenu != '6') {
        cout << endl << endl;
        cout << "+---------------------------------------------------+\n";
        cout << "|          SISTEMA DE RED NEURONAL LINEAL           |\n";
        cout << "+---------------------------------------------------+\n";
        cout << "|  1. Ver Tabla de Datos Registrada (X e Y)         |\n";
        cout << "|  2. Ver Simulacion Paso a Paso (y, w, b, a, E)    |\n";
        cout << "|  3. Ver Pesos y Sesgos Optimos Finales            |\n";
        cout << "|  4. Ver Ecuacion Lineal Encontrada                |\n";
        cout << "|  5. Probar Ecuacion                               |\n";
        cout << "|  6. Regresar al Menu Principal                    |\n";
        cout << "+---------------------------------------------------+\n";
        cout << " Seleccione una opcion [1-6]: \n";
        cout << " -> ";
        cin >> opcionMenu;
        cout << endl << "********************* RESPUESTA *********************" << endl << endl;

        switch (opcionMenu) {
            case '1':
                mostrarTablaDatos(datosX, datosY, totalDatos, contadorIteraciones);
                break;
            case '2':
                simularPasoAPaso(datosX, datosY, totalDatos, contadorIteraciones, pesoInicial, sesgoInicial, tasaAprendizaje);
                break;
            case '3':
                cout << " PARAMETROS OPTIMIZADOS POR EL GRADIENTE:\n";
                cout << " * Peso final (w) : " << peso << endl;
                cout << " * Sesgo final (b): " << sesgo << endl;
                break;
            case '4':
                cout << " FORMULA MATEMATICA APRENDIDA POR LA RED:\n";
                cout << " * Ecuacion: Y = " << peso << " * X + " << sesgo << endl;
                break;
            case '5':
                realizarPrediccion(peso, sesgo);
                break;
            case '6':
                cout << "       Saliendo al menu principal...\n";
                break;
            default:
                cout << " [ERROR] '" << opcionMenu << "' no es una opcion valida. Intente de nuevo.\n";
                break;
        }
        cout << "\n*****************************************************\n";
    }
}

int solicitarTotalDatos() {
    int totalDatos;
    while (true) {
        cout << " Ingrese la cantidad de filas de datos a registrar: \n";
        cout << " -> ";
        cin >> totalDatos;
        
        if (cin.fail() || totalDatos <= 0 || totalDatos > 100) {
            cin.clear();
            while (cin.get() != '\n');
            cout << " [ERROR] Por favor, ingrese un numero entero entre 1 y 100." << endl << endl;
        } else {
            return totalDatos;
        }
    }
}

double solicitarParametro(string nombreParametro) {
    double valor;
    while (true) {
        cout << " Ingrese valor para " << nombreParametro << ": ";
        cin >> valor;
        if (cin.fail()) {
            cin.clear();
            while (cin.get() != '\n');
            cout << "   [ERROR] Debe ingresar un numero valido.\n";
        } else {
            return valor;
        }
    }
}
void capturarDatos(double datosX[], double datosY[], int totalDatos) {
    for (int k = 0; k < totalDatos; k++) {
        while (true) {
            cout << " Fila [" << (k + 1) << "] - Ingrese valor de X: ";
            cin >> datosX[k];
            if (cin.fail()) {
                cin.clear(); 
				while (cin.get() != '\n');
                cout << "   [ERROR] El valor debe ser un numero decimal o entero.\n";
            } else {
            	break;
			}
        }

        while (true) {
            cout << " Fila [" << (k + 1) << "] - Ingrese valor de Y esperado: ";
            cin >> datosY[k];
            if (cin.fail()) {
                cin.clear(); 
				while (cin.get() != '\n');
                cout << "   [ERROR] El valor debe ser un numero decimal o entero.\n";
            } else {
            	break;
			}
        }
        cout << "-----------------------------------------------------\n";
    }
}

int entrenarRed(double datosX[], double datosY[], int totalDatos, double &peso, double &sesgo, double tasaAprendizaje) {
    double errorAnterior = 100000.0;
    int contadorIteraciones = 0;
    bool continuar = true;

    while (continuar && contadorIteraciones < 2000) {
        contadorIteraciones++;
        double sumaErroresCuadrados = 0.0;

        for (int j = 0; j < totalDatos; j++) {
            double errorFila = ((peso * datosX[j]) + sesgo) - datosY[j]; 
            sumaErroresCuadrados += (errorFila * errorFila); 

            peso -= (2.0 * tasaAprendizaje * errorFila * datosX[j]); 
            sesgo -= (2.0 * tasaAprendizaje * errorFila); 
        }

        double mseActual = sumaErroresCuadrados / totalDatos;
        
        if((errorAnterior - mseActual) < 0.000001) continuar = false;
        errorAnterior = mseActual;
    }
    return contadorIteraciones;
}

void mostrarTablaDatos(double datosX[], double datosY[], int totalDatos, int contadorIteraciones){
    cout << " TABLA DE DATOS ORIGINAL:" << endl;
    cout << " X\tY" << endl;
    cout << " ----------" << endl;
    for (int k = 0; k < totalDatos; k++) {
        cout << " " << datosX[k] << "\t" << datosY[k] << endl;
    }
    cout << endl << "La red fue entrenada en " << contadorIteraciones << " iteraciones." << endl;
}

void simularPasoAPaso(double datosX[], double datosY[], int totalDatos, int contadorIteraciones, double pesoInicial, double sesgoInicial, double tasaAprendizaje) {
    double pesoSimulacion = pesoInicial;
    double sesgoSimulacion = sesgoInicial;
    int iteracionesAMostrar = (contadorIteraciones < 3) ? contadorIteraciones : 3;

    cout << " SIMULACION MATEMATICA :" << endl;

    for (int i = 0; i < iteracionesAMostrar; i++) {
        cout << endl << " --- ITERACION COMPLETA NUMERO " << (i + 1) << " ---" << endl;
        cout << "  y\tw\tb\ta\tE" << endl;
        cout << "  -----------------------------------------" << endl;

        for (int j = 0; j < totalDatos; j++) {
            double prediccionA = (pesoSimulacion * datosX[j]) + sesgoSimulacion; 
            double errorFila = prediccionA - datosY[j];

            cout << "  " << datosY[j] << "\t" << pesoSimulacion << "\t" << sesgoSimulacion << "\t" << prediccionA << "\t" << errorFila << endl;

            pesoSimulacion -= (2.0 * tasaAprendizaje * errorFila * datosX[j]);
            sesgoSimulacion -= (2.0 * tasaAprendizaje * errorFila);
        } 
    } 
}
void realizarPrediccion(double peso, double sesgo) {
    double xUsuario;
    while (true) {
        cout << " PREDICCION: " << endl;
        cout << " Ingrese cualquier numero para X (decimal o entero): " << endl;
        cout << " -> ";
        cin >> xUsuario;

        if (cin.fail()) {
            cin.clear(); 
			while (cin.get() != '\n');
            cout << " [ERROR] Entrada invalida. Debe ser estrictamente un numero." << endl << endl;
        } else {
            break;
		}
    }
    cout << " --> El valor calculado de Y es: " << (peso * xUsuario) + sesgo << endl;
}
