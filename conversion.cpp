#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include <string.h>


#define DIM 3 //dimen��es das matrizes

void getCifra(int matriz[][DIM], char alfabeto[], char palavra[9]);
void showMatrizInt(int matriz[][DIM]);
void showMatrizFloat(float matriz[][DIM]);
void criptografar(int matrizChave[][DIM], int matrizCifrada[][DIM], int criptografia[][DIM]);
void descriptografar(float matrizChaveInversa[][DIM], int criptografia[][DIM]);

void desCifrar(int matriz[][DIM],  char alfabeto[]);

int main()
{
    int   matrizChave[DIM][DIM]        = {3,6,1,2,9,0,1,0,4};
    float matrizChaveInversa[DIM][DIM] = {0.705882, -0.470588, -0.176471, -0.156863, 0.215686, 0.039216, -0.176471, 0.117647, 0.294118};
    char  alfabeto[31]                 = {'-','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','#','?','.','!'};
    int   matrizCifrada[DIM][DIM];
    int   criptografia[DIM][DIM];
    
    //vou inicializar o vetor para que possa validar posteriormente.
    char op, palavra[9] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    
    
    do
    {
      printf("\nEscolha\n 1. CRIAR CRIPTOGRAFIA\n 2. VER CRIPTOGRAFIA\n 3. DESCRIPTOGRAFAR\n 4. INFORMAR UMA CRIPTOGRAFIA\n 5.SAIR DO PROGRAMA\n ");    
      op = getche(); 
         
      switch(op)
      {
          case '1':
               system("cls");
               printf("Informe uma palavra com 9 letras");
               fflush(stdin);
               gets(palavra);
               
               if( strlen( palavra ) > 9 )
			   {
			   	    printf("Sua palavra nao pode conter mais de 9 letras");
			   }
			   else
			   {
              	    //convertendo letras para numeros na ordem alfabetica
              	    getCifra(matrizCifrada, alfabeto, palavra);
               
                    //gerando criptografia
                    criptografar(matrizChave, matrizCifrada, criptografia);
           		}
          break;
        
          case '2':
          	    system("cls");
                if( palavra[0]  == NULL )
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
                if( palavra[0]  == NULL )
			    {
			   	    printf("Nao ha criptografia");
			    }
			    else
			    {   
              		descriptografar(matrizChaveInversa, criptografia); 
              		desCifrar(matrizCifrada, alfabeto);
          		}
          break;
          
          case '4':
              system("cls");
               
          break; 
          
          
          case '5':
              //sair do programa
          break;
          
          default:
                printf("Opcao invalida");
          break;      
      }
       
    }while(op != '6');
    system("cls");
    printf("Ate mais !");
    
    system("pause");
    return 1;
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
         
            //faz compara��o cada vez que percorrer o alfabeto
            //o programa fica preso no segundo loop
            //at� percorrer todo alfabeto ou encontrar o caracter
            if( palavra[l] == alfabeto[a] )
            {
                ordem[l] = a; //add ref. numerica dentro do vetor
                a=31;         //apenas um flag para for�ar a saida do la�o
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



//realizar a multiplica��o de matrizes gerando como resultado(produto) uma terceita matriz (criptografia)
void criptografar(int matrizChave[][DIM], int matrizCifrada[][DIM], int criptografia[][DIM])
{
    int somadora=0; // somar a multiplica��o dos indices equivalentes entre as duas matrizes
    
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
void descriptografar(float matrizChaveInversa[][DIM], int criptografia[][DIM])
{ 
    float somadora=0;
    
    for(int l=0; l<3; l++)
    {
        for(int c=0; c<3; c++)
        {
            for(int j=0; j<3; j++)
            {
              somadora = (somadora) + ((matrizChaveInversa[l][j])*(criptografia[j][c]));
            }
            printf(" [%.0f] ", somadora);
            somadora=0;
        }
        printf("\n");
    }
}


//desfaz a cifra da matriz cifrada e devolve a palavra
void desCifrar(int matriz[][DIM], char alfabeto[])
{
    char  palavraDescriptografada[9];
    int ordem[9], indexV=0;
    
    //transferindo valores do vetor para matriz (preenchendo a matriz cifrada)
    for( int l=0; l<3; l++ )
    {
         for( int c=0; c<3; c++ )
         {
            ordem[indexV++] = matriz[l][c];
         }  
    }
    
    
    //percorre todos os numeros do vetor ordem
    for( int l=0; l<9; l++ )
    {
         //percorre alfabeto procurando o indice
         for( int a=0; a<31; a++ )
         {
            if( ordem[l] == a )
            {
                palavraDescriptografada[l] = alfabeto[a]; //add ref. numerica dentro do vetor
                a=31;                           //apenas um flag para for�ar a saida do la�o
            }
         }   
    }
    
    system("cls");
    printf("\n esta eh a palavra que foi criptografada %s \n", palavraDescriptografada);
}
