
#include "funcionarios.h"
#include <stdlib.h>
#include <limits.h>

#include "particoes.h"


void classificacao_interna(FILE *arq, Lista *nome_arquivos_saida, int M, int nFunc) {
    rewind(arq); //posiciona cursor no inicio do arquivo


    int reg = 0;

    while (reg != nFunc) {
        //le o arquivo e coloca no vetor
        TFunc *v[M];
        int i = 0;
        while (!feof(arq)) {
            fseek(arq, (reg) * tamanho_registro(), SEEK_SET);
            v[i] = le_funcionario(arq);
       //     imprime_funcionario(v[i]);
            i++;
            reg++;
            if(i>=M) break;
        }

        //ajusta tamanho M caso arquivo de entrada tenha terminado antes do vetor
        if (i != M) {
            M = i;
        }

        //faz ordenacao
        for (int j = 1; j < M; j++) {
            TFunc *f = v[j];
            i = j - 1;
            while ((i >= 0) && (v[i]->cod > f->cod)) {
                v[i + 1] = v[i];
                i = i - 1;
            }
            v[i + 1] = f;
        }

        //cria arquivo de particao e faz gravacao
        char *nome_particao = nome_arquivos_saida->nome;
        nome_arquivos_saida = nome_arquivos_saida->prox;
        printf("\n%s\n", nome_particao);
        FILE *p;
        if ((p = fopen(nome_particao, "wb+")) == NULL) {
            printf("Erro criar arquivo de saida\n");
        } else {
            for (int i = 0; i < M; i++) {
                fseek(p, (i) * tamanho_registro(), SEEK_SET);
                salva_funcionario(v[i], p);
                imprime_funcionario(v[i]);
            }
            fclose(p);
        }
        for(int jj = 0; jj<M; jj++){
            free(v[jj]);
        }
    }
}

