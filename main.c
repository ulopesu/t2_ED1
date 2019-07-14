/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: ulopesu
 *
 * Created on 17 de Novembro de 2016, 09:47
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Administrador.h"
#include "Arvore.h"
#include "Hash.h"

/*
 * 
 */
int main(int argc, char** argv) {
    Sistema *system;
    char dirinp[200], dirout[200];
    FILE *fileinp, *fileout;

    if (argc < 3) {
        printf("ERRO: Algum diretorio de arquivos nao foi informado!");
        return 1;
    }

    strcpy(dirinp, "../../../input/");
    strcpy(dirout, "../../../output/");
    strcat(dirinp, argv[1]);
    strcat(dirout, argv[2]);

    fileinp = fopen(dirinp, "r");
    fileout = fopen(dirout, "w");

    if (fileinp == NULL) {
        printf("\nNao foi possivel ler o arquivo de entrada\n");
        return 1;
    }
   
    system = CriaSistema();
    IniciaSistema(system, fileinp, fileout);

    fclose(fileinp);
    fclose(fileout);

    system = LiberaSistema(system);

    return 0;
}

