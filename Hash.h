/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Hash.h
 * Author: ulopesu
 *
 * Created on 17 de Novembro de 2016, 09:53
 */

#define tam 10

#ifndef HASH_H
#define HASH_H


#include "Administrador.h"
#include "Arvore.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct Muda {
        int idm;
        struct Arv *arvore;
        struct Muda *prox;
    } Muda;

    typedef struct ListaMudas {
        struct Muda *pri;
        struct Muda *ult;
    } ListaMudas;

    typedef struct Celula {
        int chave;
        struct ListaMudas *mudas;
    } Celula;
    
    Muda *PegaMuda(ListaMudas *lm, int idm);
    int IdMudaExiste(int idm, ListaMudas *lm);
    ListaMudas* CriaListaMudas();
    void InserirMuda(ListaMudas *lm, Arv *arv);
    ListaMudas *LiberaListaMudas(ListaMudas *m);
    ListaMudas *ExcluirMuda(ListaMudas *lm, int idm);
    int GeraIdRamo(int idrp, int dir);
    int EhPar(int n);
    int InserirPassageiro(int idp, int idt, Sistema *sys, FILE *fileout);
    int CriaChave(int n);
    void InserirArvHash(Celula** Hash, Arv* arv);
    Celula** CriaHash(ListaPessoas *lp);
    Celula** LiberaHash(Celula* Hash[tam]);
    void InserirPessoaHash(Sistema *sys, FILE *fileinp, FILE *fileout);
    Indv *PegaIndvHash(Celula **Hash, int idp);
    void ExibirHash(Celula** Hash, FILE *fileout);
    
    
#ifdef __cplusplus
}
#endif

#endif /* HASH_H */

