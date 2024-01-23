#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "forca.h" //declara minha propria headerfiles

//variaveis globais
    int chutesDados = 0;
    char palavraSecreta[20];
    char chutes[26];

void menu()
{
    printf("******************************\n");
    printf("*       Jogo de Forca        *\n");
    printf("******************************\n");
}

void chuta() 
{ 
    //captura um chute
    char chute;
    chute = getchar();  // faz o imput 
        fflush(stdin);  //limpa o buffer

    chutes[chutesDados] = chute;

    chutesDados++; //somando +1 em tentativas
}

int jaChutou(char letra)
{
    int achou = 0;
                
            for (int j = 0; j < chutesDados; j++)    //faz um loop para verificar se achou a letra da palavra secreta ou não
            {                                      
                if (chutes[j] == letra)             //se acertou retorna a variavel achou
                {
                    achou = 1;
                    break;
                }   
            }
            return achou;
}

void desenhaForca()
{
    //imprime a letra secreta
        for(int i = 0 ; i < strlen(palavraSecreta); i++){ //loop para verificar o tamanho da palavra secreta

             int achou = jaChutou(palavraSecreta[i]); //chama a função e retorna a função achou
            
            if (achou)
            {
                printf("%c ",palavraSecreta[i]); 
            }
            else
            {
                printf("_ ");
            }
        }

        printf("\n");
}

void adicionaPalavra()
{
    char escolha;
    char novaPalavra[20];

    printf("voce deseja adicionar uma nova palavra no jogo? (S/N)\n");
        escolha = getchar();
            fflush(stdin);

    if (escolha == 'S' || escolha == 's')
    {
        printf("Qual a nova palavra? ");
          gets(novaPalavra);

        FILE* f;

        f = fopen("palavras.txt", "r+"); //abre o arquivo ler e escreve nele
        if (f == 0)
        {
            printf("Desculpe,banco de dados não desponivel\n"); //mensagem de erro
       
            exit(1); //serve para matar o programa e exit(0) avisa que o programa funcionou corretamente.
        }

        int quantidade;
        fscanf(f,"%d",&quantidade); //pega a quantidade de arquivo e escreve nele

        quantidade++;   //soma +1, assim escrevendo no arquivo a palavra nova

        fseek(f, 0, SEEK_SET); //posiciona para o começo do arquivo

        fprintf(f,"%d",quantidade); //escreve no arquivo

        fseek(f, 0, SEEK_END); //posiciona no final do arquivo

        fprintf(f,"\n%s",novaPalavra); 
        
        fclose(f); //fecha o arquivo
    }
    

}

void escolhePalavra()
{
    FILE* f; //variavel de arquivo

   f = fopen("palavras.txt", "r"); //abre o arquivo e ler ele

   if (f == 0)
   {
       printf("Desculpe,banco de dados não desponivel\n"); //mensagem de erro
       
       exit(1); //serve para matar o programa e exit(0) avisa que o programa funcionou corretamente.
   }

    int quantidadeDePalavras;
    fscanf(f,"%d",&quantidadeDePalavras); //descobre a quantidade de palavras que tem no arquivo

    srand(time(0));
    int randomico = rand() % quantidadeDePalavras; //calcula um numero randomico de 0 a quantidade de palavras

    for (int i = 0; i <= randomico; i++) //conta a quantidade de numero randomico 
    {
        fscanf(f,"%s",palavraSecreta); //ler a linha que está no momento atual do arquivo
    }

   fclose(f); //fecha o arquivo
}

int acertou()
{
    for (int i = 0; i < strlen(palavraSecreta); i++)
    {
        if (!jaChutou(palavraSecreta[i])) 
        {
            return 0;
        }
    }
    return 1;
}

int enforcou()
{
    int erros = 0;

    for (int i = 0; i < chutesDados; i++) //varre a lista de chutes e conta quantos chutes errados , se passar de 5 encerra o jogo
    {
         int existe = 0;

        for(int j = 0; j < strlen(palavraSecreta); j++)  //pega a quantidade de letras da palavra secreta
        {
            if (chutes[i] == palavraSecreta[j]) //verifica se chutes na possição i e igual a palavra secreta na posição j 
          {
              existe = 1;
              break;
          }
        }

        if(!existe) erros++;        //caso não encontrou aumenta +1 em erros
    }
    return erros >=5; //retorna a quantidades de erro e se erros for = a 5 fecha o jogo
}

int main(){
    menu(); //invoca a função menu

    escolhePalavra(); //invoca a função escolhe Palavra

    do 
    {
        desenhaForca(); 

        chuta(); 

    } while (!acertou() && !enforcou());
    
    adicionaPalavra();
}