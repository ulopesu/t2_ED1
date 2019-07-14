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
#include "Hash.h"

ListaMudas *PegaListaMudas(Celula** Hash, int chavebusca) {
    return Hash[chavebusca]->mudas;
}

Muda *PegaMuda(ListaMudas *lm, int idm) {
    Muda *aux = lm->pri, *aux2 = NULL;
    if (lm != NULL) {
        for (aux = lm->pri; lm->pri != NULL; lm->pri = lm->pri->prox) {
            if (lm->pri->idm == idm) {
                aux2 = lm->pri;
                lm->pri = aux;
                return aux2;
            }
        }
        lm->pri = aux;
        return aux2;
    } else {
        return NULL;
    }
}

int IdMudaExiste(int idm, ListaMudas *lm) {
    Muda *aux;
    if (lm->pri == NULL) {
        return 0;
    } else {
        for (aux = lm->pri; lm->pri != NULL; lm->pri = lm->pri->prox) {
            if (lm->pri->idm == idm) {
                lm->pri = aux;
                return 1;
            }
        }
        lm->pri = aux;
    }
    return 0;
}

ListaMudas *CriaListaMudas() {
    ListaMudas *lm;
    lm = (ListaMudas*) malloc(sizeof (ListaMudas));
    lm->pri = NULL;
    lm->ult = NULL;
    return lm;
}

void InserirMuda(ListaMudas *lm, Arv *arv) {
    Muda *novo;

    novo = (Muda*) malloc(sizeof (Muda));
    novo->idm = arv->id_ramo;
    novo->arvore = arv;

    // INSERIR NA LISTA VAZIA
    if (lm->pri == NULL && lm->ult == NULL) {
        novo->prox = NULL;
        lm->pri = novo;
        lm->ult = novo;
    }// INSERIR EM LISTA NAO VAZIA.  
    else {
        novo->prox = NULL;
        lm->ult->prox = novo;
        lm->ult = novo;
    }
}

ListaMudas *LiberaListaMudas(ListaMudas *lm) {
    Muda *aux;
    if (lm != NULL) {
        while (lm->pri != NULL) {
            aux = lm->pri->prox;
            lm->pri->arvore = LiberaArv(lm->pri->arvore);
            free(lm->pri);
            lm->pri = aux;
            if (aux == NULL) {
                lm->ult = NULL;
            }
        }
        free(lm);
    }
    return NULL;
}

ListaMudas *ExcluirMuda(ListaMudas *lm, int idm) {
    Muda *aux = NULL, *aux2 = lm->pri;

    for (aux = lm->pri; lm->pri != NULL; aux2 = lm->pri, lm->pri = lm->pri->prox) {
        // APAGANDO DE LISTA DE UNICO ELEMENTO.
        if (idm == lm->pri->idm && lm->pri == lm->ult && aux == lm->pri) {
            lm->pri->arvore = LiberaArv(lm->pri->arvore);
            free(lm->pri);
            lm->pri = NULL;
            lm->ult = NULL;
            return lm;
        }// APAGANDO NO COMECO DA LISTA.
        else if (idm == lm->pri->idm && aux2 == lm->pri) {
            aux = aux->prox;
            lm->pri->arvore = LiberaArv(lm->pri->arvore);
            free(lm->pri);
            lm->pri = aux;
            return lm;
        }// APAGANDO NO MEIO DA LISTA.
        else if (idm == lm->pri->idm && lm->pri != lm->ult && lm->pri != aux) {
            aux2->prox = lm->pri->prox;
            lm->pri->arvore = LiberaArv(lm->pri->arvore);
            free(lm->pri);
            lm->pri = aux;
            return lm;
        }// APAGANDO NO FINAL DA LISTA.
        else if (idm == lm->pri->idm && lm->pri == lm->ult && aux != lm->pri) {
            aux2->prox = NULL;
            lm->ult = aux2;
            lm->pri->arvore = LiberaArv(lm->pri->arvore);
            free(lm->pri);
            lm->pri = aux;
            return lm;
        }
    }
    return lm;
}

/* GERA O ID DE CADA RAMO, SENDO:
- DIREITA = (ID DO PAI X 2);
- ESQUERDA = (ID DO PAI X 2 +1); */
int GeraIdRamo(int idrp, int dir) {
    if (dir == 0) {
        return idrp * 2;
    } else if (dir == 1) {
        return (idrp * 2) + 1;
    }
}

// RETORNA 1 PARA NÚMEROS PARES E 0 PARA IMPARES 

int EhPar(int n) {
    if (n % 2 == 0) {
        return 1;
    } else {
        return 0;
    }
}

