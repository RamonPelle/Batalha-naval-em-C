#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include "bib.h"

/* ----- DEFINES PADRÃO DA TABELA -----  */
#define mar 1
#define acertou 2
#define errou 3

/* ----- DEFINES DAS EMBARCAÇÕES -----  */
#define submarino 4
#define aviao 5
#define escolta 6
#define caca 7

/* ----- DEFINES DA VITÓRIA -----  */
#define ganhou 8
#define perdeu 9
#define sair 10

/* ----- DEFINIR TODOS OS VALORES DA EMBARCAÇÃO -----  */
embarcacao definir_str(int tipo){
	embarcacao nova;
	switch (tipo){
	case submarino:
		nova.tamanho = 2;
		nova.aux1 = 0;
		nova.aux2 = 0;
		return nova;
	case aviao:
		nova.tamanho = 4;
		nova.aux1 = 1;
		nova.aux2 = 0;
		return nova;
	case escolta:
		nova.tamanho = 3;
		nova.aux1 = 0;
		nova.aux2 = 1;
		return nova;
	case caca:
		nova.tamanho = 2;
		nova.aux1 = -1;
		nova.aux2 = -1;
		return nova;
	default:
		return nova;
	}
}

/* ----- VERIFICAR VITÓRIA -----  */
int acabou(int tabuleiro[][8], int tabuleiroIA[][8]){
	int linha, coluna;
	int checkSubmarino[2], checkAviao[2], checkCaca[2], checkEscolta[2];
	
	checkSubmarino[0] = 0; checkAviao[0] = 0; checkCaca[0] = 0; checkEscolta[0] = 0;
		for(linha =0; linha<8;linha++){
			for(coluna=0; coluna<8; coluna++){
				if(tabuleiroIA[linha][coluna]==submarino){
					checkSubmarino[0]++;
				}else if(tabuleiroIA[linha][coluna]==aviao){
					checkAviao[0]++;
				}else if(tabuleiroIA[linha][coluna]==escolta){
					checkEscolta[0]++;
				}else if(tabuleiroIA[linha][coluna]==caca){
					checkCaca[0]++;
				}
			}
		}

		checkSubmarino[1] = 0; checkAviao[1] = 0; checkCaca[1] = 0; checkEscolta[1] = 0;
		for(linha =0; linha<8;linha++){
			for(coluna=0; coluna<8; coluna++){
				if(tabuleiro[linha][coluna]==submarino){
					checkSubmarino[1]++;
				}else if(tabuleiro[linha][coluna]==aviao){
					checkAviao[1]++;
				}else if(tabuleiro[linha][coluna]==escolta){
					checkEscolta[1]++;
				}else if(tabuleiro[linha][coluna]==caca){
					checkCaca[1]++;
				}
			}
		}
		if( (checkSubmarino[1]==0)&&(checkAviao[1] == 0)&&(checkCaca[1] == 0)&&(checkEscolta[1] == 0)){
				return ganhou;
		}else if((checkSubmarino[0]==0)&&(checkAviao[0] == 0)&&(checkCaca[0] == 0)&&(checkEscolta[0] == 0)){
				return perdeu;
		}else {
				return sair;
		}
}

 /* ----- LIMPAR O BUFFER DO TECLADO -----  */
void clean_stdin(void){
    int c;
    do{
        c = getchar();
    } while (c != '\n' && c != EOF);
}

/* ----- INFORMAÇÕES DO PROGRAMA -----  */
void printSobre(){
	FILE *sobre;
	char c;
	system("cls");
	sobre = fopen("sobreMenu.txt", "r");
	if (sobre == NULL){
		perror("Erro ao abrir o arquivo sobreMenu.txt.\n");
		exit(1);
	}
	while (fscanf(sobre, "%c", &c) != EOF){
		printf("%c", c);
	}
	fclose(sobre);
}

