/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Administrador.h"
#include "Hash.h"
#include "Arvore.h"

Pessoa *PegaPessoaLista(ListaPessoas *p, int idp) {
    Pessoa *aux = p->pri, *aux2 = NULL;
    if (p != NULL) {
        for (aux = p->pri; p->pri != NULL; p->pri = p->pri->prox) {
            if (p->pri->id == idp) {
                aux2 = p->pri;
                p->pri = aux;
                return aux2;
            }
        }
        p->pri = aux;
        return aux2;
    } else {
        return NULL;
    }
}

int IdPessoaExiste(int idp, ListaPessoas *p) {
    Pessoa *aux;

    if (p->pri == NULL) {
        return 0;
    } else {
        for (aux = p->pri; p->pri != NULL; p->pri = p->pri->prox) {
            if (p->pri->id == idp) {
                p->pri = aux;
                return 1;
            }
        }
        p->pri = aux;
    }
    return 0;
}

ListaPessoas *CriaListaPessoas() {
    ListaPessoas *p;
    p = (ListaPessoas*) malloc(sizeof (ListaPessoas));
    p->pri = NULL;
    p->ult = NULL;
    return p;
}

void InserirPessoaLista(ListaPessoas *lp, int idp, char *nome) {
    Pessoa *novo;

    novo = (Pessoa*) malloc(sizeof (Pessoa));
    novo->id = idp;
    novo->nome = strdup(nome);

    // INSERIR NA LISTA VAZIA
    if (lp->pri == NULL && lp->ult == NULL) {
        novo->prox = NULL;
        lp->pri = novo;
        lp->ult = novo;
    }// INSERIR EM LISTA NAO VAZIA.  
    else {
        novo->prox = NULL;
        lp->ult->prox = novo;
        lp->ult = novo;
    }
}

ListaPessoas *LiberaListaPessoas(ListaPessoas *p) {
    Pessoa *aux;
    if (p != NULL) {
        while (p->pri != NULL) {
            aux = p->pri->prox;
            free(p->pri->nome);
            free(p->pri);
            p->pri = aux;
            if (aux == NULL) {
                p->ult = NULL;
            }
        }
        free(p);
    }
    return NULL;
}

ListaPessoas *ExcluirPessoaLista(ListaPessoas *p, int idp) {
    Pessoa *aux = NULL, *aux2 = p->pri;

    for (aux = p->pri; p->pri != NULL; aux2 = p->pri, p->pri = p->pri->prox) {
        // APAGANDO DE LISTA DE ÃšNICO ELEMENTO.
        if (idp == p->pri->id && p->pri == p->ult && aux == p->pri) {
            free(p->pri->nome);
            free(p->pri);
            p->pri = NULL;
            p->ult = NULL;
            return p;
        }// APAGANDO NO COMECO DA LISTA.
        else if (idp == p->pri->id && aux2 == p->pri) {
            aux = aux->prox;
            free(p->pri->nome);
            free(p->pri);
            p->pri = aux;
            return p;
        }// APAGANDO NO MEIO DA LISTA.
        else if (idp == p->pri->id && p->pri != p->ult && p->pri != aux) {
            aux2->prox = p->pri->prox;
            free(p->pri->nome);
            free(p->pri);
            p->pri = aux;
            return p;
        }// APAGANDO NO FINAL DA LISTA.
        else if (idp == p->pri->id && p->pri == p->ult && aux != p->pri) {
            aux2->prox = NULL;
            p->ult = aux2;
            free(p->pri->nome);
            free(p->pri);
            p->pri = aux;
            return p;
        }
    }
    return p;
}

Sistema* CriaSistema() {
    Sistema* sys;
    sys = (Sistema*) malloc(sizeof (Sistema));
    sys->lps = CriaListaPessoas();
    sys->Hash = CriaHash(sys->lps);
    return sys;
}

Sistema* LiberaSistema(Sistema* sys) {
    sys->Hash = LiberaHash(sys->Hash);
    sys->lps = LiberaListaPessoas(sys->lps);
    free(sys);
    return NULL;
}

void IncluirPessoa(ListaPessoas *lp, FILE *fileinp, FILE *fileout) {
    int cont1 = 0, qtd = 0, id, verro1 = 1;
    char nome[100];
    fprintf(fileout, "\n\n");
    fprintf(fileout, "\nDigite a QUANTIDADE de pessoas que deseja inserir.");

    fscanf(fileinp, "%d", &qtd);
    fscanf(fileinp, "\n");

    fprintf(fileout, "\nDigitado: %d", qtd);

    for (cont1 = 0; cont1 < qtd; cont1++) {
        while (verro1) {
            fprintf(fileout, "\nDigite o ID da pessoa o seu NOME. Exemplo: 3 Jose Manuel");
            fscanf(fileinp, "%d %[^\n]", &id, nome);
            fscanf(fileinp, "\n");
            fprintf(fileout, "\nDigitado: %d %s", id, nome);

            if (IdPessoaExiste(id, lp)) {
                fprintf(fileout, "\n\nErro: ID digitado ja existe.");
            } else {
                InserirPessoaLista(lp, id, nome);
                verro1 = 0;
            }
        }
        verro1 = 1;
    }
    fprintf(fileout, "\nPessoas incluidas com sucesso!");
}