void selecao_natural(FILE *arq, Lista *nome_arquivos_saida, int M, int nFunc, int n){

    int reg = 0,pos_menor, menor=9999,k=0;
    //pos_menor=menor_pos(*arq, M, nFunc);
    //posicionando o cursor
    rewind(arq);
    //lendo o arquivo
    TFunc *gv[nFunc];

    while (reg != nFunc) {
        //le o arquivo e coloca no vetor
        TFunc *v[M];
        int i = 0;
        while (!feof(arq)) {
            fseek(arq, (reg) * tamanho_registro(), SEEK_SET);
            v[i] = le_funcionario(arq);
            gv[k]=v[i];
            //imprime_funcionario(v[i]);
            i++;
            k++;
            reg++;
            if(i>=M) break;

            //*********************************************************************************************
        }
        //ajusta tamanho M caso arquivo de entrada tenha terminado antes do vetor
        if (i != M) {
            M = i;
        }

    }

      //Menor posição
    for(int s = 0; s < k; s++){
            if(gv[s]->cod < menor){
                menor = gv[s]->cod;
                pos_menor = s;
            }
        printf("*");
        imprime_funcionario(gv[s]);
    }

    printf("menor %d, pos %d", menor,pos_menor);





    //first
    char *nome_particao = nome_arquivos_saida->nome;
        nome_arquivos_saida = nome_arquivos_saida->prox;
        printf("\n%s\n", nome_particao);
        FILE *p;
        if ((p = fopen(nome_particao, "wb+")) == NULL) {
            printf("Erro criar arquivo de saida\n");
        } else {
            fseek(p, (0) * tamanho_registro(), SEEK_SET);
            salva_funcionario(gv[pos_menor], p);
            imprime_funcionario(gv[pos_menor]);
            }



    //particao(gv[pos_menor], pos_menor,nome_arquivos_saida);
    int y=1;
    int next=pos_menor+1;
    gv[pos_menor]->cod=-1;

    //ordena outros valores
    int j=pos_menor+1;
    int r=j;
    while(j!=(pos_menor)){
        if(y<M){
            for(r;r<=nFunc;r++){
                if(r>=nFunc){
                    r=0;
                    break;
                }
                if((j<pos_menor)){
                    r=j;
                    //printf("4");
                    break;
                }
                if((gv[j]->cod!=-1)&&(gv[r]->cod!=-1)){
                        //printf("3");
                    if(gv[j]->cod<gv[r]->cod){
                        if ((p = fopen(nome_particao, "wb+")) == NULL) {
                            printf("Erro criar arquivo de saida\n");
                        }
                        else {
                            fseek(p, (0) * tamanho_registro(), SEEK_SET);
                            salva_funcionario(gv[j], p);
                            imprime_funcionario(gv[j]);
                            //printf("1");
                            gv[j]->cod=-1;
                            y++;
                            break;}
                }

               if(gv[j]->cod>gv[r]->cod){
                        if ((p = fopen(nome_particao, "wb+")) == NULL) {
                            printf("Erro criar arquivo de saida\n");
                            }
                        else {
                           // printf("1");
                            fseek(p, (0) * tamanho_registro(), SEEK_SET);
                            salva_funcionario(gv[r], p);
                            imprime_funcionario(gv[r]);
                            gv[r]->cod=-1;
                            // printf("2");
                            j--;
                            y++;
                            break;
                            }
                        }
                }

        }
        }
        else{
            //printf("2");
            fclose(p);
            char *nome_particao = nome_arquivos_saida->nome;
            nome_arquivos_saida = nome_arquivos_saida->prox;
            printf("\n%s\n", nome_particao);
            FILE *p;
            j--;
            //r--;
            y=0;
            }

        j++;
        if(j>=nFunc){
            j=0;
        }

    }

}

   /* while(j!=(pos_menor)){

            for(int r=j+1;j<nFunc;r++){
                if((gv[j]->cod!=-1)&&(gv[r]->cod!=-1)){
                    if(y<M){
                    if(gv[j]->cod<gv[r]->cod){
                        if ((p = fopen(nome_particao, "wb+")) == NULL) {
                            printf("Erro criar arquivo de saida\n");
                        }
                        else {
                            fseek(p, (0) * tamanho_registro(), SEEK_SET);
                            salva_funcionario(gv[j], p);
                            imprime_funcionario(gv[j]);
                            //printf("1");
                            gv[j]->cod=-1;
                            y++;
                            break;

                        }}
                        if(gv[j]->cod>gv[r]->cod){
                            if ((p = fopen(nome_particao, "wb+")) == NULL) {
                                printf("Erro criar arquivo de saida\n");
                            }
                            else {
                                fseek(p, (0) * tamanho_registro(), SEEK_SET);
                                salva_funcionario(gv[r], p);
                                imprime_funcionario(gv[r]);
                                gv[r]->cod=-1;
                               // printf("2");
                                r--;
                                y++;
                                break;
                            }
                        }


                    }
            else{
                fclose(p);
                char *nome_particao = nome_arquivos_saida->nome;
                nome_arquivos_saida = nome_arquivos_saida->prox;
                printf("\n%s\n", nome_particao);
                FILE *p;
                j--;
                //r--;
                y=0;
            }

        j++;
        if(j>=nFunc){
            j=0;
        }
                }
    }
}*/


    /*while(j!=(pos_menor)){
        for(int r=j+1;j<nFunc;r++){
            if((gv[r]->cod>gv[j]->cod)&&(gv[j]->cod!=-1)&&(gv[r]->cod!=-1)){
                if(y<M){
                    if ((p = fopen(nome_particao, "wb+")) == NULL) {
                        printf("Erro criar arquivo de saida\n");
                    }
                else {
                    fseek(p, (0) * tamanho_registro(), SEEK_SET);
                    salva_funcionario(gv[j], p);
                    imprime_funcionario(gv[j]);
                    gv[j]->cod=-1;
                    break;

                }


                }
            else{
                fclose(p);
                char *nome_particao = nome_arquivos_saida->nome;
                nome_arquivos_saida = nome_arquivos_saida->prox;
                printf("\n%s\n", nome_particao);
                FILE *p;
                j--;
                r--;
                y=0;
                break;
        }

            }
            else if((gv[j]->cod!=-1)&&(gv[r]->cod!=-1)){

                if(y<M){
                    if ((p = fopen(nome_particao, "wb+")) == NULL) {
                        printf("Erro criar arquivo de saida\n");
                    }
                else {
                    fseek(p, (0) * tamanho_registro(), SEEK_SET);
                    salva_funcionario(gv[r], p);
                    imprime_funcionario(gv[r]);
                    gv[j]->cod=-1;
                    r--;
                    break;

                }


                }
            else{
                fclose(p);
                char *nome_particao = nome_arquivos_saida->nome;
                nome_arquivos_saida = nome_arquivos_saida->prox;
                printf("\n%s\n", nome_particao);
                FILE *p;
                j--;
                r--;
                y=0;
                break;
        }



            }
        }



        y++;
        j++;
        if(j>=nFunc){
            j=0;
        }
    }*/



void particao(TFunc *gv, int pos,Lista *nome_arquivos_saida){
    //cria arquivo de particao e faz gravacao
        char *nome_particao = nome_arquivos_saida->nome;
        nome_arquivos_saida = nome_arquivos_saida->prox;
        printf("\n%s\n", nome_particao);
        FILE *p;
        if ((p = fopen(nome_particao, "wb+")) == NULL) {
            printf("Erro criar arquivo de saida\n");
        } else {
            fseek(p, (0) * tamanho_registro(), SEEK_SET);
            salva_funcionario(gv, p);
            imprime_funcionario(gv);
            }
            fclose(p);

}