/* ----- MOSTRA AS OPÇÕES DE DENTRO DO JOGO -----  */
void menuJogo(int tabuleiro[][8], int *limite, int tabuleiroIA[][8]){
	int linha,coluna,checkSubmarino[2], checkAviao[2], checkCaca[2], checkEscolta[2], menu, sairJogo, plimite, escolha;
	char letraMenu;
	plimite = *limite;
	
	do{
		checkSubmarino[0] = 0; checkAviao[0] = 0; checkCaca[0] = 0; checkEscolta[0] = 0;
		for(linha =0; linha<8;linha++){
			for(coluna=0; coluna<8; coluna++){
				if(tabuleiroIA[linha][coluna]==submarino){
					checkSubmarino[0]++;
				}else if(tabuleiroIA[linha][coluna]==aviao){
					checkAviao[0]++;
				}else if(tabuleiroIA[linha][coluna]==escolta){
					checkEscolta[0]++;
				}else if(tabuleiroIA[linha][coluna]==caca){
					checkCaca[0]++;
				}
			}
		}
		checkSubmarino[1] = 0; checkAviao[1] = 0; checkCaca[1] = 0; checkEscolta[1] = 0;
		for(linha =0; linha<8;linha++){
			for(coluna=0; coluna<8; coluna++){
				if(tabuleiro[linha][coluna]==submarino){
					checkSubmarino[1]++;
				}else if(tabuleiro[linha][coluna]==aviao){
					checkAviao[1]++;
				}else if(tabuleiro[linha][coluna]==escolta){
					checkEscolta[1]++;
				}else if(tabuleiro[linha][coluna]==caca){
					checkCaca[1]++;
				}
			}
		}		
		if((acabou(tabuleiro, tabuleiroIA)==ganhou)||(acabou(tabuleiro, tabuleiroIA)==perdeu)){
			menu=6;
		}else{
			printf("--- OPÇÕES ---\n1- Disparar\n2- Dica\n3- Salvar\n4- Sobre\n5- Sair\n----------------------\n");
				scanf("%c", &letraMenu);
				menu = atoi(&letraMenu);
				while((menu!=1) && (menu!=2) && (menu!=3) && (menu!=4) && (menu!=5)){
					system("cls");
					mostraTabuleiro(tabuleiro);
					mostraTabuleiroIA(tabuleiroIA);
			        puts("\nTente novamente com um valor válido!");
			        clean_stdin();	
			       	printf("--- OPÇÕES ---\n1- Disparar\n2- Dica\n3- Salvar\n4- Sobre\n5- Sair\n----------------------\n");
			        scanf("%c", &letraMenu);
			       	menu = atoi(&letraMenu);
				}
		}
		switch (menu){
		case 1:
			menuDisparar(tabuleiro,checkSubmarino,checkAviao,checkCaca,checkEscolta,tabuleiroIA);
			break;
		case 2:
			darDica(tabuleiro, &plimite);
			break;
		case 3:
			salvar(tabuleiro, &plimite, tabuleiroIA);
			break;
		case 4:
			clean_stdin();
			printSobre();
			break;
		case 5:
			do{
				printf("\nDeseja salvar? [1 = Sim || 2 = Não]\n");
				scanf("%d", &sairJogo);
			}while (sairJogo < 1 || sairJogo > 2);
			
			if (sairJogo == 1){
				salvar(tabuleiro, &plimite, tabuleiroIA);
			}
			puts("\nEncerrando!");
			exit (sair);
			break;
		case 6:
			if(acabou(tabuleiro, tabuleiroIA)==ganhou){
				puts("PARABÉNS!!! VOCÊ GANHOU!!!");
				do{
					printf("\nDeseja jogar novamente? [1 = Sim || 2 = Não]\n");
					scanf("%d", &escolha);
				}while (escolha < 1 || escolha > 2);
				
				if (escolha == 1){
					clean_stdin();
					break;			
				}else{
					puts("\nEncerrando!");
					exit (sair);
				}
			}else if(acabou(tabuleiro, tabuleiroIA)==perdeu){
				puts("QUE PENA :( VOCÊ PERDEU!");
				do{
					printf("\nDeseja jogar novamente? [1 = Sim || 2 = Não]\n");
					scanf("%d", &escolha);
					clean_stdin();
				}while (escolha < 1 || escolha > 2);
				
				if (escolha == 1){
					clean_stdin();
					break;				
				}else{
					puts("\nEncerrando!");
					exit (sair);
				}
			}		
		}
	}while ((menu == 1)||(menu == 2)||(menu == 3)||(menu == 4));
}