void AtualizarSistema(Sistema *system) {
    int cont1 = 0;
    ListaMudas *lm;
    Muda *aux, *aux2;

    for (cont1 = 0; cont1 < tam; cont1++) {
        lm = system->Hash[cont1]->mudas;
        if (lm != NULL) {
            for (aux = lm->pri; lm->pri != NULL; lm->pri = lm->pri->prox) {
                if (ArvCheia(lm->pri->arvore)) {
                    AtualizaNivelArvore(lm->pri->arvore->dir);
                    AtualizaNivelArvore(lm->pri->arvore->esq);
                    InserirArvHash(system->Hash, lm->pri->arvore->dir);
                    InserirArvHash(system->Hash, lm->pri->arvore->esq);

                    lm->pri->arvore->dir = NULL;
                    lm->pri->arvore->esq = NULL;

                    if (aux == lm->pri) {
                        aux = aux->prox;
                    }

                    lm = ExcluirMuda(lm, lm->pri->idm);
                }
                if (lm->pri == NULL) {
                    break;
                }
            }
            lm->pri = aux;
        }
    }
}

void ExcluirPessoa(Sistema *sys, FILE *fileinp, FILE *fileout) {
    int id, verro1 = 0, verro2 = 0;
    char comando[50];
    Indv *indv;

    fprintf(fileout, "\n\n");
    fprintf(fileout, "\nDigite o ID da pessoa que deseja excluir.");
    fscanf(fileinp, "%d", &id);
    fscanf(fileinp, "\n");
    fprintf(fileout, "\nDigitado: %d", id);

    while (!verro1) {
        if (IdPessoaExiste(id, sys->lps)) {
            indv = PegaIndvHash(sys->Hash, id);
            if (indv == NULL) {
                sys->lps = ExcluirPessoaLista(sys->lps, id);
                verro1 = 1;
            } else {
                fprintf(fileout, "\nNao eh possivel excluir esta pessoa, "
                        "pois ela pertence a algum aviao");
                verro2 = 1;
            }
        } else {
            fprintf(fileout, "\nErro: o ID digitado nao existe no sistema");
            verro2 = 1;
        }

        if (verro2) {
            fprintf(fileout, "\nAinda desseja Excluir alguma Pessoa? Digite:"
                    "sim ou nao.");
            fscanf(fileinp, "%[^\n]", comando);
            fscanf(fileinp, "\n");
            fprintf(fileout, "\nDigitado: %s", comando);
            if (!strcmp(comando, "sim") || !strcmp(comando, "SIM") || !strcmp(comando, "Sim")) {
                fprintf(fileout, "\nDigite o ID da pessoa que deseja excluir.");
                fscanf(fileinp, "%d", &id);
                fscanf(fileinp, "\n");
                fprintf(fileout, "\nDigitado: %d", id);
                verro2 = 0;
            } else {
                verro1 = 1;
            }
        }
    }
}

void IniciaSistema(Sistema *system, FILE *fileinp, FILE * fileout) {
    char comando[100];
    int verro1 = 1, cont1 = 0;

    fprintf(fileout, "\n               Seja Bem Vindo ao Sistema 8 BOLAS!!!");

    while (verro1) {
        fprintf(fileout, "\n\n\nDigite a funcao que deseja realizar e os parametros para que ela "
                "funcione, as posiveis funcoes sao:"
                "\n1) Incluir pessoas no sistema. Exemplo: incluirpessoas"
                "\n2) Inserir pessoa em aviao. Exemplo: inserirpessoa"
                "\n3) Excluir pessoa do sistema. Exemplo: excluirpessoa"
                "\n4) Exibir todos os tripulantes com vagas em aberto. Exemplo: exibir"
                "\n5) Finalizar a execucao de comandos. Exemplo: fim"
                "\nObs: so eh possivel excluir pessoas quando elas nao pertencem a nenhum aviao. "
                "Nao eh possivel inserir uma pessoa em um aviao a qual a mesma pertence.");

        fscanf(fileinp, "%[^\n]", comando);
        fscanf(fileinp, "\n");
        fprintf(fileout, "\n\nDigitado: %s", comando);

        if (strcmp(comando, "incluirpessoas") == 0) {
            IncluirPessoa(system->lps, fileinp, fileout);
        } else if (strcmp(comando, "inserirpessoa") == 0) {
            InserirPessoaHash(system, fileinp, fileout);
        } else if (strcmp(comando, "excluirpessoa") == 0) {
            ExcluirPessoa(system, fileinp, fileout);
        } else if (strcmp(comando, "exibir") == 0) {
            ExibirHash(system->Hash, fileout);
        } else if (strcmp(comando, "fim") == 0) {
            verro1 = 0;
        } else {
            fprintf(fileout, "\nComando invalido, digite novamente");
        }
        
        AtualizarSistema(system);
    }
}

