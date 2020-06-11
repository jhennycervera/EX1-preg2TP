/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

//Author: Jhenny Cervera Vargas(20182841)     

#include <stdio.h>
#include <stdlib.h>
#include "FuncAux.h"

#define MAX_LIN 80

void LeerAsistencia(int aaI, int cicloI,int*codCurs,int *cant_Horar, int*cant_Alum,double*promAsist, int*numCurs){
    
    FILE*archAsist;
    archAsist=fopen("Asistencia_clases.txt", "r");
    if(archAsist==NULL){
        printf("No se puede abrir el archivo Asistencia_clases.txt\n");
        exit(1);
    }
    (*numCurs)=0;
    int aa,ciclo,curso, horario, numMatr, pos, flag=0;
    double aux, asistencia;
    while(1){
        fscanf(archAsist, "%d %d %d %d %d %lf",&aa,&ciclo,&curso,&horario, &numMatr, &asistencia);
        if(feof(archAsist)) break;
        if(aa ==aaI &&  cicloI==ciclo){
            pos=busquedaSec(curso,codCurs,*numCurs);
            if(pos!=-1){
               cant_Horar[pos]++;
               
               if(cant_Horar[pos]==2) aux=promAsist[pos] + (numMatr*asistencia);
               else aux=(promAsist[pos] *(cant_Alum[pos])) + (numMatr*asistencia);
               cant_Alum[pos]+=numMatr;  // se pone aca porque necesito la cant de matriculados anterior
               promAsist[pos]= aux /(double)cant_Alum[pos];  
            }
            else{
                //nuevo curso
                codCurs[*numCurs]=curso;
                cant_Horar[*numCurs]++;
                cant_Alum[*numCurs]+=numMatr;
                promAsist[*numCurs]=(numMatr*asistencia);
                (*numCurs)++; 
            }
        }
    }
    fclose(archAsist);
}

int busquedaSec(int dato, int* arr, int numArr){

    for(int i=0; i<numArr; i++){
	if(dato==arr[i]) return i;
    }
    return -1;
}

 void CalcularEncuestaReal(int aaI,int cicloI,int*codCurs, int*cant_Horar,double* porcReal, int numCurs){
     
    FILE* archEnc;
    archEnc=fopen("Encuestas_Alumnos.txt", "r");
    if(archEnc==NULL){
        printf("ERROR: No se puede abrir el archivo Encuestas_Alumnos.txt\n");
        exit(1);
    }
    for(int i=0; i<numCurs; i++){
        cant_Horar[i]=0;
    } 
    //reseteo porq la cantidad de horarios es igual en los dos archivos
    int aa, ciclo,curso, pos, contVal;
    double valor, aux, promHor, sumValores=0;
    
    while(1){
        fscanf(archEnc, "%d %d %d %*d %*d/%*d/%*d", &aa, &ciclo,&curso);
        if(feof(archEnc)) break;
        if(aa==aaI && cicloI==ciclo){
            contVal=sumValores=0;
            pos=busquedaSec(curso,codCurs,numCurs);
            cant_Horar[pos]++;
            while(1){
                //Calculo el promedio de los valores por horario
                fscanf(archEnc, "%lf",&valor);
                    contVal++;
                    sumValores+=valor;
                    
                if(fgetc(archEnc)=='\n'){
                    //como son los mismos horarios, entonces siempre va a ver el horario crrespondiente
                    promHor=sumValores/(double)contVal;
                    if(cant_Horar[pos]==1) porcReal[pos]=promHor;
                    else{
                        aux=porcReal[pos] * (cant_Horar[pos]-1)+(promHor);
                        porcReal[pos]=aux/(double)cant_Horar[pos];
                    }
                    break;
                }
            }
        }
        else while(fgetc(archEnc)!='\n');
    }
    fclose(archEnc);
 }
 
 void CalcularEncuestaAjustada(double*porcAjust,double* promAsist,double *porcReal,int numCurs){
     double factor;
     for(int i=0; i<numCurs; i++){
        factor=fFactor(promAsist,i);
         porcAjust[i]=porcReal[i] * factor;
     } 
 }
 
 double fFactor(double *promAsist,int i){
     
     if(promAsist[i]>=90) return 1.0;
     if(promAsist[i]>=80 && promAsist[i]<90) return 1.05;
     if(promAsist[i]>=70 && promAsist[i]<80) return 1.08;
     if(promAsist[i]>=60 && promAsist[i]<70) return 1.11;
     if(promAsist[i]>=50 && promAsist[i]<60) return 1.13;
     else return 0;
     
 }
 
void ImprimirRep1(int aaI,int cicloI,int *codCurs,int*cant_Alum,int*cant_Horar,double*promAsist,
                        double *porcReal,double*porcAjust, int numCurs){
    FILE* archRep1;
    archRep1=fopen("REPORTE1.txt", "w");
    if(archRep1==NULL){
        printf("ERROR: No se puede abrir el archivo REPORTE1.txt\n");
        exit(1);
    }
    //imprimir cabecera
    fprintf(archRep1,"RESUMEN DE LA ASISTENCIA Y ENCUESTA DE ALUMNOS POR CURSO\n");
    fprintf(archRep1,"ANIO: %7d",aaI);
    fprintf(archRep1,"%15s: %d\n","CICLO",cicloI);
    ImprimLin(archRep1,MAX_LIN, '=');
    fprintf(archRep1,"%s %12s %12s %15s(%%) %15s(%%) %15s(%%)\n","CICLO","ALUMNOS", "HORARIOS","ASISTENCIA", "ENCUESTA REAL", "ENCUESTA AJUSTADA");
    ImprimLin(archRep1,MAX_LIN, '=');
    for(int i=0; i<numCurs; i++){
        fprintf(archRep1, "%d %12d %12d %15.2lf %15.2lf %15.2lf\n",codCurs[i],
               cant_Alum[i],cant_Horar[i],promAsist[i], porcReal[i],porcAjust[i]);
    }
    ImprimLin(archRep1,MAX_LIN, '=');
    fclose(archRep1);
    
 }
void OrdenarDatos(int *codCurs,int*cant_Alum,int*cant_Horar,double*promAsist,
                        double *porcReal,double*porcAjust, int numCurs){
    
    for(int i=0; i<numCurs-1; i++){
        for(int j=i+1; j<numCurs;j++){
            if(porcAjust[i]<porcAjust[j] || (porcAjust[i]==porcAjust[j] && promAsist[i]<promAsist[j])
             || (porcAjust[i]==porcAjust[j] && promAsist[i]==promAsist[j] && cant_Horar[i]<cant_Horar[j]))
             
            intercambiarI(codCurs,i, j);
            intercambiarI(cant_Alum, i, j);
            intercambiarI(cant_Horar, i, j);
            intercambiarD(promAsist,i ,j );
            intercambiarD(porcReal, i , j);
            intercambiarD(porcAjust, i , j);
        }
    }
    
}

void intercambiarD(double* arr,int i,int j){
    
    double aux;
    aux=arr[i];
    arr[i]=arr[j];
    arr[j]=aux;
}

void ImprimLin(FILE *arch, int cant, char c){
    for(int i=0; i<cant; i++){
        fprintf(arch, "%c", c);
    }
    fprintf(arch, "\n");
}

void intercambiarI(int *arr,int  i,int  j){
    
    int aux;
    aux=arr[i];
    arr[i]=arr[j];
    arr[j]=aux;
    
}