/* ----- MOSTRA AS OPÇÕES DE DISPARO -----  */
void menuDisparar(int tabuleiro[][8], int checkSubmarino[], int checkAviao[], int checkCaca[], int checkEscolta[], int tabuleiroIA[][8]){
	system("cls");
	mostraTabuleiro(tabuleiro);
	int contErro=0, menu, tiro[2],morte=0,menuIA, cont=0;
	char c[2], letraMenu;
	
	if(acabou(tabuleiro, tabuleiroIA)==perdeu){
		puts("PERDEU");
	}else{
		tiro[0] = -1;
		tiro[1] = -1;
		while(morte==0){
			printf("--- OPÇÕES ---\n1- Submarino          (1 tiro)\n2- Porta-avião        (2 tiros, alvo + baixo)\n3- Navil de Escolta   (2 tiros, alvo + direita)\n4- Caça               (5 tiros, formato de +)\n----------------------\n");
			puts("Digite a embarcação desejada: ");
			clean_stdin();
			scanf("%c", &letraMenu);
	       	menu = atoi(&letraMenu);

			while((menu!=1) && (menu!=2) && (menu!=3) && (menu!=4)){
				system("cls");
				mostraTabuleiro(tabuleiro);
				puts("\nTente novamente com um valor válido!\n");
				clean_stdin();
				printf("1- Submarino          (1 tiro)\n2- Porta-avião        (2 tiros, alvo + baixo)\n3- Navil de Escolta   (2 tiros, alvo + direita)\n4- Caça               (5 tiros, formato de +)\n----------------------\n");
				puts("Digite a embarcação desejada: ");
				scanf("%c", &letraMenu);
				menu = atoi(&letraMenu);
			}
	
			while(tiro[0]<0 || tiro[0]>7){
				clean_stdin();
				printf("Exemplo: A1\nLinha e coluna: ");
				gets(c);
				if(c[0]=='A' || c[0]=='a'){
					tiro[0] = 0;
				}else if(c[0]=='B' || c[0]=='b'){
					tiro[0] = 1;
				}else if(c[0]=='C' || c[0]=='c'){
					tiro[0] = 2;
				}else if(c[0]=='D' || c[0]=='d'){
					tiro[0] = 3;
				}else if(c[0]=='E' || c[0]=='e'){
					tiro[0] = 4;
				}else if(c[0]=='F' || c[0]=='f'){
					tiro[0] = 5;
				}else if(c[0]=='G' || c[0]=='g'){
					tiro[0] = 6;
				}else if(c[0]=='H' || c[0]=='h'){
					tiro[0] = 7;
				}else{
					printf("Operação inválida, pressione alguma enter e tente novamente.");
					printf("\n");
					contErro++;
				}
				tiro[1] = atoi(&c[1]);
				if((tiro[1]<1 || tiro[1]>8) && contErro==0){
					printf("Operação inválida, pressione alguma enter e tente novamente.");
					printf("\n");
					tiro[0] = -1;
				}
				tiro[1]--;  
			}
			switch (menu){
				case 1: ;
					if(checkSubmarino[0]>0){
						embarcacao submarino_str = definir_str(submarino);
						teste(tiro, tabuleiro, submarino_str.aux1, submarino_str.aux2);
						morte++;
						break;
					}else{
						printf("\n\n-------- SUBMARINO JÁ FOI DESTRUÍDO. TENTE NOVAMENTE COM OUTRA EMBARCAÇÃO. --------\n\n");
						break;
					}	
				case 2: ;
					if(checkAviao[0]>0){
						embarcacao aviao_str = definir_str(aviao);
						teste(tiro, tabuleiro, aviao_str.aux1, aviao_str.aux2);
						morte++;
						break;
					}else{
						printf("\n\n-------- PORTA-AVIÃO JÁ FOI DESTRUÍDO. TENTE NOVAMENTE COM OUTRA EMBARCAÇÃO. --------\n\n");
						break;
					}
				case 3: ;
					if(checkEscolta[0]>0){
						embarcacao escolta_str = definir_str(escolta);
						teste(tiro, tabuleiro, escolta_str.aux1, escolta_str.aux2);
						morte++;
						break;
					}else{
						printf("\n\n-------- NAVIO DE ESCOLTA JÁ FOI DESTRUÍDO. TENTE NOVAMENTE COM OUTRA EMBARCAÇÃO. --------\n\n");
						break;
					}
				case 4: ;
					if(checkCaca[0]>0){
						embarcacao caca_str = definir_str(caca);
						teste(tiro, tabuleiro, caca_str.aux1, caca_str.aux2);
						morte++;
						break;
					}else{
						printf("\n\n-------- CAÇA JÁ FOI DESTRUÍDO. TENTE NOVAMENTE COM OUTRA EMBARCAÇÃO. --------\n\n");
						break;
					}
			}
		}	
	}
	
	if(acabou(tabuleiro, tabuleiroIA)==ganhou){
		puts("GANHOU!!");
	}else{
		morte=0;
		srand(time(NULL));
		while(morte==0){
			menuIA = rand()%4;
			cont=0;
			while(cont==0){
				tiro[0]=rand()%8;
				tiro[1]=rand()%8;
				if((tabuleiroIA[tiro[0]][tiro[1]] != acertou) && (tabuleiroIA[tiro[0]][tiro[1]] != errou)){
					switch (menuIA){
						case 0: ;
							if(checkSubmarino[1]>0){
								embarcacao submarino_str = definir_str(submarino);
								testeIA(tiro, tabuleiroIA, submarino_str.aux1, submarino_str.aux2);
								morte++;
							}
							break;
						case 1: ;
							if(checkAviao[1]>0){
								embarcacao aviao_str = definir_str(aviao);
								testeIA(tiro, tabuleiroIA, aviao_str.aux1, aviao_str.aux2);
								morte++;
							} 
							break;
						case 2: ;
							if(checkEscolta[1]>0){
								embarcacao escolta_str = definir_str(escolta);
								testeIA(tiro, tabuleiroIA, escolta_str.aux1, escolta_str.aux2);
								morte++;
							}
							break;
						case 3: ;
							if(checkCaca[1]>0){
								embarcacao caca_str = definir_str(caca);
								testeIA(tiro, tabuleiroIA, caca_str.aux1, caca_str.aux2);
								morte++;
							}
							break;
					}	
					cont++;
				}
			}
		}
	}
	
	system("cls");
	mostraTabuleiro(tabuleiro);
	mostraTabuleiroIA(tabuleiroIA);
}

