/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Administrador.h
 * Author: ulopesu
 *
 * Created on 17 de Novembro de 2016, 09:52
 */

#include "Hash.h"

#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H

#include "Arvore.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    typedef struct Pessoa {
        int id;
        char *nome;
        struct Pessoa *prox;
    } Pessoa;

    typedef struct ListaPessoas {
        struct Pessoa *pri;
        struct Pessoa *ult;
    } ListaPessoas;

    typedef struct Sistema {
        struct ListaPessoas *lps;
        struct Celula** Hash;
    } Sistema;

    Pessoa *PegaPessoaLista(ListaPessoas *p, int idp);
    int IdPessoaExiste(int idp, ListaPessoas *p);
    ListaPessoas *CriaListaPessoas();
    void InserirPessoaLista(ListaPessoas *p, int idp, char *nome);
    ListaPessoas *LiberaListaPessoas(ListaPessoas *p);
    ListaPessoas *ExcluirPessoaLista(ListaPessoas *p, int id);
    Sistema* CriaSistema();
    Sistema* LiberaSistema(Sistema* sys);
    void IncluirPessoa(ListaPessoas *lp, FILE *fileinp, FILE *fileout);
    void AtualizarSistema(Sistema *system);
    void IniciaSistema(Sistema *sys, FILE *fileinp, FILE *fileout);
    void ExcluirPessoa(Sistema *sys, FILE *fileinp, FILE *fileout);
    


#ifdef __cplusplus
}
#endif

#endif /* ADMINISTRADOR_H */

