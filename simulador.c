#include<stdio.h>

struct Processos
{
    int qtd_total_ios, tempo_de_chegada_io[10], tipo_io[10];
    int tempo_de_espera, tempo_de_resposta, tempo_de_chegada_processo, tempo_de_explosao_processo;
};

int main()
{
    // Declarando Variaveis Necessárias
    int i, j, qtd_total_processos, total = 0, x, var_aux = 0, quantum;    
    int tempo_de_espera = 0, tempo_de_resposta = 0;
    float tempo_medio_de_espera, tempo_medio_de_resposta;
    printf("\nEntre o numero total de processos:\t");
    scanf("%d", &qtd_total_processos);

    x = qtd_total_processos; // Recebe o numero total de processos

    struct Processos processo[x];
    
    int array_temp[x];

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
    }
 
    printf("\nEntre o tempo do Quantum:\t");
    scanf("%d", &quantum);
    printf("\nProcesso ID\t\tTempo de Explosão\t Tempo de Resposta\t Tempo de Espera\n");
    
    // Percorre enquanto a quantidade de processos for diferente de zero 
    for(total = 0, i = 0; x != 0;)
    {
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
    }
      
    // Extrai o tempo medio de espera
    tempo_medio_de_espera = tempo_de_espera * 1.0 / qtd_total_processos;
    printf("\n\nTempo Médio de Espera:\t%f", tempo_medio_de_espera);

    // Extrai o tempo medio  de inversão
    tempo_medio_de_resposta = tempo_de_resposta * 1.0 / qtd_total_processos;
    printf("\nAvg Tempo Médio de Resposta:\t%f\n", tempo_medio_de_resposta);

    return 0;
}