/* ----- MOSTRA O TABULEIRO QUE O USUÁRIO ATIRA (TABULEIRO DO CPU) -----  */
void mostraTabuleiro(int tabuleiro[][8]){
	int linha, coluna;
	char letras[9] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
	printf("\t\t\t   ---------------\n\t\t\t   |Tabuleiro CPU|\n\t\t\t   ---------------\n");
	printf("\t1 \t2 \t3 \t4 \t5 \t6 \t7 \t8\n");
	
	for (linha = 0; linha < 8; linha++){
		printf("%c",letras[linha]);
		for (coluna = 0; coluna < 8; coluna++){
			switch (tabuleiro[linha][coluna]){
			case mar:
				printf("\t~");
				break;
			case submarino:
				printf("\t~");
				break;
			case aviao:
				printf("\t~");
				break;
			case escolta:
				printf("\t~");
				break;
			case caca:
				printf("\t~");
				break;
			case errou:
				printf("\t*");
				break;
			case acertou:
				printf("\tX");
				break;
			}
		}
		printf("\n");
	}
	printf("\n");
}

/* ----- MOSTRA O TABULEIRO QUE A IA ATIRA (TABULEIRO DO USUÁRIO) -----  */
void mostraTabuleiroIA(int tabuleiroIA[][8]){
	int linha, coluna;
    char letras[9] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    printf("\t\t\t -------------------\n\t\t\t |Tabuleiro Usuario|\n\t\t\t -------------------\n");
    printf("\t1 \t2 \t3 \t4 \t5 \t6 \t7 \t8\n");

    for (linha = 0; linha < 8; linha++){
        printf("%c",letras[linha]);
        for (coluna = 0; coluna < 8; coluna++){
            switch (tabuleiroIA[linha][coluna]){
            case mar:
                printf("\t~");
                break;
            case submarino:
                printf("\tS");
                break;
            case aviao:
                printf("\tA");
                break;
            case escolta:
                printf("\tE");
                break;
            case caca:
                printf("\tC");
                break;
            case errou:
                printf("\t*");
                break;
            case acertou:
                printf("\tX");
                break;
            }
        }
        printf("\n");
    }
}

