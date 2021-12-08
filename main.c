#include<stdio.h>


typedef struct
{
      int  chegada, duracao, prioridade;
      int fila, pronto;
}process_structure;

int DefineFila(int t1)
{
      if(t1 == 0 || t1 == 1 || t1 == 2 || t1 == 3)
      {
            return 1;
      }
      else
      {
            return 2;
      }
}
// Conta as linhas do arquivo de entrada para saber o numero de processos
int numeroLinhas(FILE *dados){
    int contador = 1;
    char linha;
    for (linha = getc(dados); linha != EOF; linha = getc(dados)){
        if (linha == '\n'){
            contador = contador + 1;
        }
    }
    fclose(dados);
    return contador;

}

int main()
{
      FILE *dados;
      dados = fopen("dados.txt","r");//para contar numero de processos

      FILE *dadosProcessos;
      if (dados == NULL){
        printf("Arquivo nao existe!");
      }
       printf("\n Arquivo encontrado com sucesso \n");

      int limite, contador, processoTemp, tempo, j, y, contador2, trocas;
      process_structure temp;
      limite = numeroLinhas(dados);
      process_structure processos[limite];
      dadosProcessos = fopen("dados.txt","r");//para salvar os dados de cada processo
      float tempoMedioEspera = 0;
      trocas=0;
      int k=1;
      contador=0;
      while (contador<limite) {

        int valor;
        int controlador = fscanf (dados, "%d", &valor);
        if (controlador != 1) break;
        if(k ==1){

            processos[contador].chegada = valor;

            k++;
        }
        else if(k ==2){
            processos[contador].duracao = valor;

            k++;
        }
        else if (k ==3){
            processos[contador].prioridade = valor;
            k++;
            processos[contador].fila= DefineFila( processos[contador].prioridade);
             processos[contador].pronto=0;
            k =1;
            contador++;
        }
    }
    fclose (dadosProcessos);
    printf("\n Dados de entrada lidos com sucesso \n");

    tempo = processos[0].duracao;

    int count;
    for(y = 0; y < limite; y++)
      {
            for(count = y; count < limite; count++)
            {
                  if(processos[count].chegada < tempo)
                  {
                        processos[count].pronto = 1;
                  }
            }
            for(count = y; count < limite - 1; count++)
            {
                  for(j = count + 1; j < limite; j++)
                  {
                        if(processos[count].pronto == 1 && processos[j].pronto == 1)
                        {
                              if(processos[count].fila == 2 && processos[j].fila == 1)
                              {
                                    temp = processos[count];
                                    processos[count] = processos[j];
                                    processos[j] = temp;
                                    trocas+=1;
                              }
                        }
                  }
            }
            for(count = y; count < limite - 1; count++)
            {
                  for(j = count + 1; j < limite; j++)
                  {
                        if(processos[count].pronto == 1 && processos[j].pronto == 1)
                        {
                              if(processos[count].fila == 1 && processos[j].fila == 1)
                              {
                                    if(processos[count].duracao > processos[j].duracao)
                                    {
                                          temp = processos[count];
                                          processos[count] = processos[j];
                                          processos[j] = temp;
                                          trocas+=1;
                                    }
                                    else
                                    {
                                          break;
                                    }
                              }
                        }
                  }
            }
            printf("\nProcesso: P%d\tTempo:\t%d a %d\n",y, tempo, tempo + processos[y].duracao);
            tempo = tempo + processos[y].duracao;

            tempoMedioEspera+= (tempo- processos[y].chegada);
            for(count = y; count < limite; count++)
            {
                  if(processos[count].pronto == 1)
                  {
                        processos[count].pronto = 0;
                  }
            }
      }
    float tempoMedioVida = tempo/limite;
    tempoMedioEspera = tempoMedioEspera/limite;
    printf("\nTrocas de contexto: %d\n",trocas);
    printf("\nTempo medio de vida: %.2f\n",tempoMedioVida);
    printf("\nTempo medio de espera: %.2f\n",tempoMedioEspera);
    return 0;
  }
