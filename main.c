/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Jhenny Cervera Vargas(20182841)
 *
 * Created on 3 de junio de 2020, 20:57
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncAux.h"
#define MAX_CUR 100
/*
 * 
 */
int main(int argc, char** argv) {
    
    FILE* archRep;
    archRep=fopen("Resumen_Asitencia_Encuesta.txt", "w");
    if(archRep==NULL){
        printf("ERROR: No se puede abrir el archivo personas.txt\n");
        exit(1);
    }

    
    int aaI, cicloI;
    printf("Ingresar anho y ciclo\n");
    scanf("%d %d",&aaI, &cicloI);
    
    int codCurs[MAX_CUR]={},cant_Horar[MAX_CUR]={}, cant_Alum[MAX_CUR]={}, numCurs;
    double porcReal[MAX_CUR], promAsist[MAX_CUR]={}, porcAjust[MAX_CUR];
    //arr Segundo reporte
    int frecReal[MAX_CUR]={}, frecAjust[MAX_CUR]={};
    
    //ImprimCabecera();
    LeerAsistencia(aaI,cicloI,codCurs,cant_Horar,cant_Alum,promAsist,&numCurs);
    CalcularEncuestaReal(aaI,cicloI,codCurs,cant_Horar,porcReal, numCurs);
    CalcularEncuestaAjustada(porcAjust,promAsist,porcReal,numCurs);
    OrdenarDatos(codCurs,cant_Alum,cant_Horar,promAsist,porcReal,porcAjust, numCurs);
    ImprimirRep1(aaI,cicloI,codCurs,cant_Alum,cant_Horar,promAsist,porcReal,porcAjust, numCurs);
    fclose(archRep);
    return (EXIT_SUCCESS);
}