/* ----- SALVA TODAS AS INFORMAÇÕES -----  */
void salvar(int tabuleiro[][8], int *limite, int tabuleiroIA[][8]){
	clean_stdin();
    int linha, coluna;
    FILE *salvarJogo, *salvarJogoIA, *dicas;
    salvarJogo = fopen("salvarJogo.txt", "w");
    if (salvarJogo == NULL){
        perror("Erro ao abrir o arquivo salvarJogo.txt.\n");
        exit(1);
    }

    salvarJogoIA = fopen("salvarJogoIA.txt", "w");
    if (salvarJogoIA == NULL){
        perror("Erro ao abrir o arquivo salvarJogoIA.txt.\n");
        exit(1);
    }
    dicas = fopen("dicas.txt", "w");
    if (dicas == NULL){
        perror("Erro ao abrir o arquivo dicas.txt.\n");
        exit(1);
    }
	
    fprintf(dicas, "%d", *limite);

    for (linha = 0; linha < 8; linha++){
        for (coluna = 0; coluna < 8; coluna++){
            switch (tabuleiro[linha][coluna])
            {
            case mar:
                fprintf(salvarJogo, "%d ", mar);
                break;
            case submarino:
                fprintf(salvarJogo, "%d ", submarino);
                break;
            case aviao:
                fprintf(salvarJogo, "%d ", aviao);
                break;
            case escolta:
                fprintf(salvarJogo, "%d ", escolta);
                break;
            case caca:
                fprintf(salvarJogo, "%d ", caca);
                break;
            case errou:
                fprintf(salvarJogo, "%d ", errou);
                break;
            case acertou:
                fprintf(salvarJogo, "%d ", acertou);
                break;
            }
        }
    }
    
    for (linha = 0; linha < 8; linha++){
        for (coluna = 0; coluna < 8; coluna++){
            switch (tabuleiroIA[linha][coluna])
            {
            case mar:
                fprintf(salvarJogoIA, "%d ", mar);
                break;
            case submarino:
                fprintf(salvarJogoIA, "%d ", submarino);
                break;
            case aviao:
                fprintf(salvarJogoIA, "%d ", aviao);
                break;
            case escolta:
                fprintf(salvarJogoIA, "%d ", escolta);
                break;
            case caca:
                fprintf(salvarJogoIA, "%d ", caca);
                break;
            case errou:
                fprintf(salvarJogoIA, "%d ", errou);
                break;
            case acertou:
                fprintf(salvarJogoIA, "%d ", acertou);
                break;
            }
        }
    }
	system("cls");
	mostraTabuleiro(tabuleiro);
	mostraTabuleiroIA(tabuleiroIA);
    printf("\nJogo salvo!\n\n");
    fclose(salvarJogo);
    fclose(salvarJogoIA);
    fclose(dicas);
}

