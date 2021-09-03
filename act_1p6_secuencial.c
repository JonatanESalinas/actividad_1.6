/*
    Actividad 1.6 Multiprocesadores
    Programa secuencial

    Jonatan Emanuel Salinas Avila       A01731815
    3/Sept/2021
*/

#include<stdio.h>
#include <math.h>
#include "omp.h"

#define PI 3.14159265

static long mi_N = 50000;

double function1(double ti, double wi){
    return ( (ti*exp(3*ti)) - (2*wi) );
}

double function2(double ti, double wi){
    return ( 1 + pow(ti-wi,2) );
}

double function3(double ti, double wi){
    return ( 1 + (wi/ti) );
}

double function4(double ti, double wi){
    return ( cos(2*ti*wi) + sin(3*ti*wi) );
}

void rungekuta(int valor_n, char * nombre_file, int que_ecuacion){
        
    FILE * fptr;
    
    long N = valor_n;
    fptr=fopen(nombre_file,"w");

    fprintf(fptr, "Datos que encuentra el metodo de Rungecuta(variable ind.\t variable dep.\t numero de thread)\n");
    double h,t,w;
    double w0=PI/4,a=0,b=PI;
    int i;
    w=w0;

    fprintf(fptr, "%f\t %f\n", a, w);
    for(i=0;i<N;i++){
        h=(b-a)/N;
        t=a+(h*i);

        if(que_ecuacion == 1){
            double k1 = h*(function1(t, w));
            double k2 = h*(function1(t + (h/2.0), w + (k1/2.0)) );
            double k3 = h*(function1(t + (h/2.0), w + (k2/2.0)) ); 
            double k4 = h*(function1(t + h, w + k3));
            w = w + (1.0/6.0)*(k1 + 2*k2 + 2*k3 + k4);
        }
        else if(que_ecuacion == 2){
            double k1 = h*(function2(t, w));
            double k2 = h*(function2(t + (h/2.0), w + (k1/2.0)) );
            double k3 = h*(function2(t + (h/2.0), w + (k2/2.0)) ); 
            double k4 = h*(function2(t + h, w + k3));
            w = w + (1.0/6.0)*(k1 + 2*k2 + 2*k3 + k4);
        }
        else if(que_ecuacion == 3){
            double k1 = h*(function3(t, w));
            double k2 = h*(function3(t + (h/2.0), w + (k1/2.0)) );
            double k3 = h*(function3(t + (h/2.0), w + (k2/2.0)) ); 
            double k4 = h*(function3(t + h, w + k3));
            w = w + (1.0/6.0)*(k1 + 2*k2 + 2*k3 + k4);
        }
        else if(que_ecuacion == 4){
            double k1 = h*(function4(t, w));
            double k2 = h*(function4(t + (h/2.0), w + (k1/2.0)) );
            double k3 = h*(function4(t + (h/2.0), w + (k2/2.0)) ); 
            double k4 = h*(function4(t + h, w + k3));
            w = w + (1.0/6.0)*(k1 + 2*k2 + 2*k3 + k4);
        }

        fprintf(fptr, "%f\t %f \t numero de thread:%d\n", t+h, w,omp_get_thread_num());
    }

    fclose(fptr);
}


int main()
{
    char nombre1[15] = "Runge1_sec.txt";
    char nombre2[15] = "Runge2_sec.txt";
    char nombre3[15] = "Runge3_sec.txt";
    char nombre4[15] = "Runge4_sec.txt";   

    const double startTime = omp_get_wtime();

    rungekuta(mi_N, nombre1, 1);
    rungekuta(mi_N, nombre2, 2);
    rungekuta(mi_N, nombre3, 3);
    rungekuta(mi_N, nombre4, 4);

    const double endTime = omp_get_wtime();
    printf("tomo (%lf) segundos\n", (endTime -startTime));

}