
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
    /*PARTE 1 TRABALHO LENDO M REGISTROS */
    rewind(arq); //posiciona cursor no inicio do arquivo

    int reg = 0;
    int menor = INT_MAX;
    int pos_menor=0,pos_inicial=0;

    while (reg != nFunc) {
        //le o arquivo e coloca no vetor
        TFunc *v[M],*menores[M];

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
        /*//encontra o funcionario com menor chave no vetor
        for(int s = 0; s < M; s++){
            if(v[s]->cod < menor){
                menor = v[s]->cod;
                pos_menor = s;
            }
        }
        */

        //cria arquivo de particao e faz gravacao

        char *nome_particao = nome_arquivos_saida->nome;
        nome_arquivos_saida = nome_arquivos_saida->prox;
        printf("\n%s\n", nome_particao);
        FILE *m;
        if ((m = fopen(nome_particao, "wb+")) == NULL) {
            printf("Erro criar arquivo de saida\n");
        } else {
            for (int i = 0; i < M; i++) {
                fseek(m, (i) * tamanho_registro(), SEEK_SET);
                if(v[i]->cod < menor){
                    menor = v[i]->cod;
                    menores[i]->cod=menor;
                    pos_menor = i;
                    printf("1");//arquivo

                }
                else{
                    for(pos_inicial; pos_inicial<pos_menor; pos_inicial++){
                        salva_funcionario(menores[pos_inicial], m);
                        printf("2"); //apagar
                    }
                    pos_inicial=pos_menor;

                }
            }  
            fclose(m);
            printf("3");//apagar
        }
        for(int jj = 0; jj<M; jj++){
            imprime_funcionario(v[jj]);
            free(v[jj]);
            free(menores[jj]);
        }

    }
}

     /*  char *nome_particao = nome_arquivos_saida->nome;
        nome_arquivos_saida = nome_arquivos_saida->prox;
        printf("\n%s\n", nome_particao);
        FILE *p;
        if ((p = fopen(nome_particao, "wb+")) == NULL)
        {
            printf("Erro criar arquivo de saida\n");
        }
        else
        {
            printf("2");
            for (int i = 0; i < M; i++){
                fseek(p, (i) * tamanho_registro(), SEEK_SET);
                if(v[i]->cod < menor)
                {
                    menor = v[i]->cod;
                    menores[i]->cod=menor;
                    pos_menor = i;
                    printf('1');
                }
                else
                {
                    for(pos_inicial; pos_inicial<=pos_menor; pos_inicial++)
                    {
                        salva_funcionario(v[pos_inicial], p);

                        imprime_funcionario(v[i]);
                        pos_inicial=pos_menor;
                    }
                }
            }
            fclose(p);
        }
        for(int jj = 0; jj<M; jj++)
        {
            free(v[jj]);
        }


     /*   //faz o insertion sort
        for (int j = 2; j <= M; j++) {
        //posiciona o arquivo no registro j
        fseek(arq, (j-1) * tamanho_registro(), SEEK_SET);
        TFunc *fj = le_funcionario(arq);
        //printf("\n********* Funcionario atual: %d\n", fj->cod);
        i = j - 1;
        //posiciona o cursor no registro i
        fseek(arq, (i-1) * tamanho_registro(), SEEK_SET);
        do{
            TFunc *fi = le_funcionario(arq);
            if( (fi->cod < fj->cod)){
                break;
            }
            //printf("fi = %d\n", fi->cod);

            //posiciona o cursor no registro i+1
            fseek(arq, i * tamanho_registro(), SEEK_SET);
          //  printf("Salvando funcionario %d na posicao %d\n", fi->cod, i+1);
            salva_funcionario(fi, arq);
            i = i - 1;
            //l� registro i
            fseek(arq, (i-1) * tamanho_registro(), SEEK_SET);
           // fi = le_funcionario(arq);
          //  printf("fi = %d; i = %d\n", fi->cod, i);

            free(fi);
        }while ((i > 0) );

        //posiciona cursor no registro i + 1
        fseek(arq, (i) * tamanho_registro(), SEEK_SET);
        //printf("*** Salvando funcionario %d na posicao %d\n", fj->cod, i+1);
        //salva registro j na posi��o i
        salva_funcionario(fj, arq);
        }


       /* //faz ordenacao NATURAL
        int indice,menor,k;
        for (int j = 1; j < M; j++) {
            menor=v[j];
            indice=j;
            for(k=j+1;k< M; k++){
                if(v[k]<menor){
                    menor=v[k];
                    indice=j;
                }
            }
        v[indice]=v[i];
        v[i]=menor;
        }

        for (int j = 1; j < M; j++) {
            TFunc *f = v[j];
            i = j - 1;
            while ((i >= 0) && (v[i]->cod > f->cod)) {
                v[i + 1] = v[i];
                i = i - 1;
            }
            v[i + 1] = f;
        }*/

        /*//cria arquivo de particao e faz gravacao
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
        for(int jj = 0; jj<M; jj++)
            free(v[jj]);

    }*/