/* ----- DÁ AS DICAS -----  */
void darDica(int tabuleiro[][8], int *limite){
	system("cls");
	mostraTabuleiro(tabuleiro);
	int contErro=0,tiro[2];
	char c[2];
	if ((*limite) < 3){
		puts("\n--------Você tem direito a 3 dicas! Use-as com sabedoria.--------");
		while(tiro[0]<0 || tiro[0]>7){
			clean_stdin();
			printf("Exemplo: A1\nLinha e coluna: ");
			gets(c);
			if(c[0]=='A' || c[0]=='a'){
				tiro[0] = 0;
			}else if(c[0]=='B' || c[0]=='b'){
				tiro[0] = 1;
			}else if(c[0]=='C' || c[0]=='c'){
				tiro[0] = 2;
			}else if(c[0]=='D' || c[0]=='d'){
				tiro[0] = 3;
			}else if(c[0]=='E' || c[0]=='e'){
				tiro[0] = 4;
			}else if(c[0]=='F' || c[0]=='f'){
				tiro[0] = 5;
			}else if(c[0]=='G' || c[0]=='g'){
				tiro[0] = 6;
			}else if(c[0]=='H' || c[0]=='h'){
				tiro[0] = 7;
			}else{
				printf("Operação inválida, pressione alguma enter e tente novamente.");
				printf("\n");
				contErro++;
			}
			tiro[1] = atoi(&c[1]);
			if((tiro[1]<1 || tiro[1]>8) && contErro==0){
				printf("Operação inválida, pressione alguma enter e tente novamente.");
				printf("\n");
				tiro[0] = -1;
			}
			tiro[1]--;  
		};
		if (tabuleiro[tiro[0]][tiro[1]] == mar){
			printf("\nNÃO TEM NENHUMA EMBARCAÇÃO EM %c%c.\n\n",c[0],c[1]);
		}else if (tabuleiro[tiro[0]][tiro[1]] == errou){
			printf("\nVOCÊ JÁ ATIROU EM %c%c E ERROU.\n\n",c[0],c[1]);
		}else if (tabuleiro[tiro[0]][tiro[1]] == acertou){
			printf("\nVOCÊ JÁ ATIROU EM %c%c E ACERTOU.\n\n",c[0],c[1]);
		}else{
			printf("\nTEM UMA EMBARCAÇÃO EM %c%c.\n\n",c[0],c[1]);
		}
	}
	else{
		puts("Você já usou todas as suas dicas.\n");
		clean_stdin();
	}
	(*limite)++;
}

