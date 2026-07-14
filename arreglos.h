#ifndef ARREGLOS_H
#define ARREGLOS_H
#include <iostream>
using namespace std;


//
void Ejercicio1();
int solicitarTotalDatos();
void capturarDatos(double datosX[], double datosY[], int totalDatos);
double solicitarParametro(string nombreParametro);
int entrenarRed(double datosX[], double datosY[], int totalDatos, double &peso, double &sesgo, double tasaAprendizaje);
void mostrarTablaDatos(double datosX[], double datosY[], int totalDatos, int contadorIteraciones);
void simularPasoAPaso(double datosX[], double datosY[], int totalDatos, int contadorIteraciones, double pesoInicial, double sesgoInicial, double tasaAprendizaje);
void realizarPrediccion(double peso, double sesgo);
//
int Ejercicio2();
double f(double x, int opcion);
double derivada(double x, int opcion);
double buscarValorInicial(int opcion, bool &raiz);
double newtonRaphson(double x0, int opcion);
//
int Ejercicio3();
int menu();
void ingresarDatos(double matriz[][5], int incognitas, char variables[]);
void verificarPivote(double matriz[][5], int incognitas, int fila);
void eliminacionGauss(double matriz[][5], int incognitas);
int verificarSistema(double matriz[][5], int incognitas);
void sustitucionAtras(double matriz[][5], double solucion[], int incognitas);
void mostrarSolucion(double solucion[], int incognitas, char variables[]);

#endif
