#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include <string.h>

#define DIM 3 //dimenções das matrizes

void getCifra(int matriz[][DIM], char alfabeto[], char palavra[9]);
void showMatrizInt(int matriz[][DIM]);
void showMatrizFloat(float matriz[][DIM]);
void criptografar(int matrizChave[][DIM], int matrizCifrada[][DIM], int criptografia[][DIM]);
void descriptografar(float matrizChaveInversa[][DIM], int criptografia[][DIM], int matrizCifrada[][DIM]);
void desCifrar(int matriz[][DIM],  char alfabeto[]);

int main()
{
    int   matrizChave[DIM][DIM]        = {3,6,1,2,9,0,1,0,4};
    float matrizChaveInversa[DIM][DIM] = {0.705882, -0.470588, -0.176471, -0.156863, 0.215686, 0.039216, -0.176471, 0.117647, 0.294118};
    char  alfabeto[31]                 = {'-','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','#','?','.','!'};
    int   matrizCifrada[DIM][DIM];
    int   criptografia[DIM][DIM];
    
    //vou inicializar o vetor para que possa validar posteriormente e completar os caracteres caso usr informe menos
    char op, palavra[9] = {' ',' ',' ',' ',' ',' ',' ',' ',' '};
    
    do
    {
      printf("\nEscolha\n 1. CRIAR CRIPTOGRAFIA\n 2. VER CRIPTOGRAFIA\n 3. DESCRIPTOGRAFAR\n 4.SAIR DO PROGRAMA\n ");    
      op = getche(); 
         
      switch(op)
      {
          case '1':
               system("cls");
               //apenas um macete para que a palavra nao pegue parte da criptografia anterior
               for(int i=0; i<9; i++)palavra[i] = ' ';
               
               printf("Informe uma palavra com 9 letras");
               fflush(stdin);
               gets(palavra);
               
               if( strlen( palavra ) > 9 )
			   {
			   	    printf("Sua palavra nao pode conter mais de 9 letras");
			   }
			   else
			   {
                    //preciso substituir espaços por -                   
                    for(int e=0; e<9; e++)if( palavra[e] == ' ' )palavra[e] = '-';

              	    //convertendo letras para numeros na ordem alfabetica
              	    getCifra(matrizCifrada, alfabeto, palavra);
                    //gerando criptografia
                    criptografar(matrizChave, matrizCifrada, criptografia);
           		}
          break;
        
          case '2':
          	    system("cls");
                if( palavra[0]  == ' ' )
			    {
			   	    printf("Nao ha criptografia");
			    }
			    else
			    {    
                    showMatrizInt(criptografia); 
                }
          break;
        
          case '3':
          	    system("cls");
                if( palavra[0]  == ' ' )
			    {
			   	    printf("Nao ha criptografia");
			    }
			    else
			    {   
              		descriptografar(matrizChaveInversa, criptografia, matrizCifrada); 
              		desCifrar(matrizCifrada, alfabeto);
          		} 
          break;
          
          default:
                printf("Opcao invalida");
          break;      
      }
       
    }while(op != '4');
    system("cls");
    printf("Ate mais !");
    
    system("pause");
    return 1;
}


//PERCORRE E MOSTRA MATRIZ NA TELA
void showMatrizInt(int matriz[][DIM])
{
    for( int l=0; l<3; l++ )
    {
         for( int c=0; c<3; c++ )
         {
             printf(" [%d] ", matriz[l][c]);
         }   
         printf("\n");
    }
}


//Exibi na tela a matriz chave inversa
void showMatrizFloat(float matriz[][DIM])
{
    for( int l=0; l<3; l++  )
    {
        for( int c=0; c<3; c++  )
        {
             printf(" [%f] ", matriz[l][c]);
        }
        printf("\n");
    }
}


//Recebe a palavra e retorna uma matriz na ordem numerica das letras
void getCifra(int matriz[][DIM], char alfabeto[], char palavra[9])
{
    int ordem[9], indexV;
      
    //percorre todas as letras da palavra
    for( int l=0; l<9; l++ )
    {
         //percorre alfabeto procurando a letra atual
         for( int a=0; a<31; a++ )
         {
            //faz comparação cada vez que percorrer o alfabeto
            //o programa fica preso no segundo loop
            //até percorrer todo alfabeto ou encontrar o caracter
            if( palavra[l] == alfabeto[a] )
            {
                ordem[l] = a; //add ref. numerica dentro do vetor
                a=31;         //apenas um flag para forçar a saida do laço
            }
         }   
    }
    
    indexV=0;
    //transferindo valores do vetor para matriz (preenchendo a matriz cifrada)
    for( int l=0; l<3; l++ )
    {
         for( int c=0; c<3; c++ )
         {
            matriz[l][c] = ordem[indexV++];
         }  
    }
}


//realizar a multiplicação de matrizes gerando como resultado(produto) uma terceita matriz (criptografia)
void criptografar(int matrizChave[][DIM], int matrizCifrada[][DIM], int criptografia[][DIM])
{
    int somadora=0; // somar a multiplicação dos indices equivalentes entre as duas matrizes
    for(int l=0; l<3; l++)
    {
        for(int c=0; c<3; c++)
        {
            for(int j=0; j<3; j++)
            {
              somadora = (somadora) + ((matrizChave[l][j])*(matrizCifrada[j][c]));
            }
            criptografia[l][c] = somadora;
            somadora=0;
        }
    }
}

//descriptografando 
void descriptografar(float matrizChaveInversa[][DIM], int criptografia[][DIM], int matrizCifrada[][DIM])
{ 
    float somadora=0.0;
    for(int l=0; l<3; l++)
    {
        for(int c=0; c<3; c++)
        {
            for(int j=0; j<3; j++)
            {
              somadora = (somadora) + ((matrizChaveInversa[l][j])*(criptografia[j][c]));
            }
            printf(" [%d] ", somadora);
            somadora=0;       
        }
        printf("\n");
    }
}


//desfaz a cifra da matriz cifrada e devolve a palavra
void desCifrar(int matriz[][DIM], char alfabeto[])
{
    char  palavraDescriptografada[9];
    int   indexV=0;
    
    //transferindo valores do vetor para matriz (preenchendo a matriz cifrada)
    for( int l=0; l<3; l++ )
    {
         for( int c=0; c<3; c++ )
         {
             //percorre alfabeto procurando o indice
             for( int a=0; a<31; a++ )
             {
                if( matriz[l][c] == a )
                {
                    palavraDescriptografada[indexV++] = alfabeto[a]; //add ref. numerica dentro do vetor
                    a=31;                                            //apenas um flag para forçar a saida do laço
                }
             }   
         }
    }

    //preciso devolver os espaços que foram substituidos por -                   
    for(int e=0; e<9; e++)if( palavraDescriptografada[e] == '-' )palavraDescriptografada[e] = ' ';
    system("cls");
    printf("\n esta eh a palavra que foi criptografada %s \n", palavraDescriptografada);
}
