#include <stdio.h>

int main()
{
    int i;
    int qtd_total_processos = 4;
    int lista_prioridade_alta[4] = {1,2,3,4};
    
    // RETIRA da fila de ALTA prioridade
    for (i = 1 ; i < qtd_total_processos ; i++){
        lista_prioridade_alta[i-1]=lista_prioridade_alta[i];
    }
    lista_prioridade_alta[qtd_total_processos-1]=0;
    
    for (i = 0 ; i < 4 ; i++){
        printf("%d\n",lista_prioridade_alta[i]);
    }

    // INSERE na fila de ALTA prioridade
    for (i = 1 ; i < qtd_total_processos ; i++){
        if (lista_prioridade_alta[i]==0){
            lista_prioridade_alta[i] = 1;
            break;
        }
    }
    lista_prioridade_alta[qtd_total_processos-1]=0;

    for (i = 0 ; i < 4 ; i++){
        printf("%d\n",lista_prioridade_alta[i]);
    }

    return 0;
}
