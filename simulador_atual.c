#include<stdio.h>
#include <stdlib.h>
struct Processos
{
    int qtd_total_ios, tempo_de_chegada_io[10], tipo_io[10];
    int tempo_de_espera, tempo_de_resposta, tempo_de_chegada_processo, tempo_de_explosao_processo, tempo_processamento;
};

int main()
{
    // Declarando Variaveis Necessárias
    int i, j, k, contador_disco, contador_fita, contador_impressora, qtd_total_processos, total = 0, x, var_aux = 0, quantum, upper = 5, lower = 1;  
    int tempo_de_explosao_impressora = (rand() % (upper - lower + 1)) + lower, tempo_de_explosao_disco = (rand() % (upper - lower + 1)) + lower, tempo_de_explosao_fita = (rand() % (upper - lower + 1)) + lower;
    int tempo_de_espera = 0, tempo_de_resposta = 0;
    float tempo_medio_de_espera, tempo_medio_de_resposta;

    printf("Iniciando o Simulador ... \n\n");
    printf("Tamanho maximo de fila de cada tipo de IO: 10 \n\n");
    printf("Tempo de Explossão da Fita:\t %d \n", tempo_de_explosao_fita);
    printf("Tempo de Explosão do Disco:\t %d \n", tempo_de_explosao_disco);
    printf("Tempo de Explosão da Impressora:\t %d \n", tempo_de_explosao_impressora);
    
    printf("\nEntre o numero total de processos:\t");
    scanf("%d", &qtd_total_processos);

    x = qtd_total_processos; // Recebe o numero total de processos

    struct Processos processo[x];
    
    int array_temp[x], lista_prioridade_alta[x], lista_prioridade_baixa[x], lista_disco[x], lista_fita[x], lista_impressora[x];

    // Faz um loop recebendo as informações referentes a cada processo
    for(i = 0; i < qtd_total_processos; i++)
    {
        printf("\nEntre os detalhes do processo[%d]\n", i + 1);
 
        printf("Tempo de Chegada:\t");
        scanf("%d", &processo[i].tempo_de_chegada_processo);
 
        printf("Tempo de Explosão:\t");
        scanf("%d", &processo[i].tempo_de_explosao_processo);

        printf("Quantidade de IOs no Processo:\t");
        scanf("%d", &processo[i].qtd_total_ios);
        
        for(j=0; j < processo[i].qtd_total_ios; j++)
        {
            printf("Tempo de Chegada do IO:\t");
            scanf("%d", &processo[i].tempo_de_chegada_io[j]);

            printf("Tipo do IO (Ex: 1 para disco, 2 para fita e 3 para impressora):\t");
            scanf("%d", &processo[i].tipo_io[j]);
        }
        // Variavel Temporaria
        array_temp[i] = processo[i].tempo_de_explosao_processo;
        lista_prioridade_alta[i] = i;
        processo[i].tempo_processamento = 0;
    }
    
    //loops para inicializar listas com 0(vazio)
    //inicializando lista_prioridade_alta, lista_prioridade_baixa, lista_disco, lista_fita e lista_impressora
    for(i = 0; i<qtd_total_processos; i++)
    {
        lista_prioridade_baixa[i] = 0;
        lista_prioridade_alta[i] = 0;
        lista_disco[i] = 0;
        lista_fita[i] = 0;
        lista_impressora[i] = 0;
    }
    
    printf("\nEntre o tempo do Quantum:\t");
    scanf("%d", &quantum);
    printf("\nProcesso ID\t\tTempo de Explosão\t Tempo de Resposta\t Tempo de Espera\n");
    
    // Percorre enquanto a quantidade de processos for diferente de zero 
    for(i = 0; x != 0; i++)
    {
    	        
    //verifica a cada tique
        //verificar se processo atual pediu IO
            //verifica lista de prontos de alta prioridade
            if(lista_prioridade_alta[0] != 0)
            {
                processo[lista_prioridade_alta[0]].tempo_processamento++;
                //percorre a lista de tempos io do processo atual e compara com o tempo atual de execucao 
                for(j=0; j<processo[lista_prioridade_alta[0]].qtd_total_ios;j++)
                {
                    //testa se algum tempo de IO do processo eh o tempo atual
                    if(processo[lista_prioridade_alta[0]].tempo_de_chegada_io[j] == i)
                    {
                        //identifica o tipo de IO requisitado, remove o processo atual da fila de prontos de alta prioridade e insere na fila do IO respectivo
                        //funcao para remover o processo atual da fila de prontos de alta prioridade
		                for (k = 1 ; k < qtd_total_processos ; k++){
		                    lista_prioridade_alta[k-1]=lista_prioridade_alta[k];
		                }
		                lista_prioridade_alta[qtd_total_processos-1]=0;

                        if(processo[lista_prioridade_alta[0]].tipo_io[j] == 1)
                        {
                            //funcao para inserir o processo lista_prioridade_alta[0] no final da fila de disco
                            contador_disco = tempo_de_explosao_disco;
                            int m = 0;
                            for (m = 1 ; m < qtd_total_processos ; m++){
                                if (lista_disco[m]==0){
                                    lista_disco[m] = lista_prioridade_alta[0];
                                    break;
                                }
                            }
                            

                        }

                        else if(processo[lista_prioridade_alta[0]].tipo_io[j] == 2)
                        {
                            //funcao para inserir o processo lista_prioridade_alta[0] no final da fila de fita
                            contador_fita = tempo_de_explosao_fita;
                            int m = 0;
                            for (m = 1 ; m < qtd_total_processos ; m++){
                                if (lista_fita[m]==0){
                                    lista_fita[m] = lista_prioridade_alta[0];
                                    break;
                                }
                            }
                            
                        }
                        else 
                        {
                            //funcao para inserir o processo lista_prioridade_alta[0] no final da fila de impressora
                            contador_impressora = tempo_de_explosao_impressora;
                            
                            int m = 0;
                            for (m = 1 ; m < qtd_total_processos ; m++){
                                if (lista_impressora[m]==0){
                                    lista_impressora[m] = lista_prioridade_alta[0];
                                    break;
                                }
                            }

                        }
                    }
                }
            }
            //se nao existir processo na alta, verifica lista de prontos de baixa prioridade
            else if(lista_prioridade_baixa[0] != 0)
                 {
                    //percorre a lista de tempos io do processo atual e compara com o tempo atual de execucao 
                    for(j=0; j<processo[lista_prioridade_baixa[0]].qtd_total_ios; j++)
                    {
                        //testa se algum tempo de IO do processo eh o tempo atual
                        if(processo[lista_prioridade_baixa[0]].tempo_de_chegada_io[j] == i)
                        {
                            //identifica o tipo de IO requisitado, remove o processo atual da fila de prontos de baixa prioridade e insere na fila do IO respectivo
                            
                            //funcao para remover o processo atual da fila de prontos de baixa prioridade
                            for (k = 1 ; k < qtd_total_processos ; k++){
                                lista_prioridade_baixa[k-1]=lista_prioridade_baixa[k];
                            }
                            lista_prioridade_baixa[qtd_total_processos-1]=0;

                            if(processo[lista_prioridade_baixa[0]].tipo_io[j] == 1)
                            {
                                //funcao para inserir o processo lista_prioridade_baixa[0] no final da fila de disco
                                contador_disco = tempo_de_explosao_disco;
                                int m = 0;
                                for (m = 1 ; m < qtd_total_processos ; m++){
                                    if (lista_disco[m]==0){
                                        lista_disco[m] = lista_prioridade_baixa[0];
                                        break;
                                    }
                                }

                            }
                            else 
                            if(processo[lista_prioridade_baixa[0]].tipo_io[j] == 2)
                            {
                                //funcao para inserir o processo lista_prioridade_baixa[0] no final da fila de fita
                                contador_fita = tempo_de_explosao_fita;
                                int m = 0;
                                for (m = 1 ; m < qtd_total_processos ; m++){
                                    if (lista_fita[m]==0){
                                        lista_fita[m] = lista_prioridade_baixa[0];
                                        break;
                                    }
                                }

                            }
                            else 
                            {
                                //funcao para inserir o processo lista_prioridade_baixa[0] no final da fila de impressora
                                contador_impressora = tempo_de_explosao_impressora;
                                int m = 0;
                                for (m = 1 ; m < qtd_total_processos ; m++){
                                    if (lista_impressora[m]==0){
                                        lista_impressora[m] = lista_prioridade_baixa[0];
                                        break;
                                    }
                                }
                            }
                        }
                    }
                 }
                
        
        //verifica se algum processo eh criado(entra pra fila de prontos de alta prioridade)
        for(j=0; j<qtd_total_processos; j++)
        {
            if(processo[j].tempo_de_chegada_processo == i)
            {
                //funcao para inserir o processo j no final da fila de alta prioridade
                int m = 0;
                for (m = 1 ; m < qtd_total_processos ; m++){
                    if (lista_prioridade_alta[m]==0){
                        lista_prioridade_alta[m] = j+1;
                        printf("Processo Criado \n");
                        break;
                    }
                }
                
            }
        }
        
        //verifica se algum IO terminou de executar e direciona pra fila de prontos correta
            //verifica se existe algum processo em operacao de IO
            //verifica fila de disco. Se existe, processa e decrementa o contador.
            if(lista_disco[0] != 0)
            {
                contador_disco--;
                //Se contador igual a zero, terminou de processar.
                //Insere processo na fila de prontos de baixa prioridade e remove da fila de disco.
                if(contador_disco == 0)
                {
                    //funcao para inserir o processo lista_disco[0] no final da fila de baixa prioridade
                    int m = 0;
                    for (m = 1 ; m < qtd_total_processos ; m++){
                        if (lista_prioridade_baixa[m]==0){
                            lista_prioridade_baixa[m] = lista_disco[0] ;
                            break;
                        }
                    }
                    //funcao para remover o processo lista_disco[0] do inicio da fila de disco
                    int k=0;
                    for (k = 1 ; k < qtd_total_processos ; k++){
                        lista_disco[k-1]=lista_disco[k];
                    }
                    lista_disco[qtd_total_processos-1]=0;
                }
            }
            else
            //verifica fila de fita. Se existe, processa e decrementa o contador.
            if(lista_fita[0] != 0)
            {
                contador_fita--;
                //Se contador igual a zero, terminou de processar.
                //Insere processo na fila de prontos de alta prioridade e remove da fila de fita.
                if(contador_fita == 0)
                {
                    //funcao para inserir o processo lista_fita[0] no final da fila de alta prioridade
                    int m = 0;
                    for (m = 1 ; m < qtd_total_processos ; m++){
                        if (lista_prioridade_alta[m]==0){
                            lista_prioridade_alta[m] = lista_fita[0] ;
                            break;
                        }
                    }
                    //funcao para remover o processo lista_fita[0] do inicio da fila de fita
                    int k=0;
                    for (k = 1 ; k < qtd_total_processos ; k++){
                        lista_fita[k-1]=lista_fita[k];
                    }
                    lista_fita[qtd_total_processos-1]=0;
                }
            }
            //verifica fila de impressora. Se existe, processa e decrementa o contador.
            else if(lista_impressora[0] != 0)
            {
                contador_impressora--;
                //Se contador igual a zero, terminou de processar.
                //Insere processo na fila de prontos de alta prioridade e remove da fila de impressora.
                if(contador_impressora == 0)
                {
                    //funcao para inserir o processo lista_impressora[0] no final da fila de alta prioridade
                    int m = 0;
                    for (m = 1 ; m < qtd_total_processos ; m++){
                        if (lista_prioridade_alta[m]==0){
                            lista_prioridade_alta[m] = lista_impressora[0] ;
                            break;
                        }
                    }
                    //funcao para remover o processo lista_impressora[0] do inicio da fila de impressora
                    int k=0;
                    for (k = 1 ; k < qtd_total_processos ; k++){
                        lista_impressora[k-1]=lista_impressora[k];
                    }
                    lista_impressora[qtd_total_processos-1]=0;
                }
            }
        
        //verifica no final de cada quantum
        if( i%quantum == 0)
        {
            printf("final do quantum \n");
            if( lista_prioridade_alta[0] != 0 )
            {
                //funcao para inserir o processo atual no final da fila de baixa prioridade
                for (j = 1 ; j < qtd_total_processos ; j++){
                    if (lista_prioridade_baixa[j]==0){
                        lista_prioridade_baixa[j] = lista_prioridade_alta[0] ;
                        
                        break;
                    }
                }
                
                //funcao para remover o processo atual do inicio da fila de prontos de alta prioridade
                // RETIRA da fila de ALTA prioridade
                for (j = 1 ; j < qtd_total_processos ; j++){
                    lista_prioridade_alta[j-1]=lista_prioridade_alta[j];
                }
                lista_prioridade_alta[qtd_total_processos-1]=0;
                printf("processo preemptado da alta \n");
            } 
            else
            if( lista_prioridade_baixa[0] != 0)
            {
                //funcao para inserir o processo atual no final da fila de baixa prioridade
                for (j = 1 ; j < qtd_total_processos ; j++){
                    if (lista_prioridade_baixa[j]==0){
                        lista_prioridade_baixa[j] = lista_prioridade_alta[0] ;
                        break;
                    }
                }
                                
                //funcao para remover o processo atual do inicio da fila de prontos de baixa prioridade
                for (j = 1 ; j < qtd_total_processos ; j++){
                    lista_prioridade_baixa[j-1]=lista_prioridade_baixa[j];
                }
                lista_prioridade_baixa[qtd_total_processos-1]=0;
                printf("processo preemptado da baixa \n");
            }
        }
        
        //verificar se processo atual chegou ao fim
        //verificar fila de alta
        if(lista_prioridade_alta[0] != 0)
        {
            if(processo[lista_prioridade_alta[0]-1].tempo_processamento == processo[lista_prioridade_alta[0]-1].tempo_de_explosao_processo)
            {
                x--; // Diminui no numero de processos
                
                // Printa o fim daquele processo
                printf("\nProcesso[%d]\t\t%d\t\t %d\t\t\t %d", lista_prioridade_alta[0], processo[lista_prioridade_alta[0]-1].tempo_de_explosao_processo, i - processo[lista_prioridade_alta[0]-1].tempo_de_chegada_processo, i - processo[lista_prioridade_alta[0]-1].tempo_de_chegada_processo - processo[lista_prioridade_alta[0]-1].tempo_de_explosao_processo);
                tempo_de_espera = tempo_de_espera + i - processo[lista_prioridade_alta[0]-1].tempo_de_chegada_processo - processo[lista_prioridade_alta[0]-1].tempo_de_explosao_processo; // Verifica o tempo de espera
                tempo_de_resposta = tempo_de_resposta + i - processo[lista_prioridade_alta[0]-1].tempo_de_chegada_processo; // Verifica o tempo de inversão 
                
                
                //remover processo da fila de alta
                for (j = 1 ; j < qtd_total_processos ; j++){
                        lista_prioridade_alta[j-1]=lista_prioridade_alta[j];
                    }
                lista_prioridade_alta[qtd_total_processos-1]=0;
                
            }
        } else
        //verificar fila de baixa
        if(lista_prioridade_baixa[0] != 0)
        {
            if(processo[lista_prioridade_baixa[0]-1].tempo_processamento == processo[lista_prioridade_baixa[0]-1].tempo_de_explosao_processo)
            {
                
                x--; // Diminui no numero de processos
                
                // Printa o fim daquele processo
                printf("\nProcesso[%d]\t\t%d\t\t %d\t\t\t %d", lista_prioridade_baixa[0], processo[lista_prioridade_baixa[0]-1].tempo_de_explosao_processo, i - processo[lista_prioridade_baixa[0]-1].tempo_de_chegada_processo, i - processo[lista_prioridade_baixa[0]-1].tempo_de_chegada_processo - processo[lista_prioridade_baixa[0]-1].tempo_de_explosao_processo);
                tempo_de_espera = tempo_de_espera + i - processo[lista_prioridade_baixa[0]-1].tempo_de_chegada_processo - processo[lista_prioridade_baixa[0]-1].tempo_de_explosao_processo; // Verifica o tempo de espera
                tempo_de_resposta = tempo_de_resposta + i - processo[lista_prioridade_baixa[0]-1].tempo_de_chegada_processo; // Verifica o tempo de inversão 
                
                
                //remover processo da fila de baixa
                for (j = 1 ; j < qtd_total_processos ; j++){
                        lista_prioridade_baixa[j-1]=lista_prioridade_baixa[j];
                    }
                lista_prioridade_baixa[qtd_total_processos-1]=0;
                
                
            }
        }
            
        /*    
        // Verifica de tempo de explosão dele é menor ou igual o quanto e maior que zero
        if(array_temp[i] <= quantum && array_temp[i] > 0)
        {
            total = total + array_temp[i]; //Adiciona ao tempo total
            array_temp[i] = 0; // Associa como zero para dar como terminado 
            var_aux = 1; 
        }
        
        
        // Verifica apenas que o tempo de explosão é maior que zero
        else if(array_temp[i] > 0)
        {
            array_temp[i] = array_temp[i] - quantum; // Diminui o Tempo pelo quantum 
            total = total + quantum; // Adiciona o tempo do quanto ao total ja processado 
        }
        
        // Verifica se o tempo daquele processo foi pra zero e o var_aux é igual a 1
        if(array_temp[i] == 0 && var_aux == 1)
        {
            x--; // Diminui no numero de processos
            // Printa o fim daquele processo
            printf("\nProcesso[%d]\t\t%d\t\t %d\t\t\t %d", i + 1, processo[i].tempo_de_explosao_processo, total - processo[i].tempo_de_chegada_processo, total - processo[i].tempo_de_chegada_processo - processo[i].tempo_de_explosao_processo);
            tempo_de_espera = tempo_de_espera + total - processo[i].tempo_de_chegada_processo - processo[i].tempo_de_explosao_processo; // Verifica o tempo de espera
            tempo_de_resposta = tempo_de_resposta + total - processo[i].tempo_de_chegada_processo; // Verifica o tempo de inversão 
            var_aux = 0; // Coloca a variavel auxiliar como zero
        }
        
        
        // Se i é igual ao numero de processos menos um 
        if(i == qtd_total_processos - 1)
        {
            i = 0;
        }
        
        // Se o tempo de chegada do processo for menor ou igual ao tempo total, ele incrementa o i
        else if(processo[i+1].tempo_de_chegada_processo <= total)
        {
            i++;
        }
        
        // Caso contrario o i segue como zero 
        else
        {
            i = 0;
        }
        */
    }
      
    // Extrai o tempo medio de espera
    tempo_medio_de_espera = tempo_de_espera * 1.0 / qtd_total_processos;
    printf("\n\nTempo Médio de Espera:\t%f", tempo_medio_de_espera);

    // Extrai o tempo medio  de inversão
    tempo_medio_de_resposta = tempo_de_resposta * 1.0 / qtd_total_processos;
    printf("\nAvg Tempo Médio de Resposta:\t%f\n", tempo_medio_de_resposta);

    return 0;
}