/* ----- VERIFICAR SE O USUÁRIO ACERTOU UMA EMBARCAÇÃO -----  */
void teste(int tiro[2], int tabuleiro[][8], int aux1, int aux2){
	int i, j;
	if (aux1 == -1 && aux2 == -1){ //caça
		if(tiro[0] == 0 && tiro[1] == 0){ //SOLUCAO PRO A1 - GAMBIARRA
			if(tabuleiro[tiro[0] + 1][tiro[1]] != mar && tabuleiro[tiro[0] + 1][tiro[1]] != errou){
				tabuleiro[tiro[0] + 1][tiro[1]] = acertou;
			}else{
				tabuleiro[tiro[0] + 1][tiro[1]] = errou;
			}
			
			if(tabuleiro[tiro[0]][tiro[1]+1] != mar && tabuleiro[tiro[0]][tiro[1]+1] != errou){
				tabuleiro[tiro[0]][tiro[1]+1] = acertou;
			}else{
				tabuleiro[tiro[0]][tiro[1]+1] = errou;
			}
			
			if(tabuleiro[tiro[0]][tiro[1]] != mar && tabuleiro[tiro[0]][tiro[1]] != errou){
				tabuleiro[tiro[0]][tiro[1]] = acertou;
			}else{
				tabuleiro[tiro[0]][tiro[1]] = errou;
			}			
		}
		/// fim da gambiarra
		for (i = -1; i <= 1; i++){
			if(tiro[0]+i<0 || tiro[0]+i>7){
				i++;
			}else if (tabuleiro[tiro[0] + i][tiro[1]] != mar && tabuleiro[tiro[0] + i][tiro[1]] != errou){
				tabuleiro[tiro[0] + i][tiro[1]] = acertou;
			}
			else{
				tabuleiro[tiro[0] + i][tiro[1]] = errou;
			}
		}
		for (j = -1; j <= 1; j++){
			if(tiro[1]+j<0 || tiro[1]+j>7){
				j++;
			}else if (tabuleiro[tiro[0]][tiro[1] + j] != mar && tabuleiro[tiro[0]][tiro[1] + j] != errou){
				tabuleiro[tiro[0]][tiro[1] + j] = acertou;
			}
			else{
				tabuleiro[tiro[0]][tiro[1] + j] = errou;
			}
		}
	}
	else{
		for (i = 0; i <= aux1; i++){
			for (j = 0; j <= aux2; j++){
				if(tiro[0]+i<0 || tiro[0]+i>7){
					i++;
				}else if(tiro[1]+j<0 || tiro[1]+j>7){
					j++;
				}else if (tabuleiro[tiro[0] + i][tiro[1] + j] != mar && tabuleiro[tiro[0] + i][tiro[1] + j] != errou){
					tabuleiro[tiro[0] + i][tiro[1] + j] = acertou;
				}
				else{
					tabuleiro[tiro[0] + i][tiro[1] + j] = errou;
				}
			}
		}
	}
}

/* ----- VERIFICAR SE A IA ACERTOU UMA EMBARCAÇÃO -----  */
void testeIA(int tiro[2], int tabuleiroIA[][8], int aux1, int aux2){
	int i, j;
	if (aux1 == -1 && aux2 == -1){
		for (i = -1; i <= 1; i++){
			if(tiro[0]+i<0 || tiro[0]+i>7){
				i++;
			}else if (tabuleiroIA[tiro[0] + i][tiro[1]] != mar && tabuleiroIA[tiro[0] + i][tiro[1]] != errou){
				tabuleiroIA[tiro[0] + i][tiro[1]] = acertou;
			}
			else{
				tabuleiroIA[tiro[0] + i][tiro[1]] = errou;
			}
		}
		for (j = -1; j <= 1; j++){
			if(tiro[1]+j<0 || tiro[1]+j>7){
				j++;
			}else if (tabuleiroIA[tiro[0]][tiro[1] + j] != mar && tabuleiroIA[tiro[0]][tiro[1] + j] != errou){
				tabuleiroIA[tiro[0]][tiro[1] + j] = acertou;
			}
			else{
				tabuleiroIA[tiro[0]][tiro[1] + j] = errou;
			}
		}
	}
	else{
		for (i = 0; i <= aux1; i++){
			for (j = 0; j <= aux2; j++){
				if(tiro[0]+i<0 || tiro[0]+i>7){
					i++;
				}else if(tiro[1]+j<0 || tiro[1]+j>7){
					j++;
				}else if (tabuleiroIA[tiro[0] + i][tiro[1] + j] != mar && tabuleiroIA[tiro[0] + i][tiro[1] + j] != errou){
					tabuleiroIA[tiro[0] + i][tiro[1] + j] = acertou;
				}
				else{
					tabuleiroIA[tiro[0] + i][tiro[1] + j] = errou;
				}
			}
		}
	}

}

//														 ---------------------------------------  
//														 ----- INICIA TODAS AS EMBARCAÇÕES -----  
//														 ---------------------------------------  

