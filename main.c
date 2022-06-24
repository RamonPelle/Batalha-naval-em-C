#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <locale.h>
#include "bib.h"

int main(int argc, char *argv[]){    
    SetConsoleOutputCP(65001); // arrumar o portugues no vscode
    // setlocale(LC_ALL, "Portuguese"); // arrumar o portugues no devc++

    FILE *dicas, *existir, *existirIA;
    int linha = 0, coluna = 0,limite=0, menu, tabuleiro[8][8], tabuleiroIA[8][8], flag=0;
    char letraMenu;
    do{
        printf("--- OPÇÕES ---\n1- Novo jogo\n2- Carregar\n3- Sobre\n4- Sair\n----------------------\n");
		scanf("%c", &letraMenu);
        menu = atoi(&letraMenu);
        
	  	while((menu!=1) && (menu!=2) && (menu!=3) && (menu!=4)){
			system("cls");
        	puts("\nTente novamente com um valor válido!\n");
            clean_stdin();
       	 	printf("--- OPÇÕES ---\n1- Novo jogo\n2- Carregar\n3- Sobre\n4- Sair\n----------------------\n");
        	scanf("%c", &letraMenu);
       		menu = atoi(&letraMenu);
        }
		
        switch (menu){
	        case 1: // criar novo jogo 
	            dicas = fopen("dicas.txt", "w");
	            if(dicas == NULL){
	                printf("Erro ao carregar jogo, entre uma tecla e tente criar um jogo novo.\n");
	                exit(1);
	            }
	            
	            system("cls");
				
	            for(linha = 0; linha < 8; linha++){
	                for (coluna = 0; coluna < 8; coluna++){
	                    tabuleiro[linha][coluna] = 1;
	                }
	            }

	            for(linha = 0; linha < 8; linha++){
	                for (coluna = 0; coluna < 8; coluna++){
	                    tabuleiroIA[linha][coluna] = 1;
	                }
	            }
				clean_stdin();
	            iniciaSubmarino(tabuleiro, tabuleiroIA);
	            iniciaAviao(tabuleiro, tabuleiroIA);
	            iniciaEscolta(tabuleiro, tabuleiroIA);
	            iniciaCaca(tabuleiro, tabuleiroIA);
	            mostraTabuleiro(tabuleiro);
	            mostraTabuleiroIA(tabuleiroIA);
	            menuJogo(tabuleiro, &limite, tabuleiroIA);
	            break;
	        case 2: // carrega jogo
	            dicas = fopen("dicas.txt", "r");
	            if(dicas == NULL){
	                printf("Erro ao carregar jogo, entre uma tecla e tente criar um jogo novo.\n");
	                scanf("%d",&flag);
	                exit(1);
					break;
	            }
	            fscanf(dicas, "%d", &limite);
	            system("cls");
	            existir = fopen("salvarJogo.txt", "r");
	            existirIA = fopen("salvarJogoIA.txt", "r");
	            if(existir){
	                for (linha = 0; linha < 8; linha++){
	                    for (coluna = 0; coluna < 8; coluna++){
	                        fscanf(existir, "%d%*c", &tabuleiro[linha][coluna]);
	                    }
	                }
	                flag++;	
				}
	            if(existirIA){
	                for (linha = 0; linha < 8; linha++){
	                    for (coluna = 0; coluna < 8; coluna++){
	                        fscanf(existirIA, "%d%*c", &tabuleiroIA[linha][coluna]);
	                    }
	                }
					flag++;
	            }
	            if(flag==0){
	            	printf("Não existe jogo salvo, entre uma tecla e tente criar um jogo novo.\n");
	            	scanf("%d",&flag);
	            	exit(1);
					break;
				}else if(flag ==1){
					printf("Erro ao carregar jogo, entre uma tecla e tente criar um jogo novo.\n");
					scanf("%d",&flag);
					exit(1);
					break;
				}else if (flag==2){
					clean_stdin();
					mostraTabuleiro(tabuleiro);
	            	mostraTabuleiroIA(tabuleiroIA);
	            	menuJogo(tabuleiro, &limite, tabuleiroIA);
				}
	            break;
	        case 3:
	            printSobre();
	            clean_stdin();
	            break;
	        case 4:
	            puts("\nEncerrando!");
	            break;	        
        }
    }while (menu != 4);

    fclose(existir);
    fclose(dicas);
    return 0;
}

