/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Arvore.h
 * Author: ulopesu
 *
 * Created on 17 de Novembro de 2016, 09:53
 */
#include "Administrador.h"

#ifndef ARVORE_H
#define ARVORE_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct Indv {
        int id;
        char *nome;
    } Indv;

    typedef struct Arv {
        int id_ramo;
        int nivel;
        struct Indv *membro;
        struct Arv* esq;
        struct Arv* dir;
    } Arv;

    Arv* IniciaArv();
    Arv* CriaRamo(int idr, int idp, char nome[100], int nivel);
    int ArvVazia(Arv *a);
    int ArvCheia(Arv *a);
    void ImprimeArv(Arv *a, FILE *fileout);
    Arv* LiberaArv(Arv *a);
    Arv* BuscaRamo(Arv *a, int idr); 
    Indv* BuscaIndvArv(Arv *a, int idm);
    void AtualizaNivelArvore(Arv *a);

#ifdef __cplusplus
}
#endif

#endif /* ARVORE_H */