int InserirPassageiro(int idp, int idt, Sistema *sys, FILE *fileout) {
    int cont1, aux;
    Muda *muda;
    Arv *arv;
    Pessoa *p;
    Indv *indv;

    p = PegaPessoaLista(sys->lps, idp);
    if (p == NULL) {
        fprintf(fileout, "\nERRO: ID DE PESSOA INEXISTENTE");
        return 0;
    }

    aux = idt;

    while (aux >= 1) {
        for (cont1 = 0; cont1 < tam; cont1++) {
            if (sys->Hash[cont1]->mudas != NULL) {
                muda = PegaMuda(sys->Hash[cont1]->mudas, aux);
                if (muda != NULL) {
                    indv = BuscaIndvArv(muda->arvore, idp);
                    if (indv != NULL) {
                        fprintf(fileout, "\n\nERRO: ESTE PESSAGEIRO JA EXISTE NESTE AVIAO");
                        return 0;
                    }
                    arv = BuscaRamo(muda->arvore, idt);
                    if (!ArvVazia(arv)) {
                        if ((ArvVazia(arv->dir) || ArvVazia(arv->esq)) && arv->nivel < 4) {
                            if (ArvVazia(arv->dir)) {
                                arv->dir = CriaRamo(GeraIdRamo(arv->id_ramo, 0), p->id, p->nome, arv->nivel + 1);
                                return 1;
                            } else if (ArvVazia(arv->esq)) {
                                arv->esq = CriaRamo(GeraIdRamo(arv->id_ramo, 1), p->id, p->nome, arv->nivel + 1);
                                return 1;
                            }
                        } else {
                            fprintf(fileout, "\n\nERRO: NAO EH POSSIVEL INSERIR NESTE TRIPULANTE");
                            return 0;
                        }
                    } else {
                        fprintf(fileout, "\n\nERRO: ID DE TRIPULANTE INEXISTENTE");
                        return 0;
                    }
                }
            }
        }
        if (aux != 1) {
            if (EhPar(aux)) {
                aux = aux / 2;
            } else {
                aux = (aux - 1) / 2;
            }
        } else {
            aux = -1;
        }
    }
    return 0;
}

int CriaChave(int n) {
    return n % tam;
}

void InserirArvHash(Celula** Hash, Arv* arv) {
    int chavebusca, cont1 = 0;

    chavebusca = CriaChave(arv->id_ramo);

    for (cont1 = 0; cont1 < tam; cont1++) {
        if (Hash[cont1]->chave == chavebusca) {
            InserirMuda(Hash[cont1]->mudas, arv);
        }
    }
}

Celula** CriaHash(ListaPessoas *lp) {
    int i = 0, chavebusca;
    Arv *a;
    a = IniciaArv();
    Celula** Hash;

    Hash = (Celula**) malloc(tam * sizeof (Celula));

    for (i = 0; i < tam; i++) {
        Hash[i] = (Celula*) malloc(sizeof (Celula));
        Hash[i]->mudas = CriaListaMudas();
    }

    for (i = 0; i < tam; i++) {
        Hash[i]->chave = CriaChave(i);
    }

    InserirPessoaLista(lp, 0, "PAIDETODOS");
    a = CriaRamo(1, lp->pri->id, lp->pri->nome, 1);

    chavebusca = CriaChave(a->id_ramo);
    InserirMuda(PegaListaMudas(Hash, chavebusca), a);

    return Hash;
}

Celula** LiberaHash(Celula* Hash[tam]) {
    int i;
    for (i = 0; i < tam; i++) {
        Hash[i]->mudas = LiberaListaMudas(Hash[i]->mudas);
        free(Hash[i]);
    }
    free(Hash);
    return NULL;
}

void InserirPessoaHash(Sistema *sys, FILE *fileinp, FILE *fileout) {
    int verro1 = 0, idp, idt, verro2 = 0;
    char comando[20];
    
    fprintf(fileout, "\n\n");
    fprintf(fileout, "\nDigite o ID da PESSOA que deseja inserir e o ID do "
            "TRIPULANTE em que esta pessoa sera inserida.\nExemplo: 3 1");
    fscanf(fileinp, "%d %d", &idp, &idt);
    fscanf(fileinp, "\n");
    fprintf(fileout, "\nDigitado: %d %d", idp, idt);
    
    while (!verro1) {
        verro1 = InserirPassageiro(idp, idt, sys, fileout);
        if (verro1) {
            verro2 = 1;
        }
        if (!verro1) {
            fprintf(fileout, "\nAinda desseja inserir algum passageiro? Digite:"
                    "sim ou nao.");
            fscanf(fileinp, "%[^\n]", comando);
            fscanf(fileinp, "\n");
            fprintf(fileout, "\nDigitado: %s", comando);
            if (!strcmp(comando, "sim") || !strcmp(comando, "SIM") || !strcmp(comando, "Sim")) {
                fprintf(fileout, "\nDigite o ID da PESSOA que deseja inserir e o ID do "
                        "TRIPULANTE em que esta pessoa sera inserida.\nExemplo: 3 1");
                fscanf(fileinp, "%d %d", &idp, &idt);
                fscanf(fileinp, "\n");
                fprintf(fileout, "\nDigitado: %d %d", idp, idt);
            } else {
                verro1 = 1;
            }
        }
    }
    if (verro2) {
        fprintf(fileout, "\nPessoa inserida com sucesso!");
    }
}

Indv *PegaIndvHash(Celula **Hash, int idp) {
    int cont1 = 0;
    ListaMudas *lm;
    Muda *aux, *m;
    Indv *indv;
    
    for (cont1 = 0; cont1 < tam; cont1++) {
        lm = Hash[cont1]->mudas;
        if (lm != NULL) {
            for (aux = lm->pri; lm->pri != NULL; lm->pri = lm->pri->prox) {
                m = lm->pri;
                if (m->arvore != NULL) {
                    indv = BuscaIndvArv(m->arvore, idp);
                    lm->pri = aux;
                    return indv;
                }
            }
            lm->pri = aux;
        }
    }
    return NULL;
}

void ExibirHash(Celula** Hash, FILE *fileout){
    int cont;
    ListaMudas *lm;
    Muda *aux;
    for(cont = 0; cont < tam; cont++){
        lm = Hash[cont]->mudas;
        for(aux = lm->pri; lm->pri != NULL; lm->pri = lm->pri->prox){
            ImprimeArv(lm->pri->arvore, fileout);
        }
        lm->pri = aux;
    }
}
