/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Arvore.h"
#include "Administrador.h"

Arv* IniciaArv() {
    return NULL;
}

Arv* CriaRamo(int idr, int idp, char nome[100], int nivel) {
    Arv* a = (Arv*) malloc(sizeof (Arv));
    a->id_ramo = idr;
    a->nivel = nivel;
    a->membro = (Indv*) malloc(sizeof (Indv));
    a->membro->id = idp;
    a->membro->nome = strdup(nome);
    a->esq = NULL;
    a->dir = NULL;
    return a;
}

int ArvVazia(Arv *a) {
    return a == NULL;
}

int ArvCheia(Arv *a) {
    if (!ArvVazia(a)) {
        if (a->nivel == 3 && !ArvVazia(a->dir) && !ArvVazia(a->esq)) {
            return 1;
        } else {
            return ArvCheia(a->dir) && ArvCheia(a->esq);
        }
    } else {
        return 0;
    }
}

void ImprimeArv(Arv *a, FILE *fileout) {
    if (!ArvVazia(a)) {
        if ((ArvVazia(a->dir) || ArvVazia(a->esq)) && a->nivel < 4) {
            fprintf(fileout, "\n%d", a->id_ramo);
        }
        ImprimeArv(a->dir, fileout);
        ImprimeArv(a->esq, fileout);
    }
}

Arv* LiberaArv(Arv *a) {
    if (!ArvVazia(a)) {
        if (a->membro != NULL) {
            if (a->membro->nome != NULL) {
                free(a->membro->nome);
                a->membro->nome = NULL;
            }
            free(a->membro);
            a->membro = NULL;
        }
        LiberaArv(a->esq);
        LiberaArv(a->dir);
        free(a);
        a = NULL;
    }
    return a;
}

Arv* BuscaRamo(Arv *a, int idr) {
    if (ArvVazia(a))
        return NULL;
    else if (a->id_ramo == idr) {
        return a;
    } else {
        if (BuscaRamo(a->esq, idr) != NULL) {
            return BuscaRamo(a->esq, idr);
        } else if (BuscaRamo(a->dir, idr) != NULL) {
            return BuscaRamo(a->dir, idr);
        } else {
            return NULL;
        }
    }
}

Indv* BuscaIndvArv(Arv *a, int idm) {
    if (ArvVazia(a))
        return NULL; /* Arvore vazia: nao encontrou */
    else if (a->membro->id == idm) {
        return a->membro;
    } else {
        if (BuscaIndvArv(a->esq, idm) != NULL) {
            return BuscaIndvArv(a->esq, idm);
        } else if (BuscaIndvArv(a->dir, idm) != NULL) {
            return BuscaIndvArv(a->dir, idm);
        } else {
            return NULL;
        }
    }
}

void AtualizaNivelArvore(Arv *a) {
    if (!ArvVazia(a)) {
        a->nivel = a->nivel - 1;
        AtualizaNivelArvore(a->dir);
        AtualizaNivelArvore(a->esq);
    }
}