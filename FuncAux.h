/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FuncAux.h
 * Author: Jhenny Cervera Vargas(20182841)
 *
 * Created on 3 de junio de 2020, 20:57
 */

#ifndef FUNCAUX_H
#define FUNCAUX_H

void LeerAsistencia(int,int ,int*,int *, int*,double*, int*);
void CalcularEncuestaReal(int ,int ,int*, int*,double*, int);
void CalcularEncuestaAjustada(double*,double* ,double *,int );
double fFactor(double *,int );
void ImprimirRep1(int aaI,int cicloI,int *codCurs,int*cant_Alum,int*cant_Horar,double*promAsist,
                        double *porcReal,double*porcAjust, int numCurs);
void OrdenarDatos(int *codCurs,int*cant_Alum,int*cant_Horar,double*promAsist,
                        double *porcReal,double*porcAjust, int numCurs);
void intercambiarD(double* ,int ,int );
void ImprimLin(FILE *, int , char );
void intercambiarI(int *,int  ,int );

#endif /* FUNCAUX_H */

