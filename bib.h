typedef struct embarcacao{
	int tamanho;
	int aux1;
	int aux2;
}embarcacao;   //Struct pra definir caracteristicas das embarcacoes
embarcacao definir_str(int tipo); //define as embarcacoes

/* ----- FUNCIONALIDADES -----  */
void clean_stdin(void); //fflush
void printSobre(); //informacoes do programa

/* ----- MENUS -----  */
void menuJogo(int tabuleiro[][8], int *limite, int tabuleiroIA[][8]); //Mostra as opcoes dentro do jogo
void menuDisparar(int tabuleiro[][8], int checkSubmarino[], int checkAviao[], int checkCaca[], int checkEscolta[], int tabuleiroIA[][8]); //Mostra as opcoes de disparo

/* ----- ARQUIVOS E VISUALIZAÇÃO -----  */
void mostraTabuleiroIA(int tabuleiroIA[][8]); //printa tabuleiro do usuário na tela
void mostraTabuleiro(int tabuleiro[][8]); //printa o tabuleiro da IA na tela
void salvar(int tabuleiro[][8], int *limite, int tabuleiroIA[][8]); //salva nos .txt
void darDica(int tabuleiro[][8], int *limite); //funcao para dar as dicas para o usuario
void teste(int tiro[2], int tabuleiro[][8], int aux1, int aux2); //verificar se acertou uma embarcacao ou nao
void testeIA(int tiro[2], int tabuleiro[][8], int aux1, int aux2); //verificar se a IA acertou uma embarcacao ou nao

/* ----- EMBARCAÇÕES -----  */
void iniciaSubmarino(int tabuleiro[][8], int tabuleiroIA[][8]);
void iniciaAviao(int tabuleiro[][8], int tabuleiroIA[][8]);
void iniciaEscolta(int tabuleiro[][8], int tabuleiroIA[][8]);
void iniciaCaca(int tabuleiro[][8], int tabuleiroIA[][8]);

/* ----- VERIFICAR VITÓRIA -----  */
int acabou(int tabuleiro[][8], int tabuleiroIA[][8]);
