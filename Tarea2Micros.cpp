// Se incluye las bibliotecas 
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <pthread.h>
#include <cmath>
#include <chrono>


//  se incluye str y std::chrono automaticamente
using namespace std;
using namespace std::chrono;


int numeros[4000000]; // Define el arreglo de tamaño de 4000000 donde se almacenaran los numeros del 0 al 3999999
double potencias[4000000]; // Define el arreglo de tamaño donde se almacenaran las potencias del arreglo numeros


// Funcion que almacena en el arreglo de entrada los numeros del 0 al 3999999
void arreglo_inicial(int arreglo[]){
    for(int i=0;i<4000000;i++){
        numeros[i] = i;
    }
}

// Funcion que crea los valores por almacenar en el arreglo de potencias
void *potenciahilo(void *arg){
	int  pos = *((int *)arg); // Crea una variable en donde el argumento introducido la funcion pasa a ser de tipo int
	// Se definen los diferentes casos dependiendo del hilo o la cantidad de hilos
	switch(pos){
	// El caso 0 es para cuando se desea hacer el recorrido con un unico hilo en este caso se almacenan en potencias los valores de las potencias del 0 al 3,999,999
	case 0: 
		for(int i=0;i<4000000;i++){
        		potencias[i] = pow(numeros[i], 2); // Se calcula la potencia de numeros posicion i y se almacena en potencias posicion i
		}
		pthread_exit(0); // sale del hilo
	// Los casos del 1 al 4 son para cuando se trabaja con 4 hilos, asignando los intervalos correspondientes a cada hilo
	// El caso 1 asigna el intervalo de trabajo para el hilo 1, trabaja los numeros del 0 al 999,999
	case 1:
		for(int i=0;i<1000000;i++){
        		potencias[i] = pow(numeros[i], 2);
		}
		pthread_exit(0); // sale del hilo
	// El caso 2 asigna el intervalo de trabajo para el hilo 2, trabaja los numeros del 1,000,000 al 1,999,999
	case 2:
		for(int i=1000000;i<2000000;i++){
        		potencias[i] = pow(numeros[i], 2);
		}
		pthread_exit(0); // sale del hilo
	// El caso 3 asigna el intervalo de trabajo para el hilo 3, trabaja los numeros del 2,000,000 al 2,999,999
	case 3: 
		for(int i=2000000;i<3000000;i++){
        		potencias[i] = pow(numeros[i], 2);
		}
		pthread_exit(0); // sale del hilo
	// El caso 4 asigna el intervalo de trabajo para el hilo 4, trabaja los numeros del 3,000,000 al 3,999,999
	case 4:
		for(int i=3000000;i<4000000;i++){
        		potencias[i] = pow(numeros[i], 2);
		}
		pthread_exit(0); // sale del hilo
	// El caso por defecto se corre en caso de que se presente algun problema
	default:
		cout << "El programa no se ejecutó correctamente." << endl;
	}
}

//Se define el programa principal
int main(){
    pthread_t hilo0, hilo1, hilo2, hilo3, hilo4; // Se crean las variables de tipo pthread_t correspondientes a cada hilo
    arreglo_inicial(numeros); //Crea en el arreglo numeros los numeros del 0 al 3,999,999
	// Se crean los valores del argumento para cada hilo, con los cuales se identificaran en la funcion de potenciahilo
    int a = 0;
    int b = 1;
    int c = 2;
    int d = 3;
    int e = 4;

    auto t0 = high_resolution_clock::now(); // Toma el valor actual del tiempo, antes de ejecutar el programa con un hilo

    pthread_create(&hilo0,NULL, potenciahilo, &a); // Crea el hilo cero y lo asocia al argumento a, correspondiente a la ejecucion con un solo hilo
    pthread_join(hilo0, NULL); // Espera a que acabe la ejecucion del hilo 0

    auto t1 = high_resolution_clock::now(); // Toma el valor actual del tiempo, al finalizar la ejecucion del programa con un hilo e inicia la ejecucion con 4 hilos

	//Crea los hilos correspondientes a la ejecucion con 4 hilos
    pthread_create(&hilo1, NULL, potenciahilo, &b);
    pthread_create(&hilo2, NULL, potenciahilo, &c);
    pthread_create(&hilo3, NULL, potenciahilo, &d);
    pthread_create(&hilo4, NULL, potenciahilo, &e);

	//Espera a que termine la ejecucion de cada uno de los hilos (1, 2, 3 y 4)
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);
    pthread_join(hilo3, NULL);
    pthread_join(hilo4, NULL);

    auto t2 = high_resolution_clock::now(); // Toma el valor actual del tiempo, al finalizar la ejecucion del programa con 4 hilos

    auto duracion1 = duration_cast<microseconds>(t1 - t0); // Determina el lapso entre el inicio y la finalizacion de la ejecucion con un hilo
    auto duracion4 = duration_cast<microseconds>(t2 - t1); // Determina el lapso entre el inicio y la finalizacion de la ejecucion con 4 hilos

	// Muestra en pantalla los tiempos de ejecucion para cada recorrido
    cout << "Tiempo de ejecucion 1 hilo: " << duracion1.count() << "microsegundos" << endl;
    cout << "Tiempo de ejecucion 4 hilos: " << duracion4.count()  << "microsegundos" << endl;

	return 1;
}