/* ----- SUBMARINO -----  */
void iniciaSubmarino( int tabuleiro[][8], int tabuleiroIA[][8]){
    srand(time(NULL));
    int cont=0, l, c, tam, i;
    embarcacao submarino_str=definir_str(submarino);
    tam=submarino_str.tamanho;
    while(cont<1){
        l=rand()%8;
        c=rand()%7;
        if((tabuleiro[l][c]==mar)&&(tabuleiro[l][c+1]==mar)){
            cont++;
            for(i=0; i<tam; i++){
                tabuleiro[l][c+i]=submarino;
            }
        }
    }
    
    cont=0;
    while(cont<1){
        l=rand()%8;
        c=rand()%7;
        if((tabuleiroIA[l][c]==mar)&&(tabuleiroIA[l][c+1]==mar)){
            cont++;
            for(i=0; i<tam; i++){
                tabuleiroIA[l][c+i]=submarino;
            }
        }
    }
}

/* ----- PORTA-AVIÕES -----  */
void iniciaAviao( int tabuleiro[][8], int tabuleiroIA[][8]){
    srand(time(NULL));
    int cont=0, l, c, tam, i;
    embarcacao aviao_str=definir_str(aviao);
    tam=aviao_str.tamanho;
    while(cont<1){
        l=rand()%8;
        c=rand()%5;
        if((tabuleiro[l][c]==mar)&&(tabuleiro[l][c+1]==mar)&&(tabuleiro[l][c+2]==mar)&&(tabuleiro[l][c+3]==mar)){
            cont++;
            for(i=0; i<tam; i++){
                tabuleiro[l][c+i]=aviao;
           }
        }
    }
    cont=0;
    while(cont<1){
        l=rand()%8;
        c=rand()%5;
        if((tabuleiroIA[l][c]==mar)&&(tabuleiroIA[l][c+1]==mar)&&(tabuleiroIA[l][c+2]==mar)&&(tabuleiroIA[l][c+3]==mar)){
            cont++;
            for(i=0; i<tam; i++){
                tabuleiroIA[l][c+i]=aviao;
           }
        }
    }
}

/* ----- NAVIO DE ESCOLTA -----  */
void iniciaEscolta( int tabuleiro[][8], int tabuleiroIA[][8]){
    srand(time(NULL));
    int cont=0, l, c, tam, i;
    embarcacao escolta_str=definir_str(escolta);
    tam=escolta_str.tamanho;
    while(cont<1){
        l=rand()%8;
        c=rand()%6;
        if((tabuleiro[l][c]==mar)&&(tabuleiro[l][c+1]==mar)&&(tabuleiro[l][c+2]==mar)){
            cont++;
            for(i=0; i<tam; i++){
                tabuleiro[l][c+i]=escolta;
           }
        }
    }
    cont=0;
    while(cont<1){
        l=rand()%8;
        c=rand()%6;
        if((tabuleiroIA[l][c]==mar)&&(tabuleiroIA[l][c+1]==mar)&&(tabuleiroIA[l][c+2]==mar)){
            cont++;
            for(i=0; i<tam; i++){
                tabuleiroIA[l][c+i]=escolta;
           }
        }
    }
}

/* ----- CAÇA -----  */
void iniciaCaca( int tabuleiro[][8], int tabuleiroIA[][8]){
    srand(time(NULL));
    int cont=0, l, c, tam, i;
    embarcacao caca_str=definir_str(caca);
    tam=caca_str.tamanho;
    while(cont<1){
        l=rand()%8;
        c=rand()%7;
        if((tabuleiro[l][c]==mar)&&(tabuleiro[l][c+1]==mar)){
            cont++;
            for(i=0; i<tam; i++){
                tabuleiro[l][c+i]=caca;
           }
        }
    }
    cont=0;
    while(cont<1){
        l=rand()%8;
        c=rand()%7;
        if((tabuleiroIA[l][c]==mar)&&(tabuleiroIA[l][c+1]==mar)){
            cont++;
            for(i=0; i<tam; i++){
                tabuleiroIA[l][c+i]=caca;
           }
        }
    }
}