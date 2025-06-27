#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <math.h> 
#include <ctype.h>

//STRUCT SAIDA - PILHA
typedef struct saida{
	float dado;
	struct saida *outro;
	
}Saida; 

//FUNCAO PARA INSERIR OS NUMEROS NA PILHA
Saida* guardarDadoDeSaida(Saida *s, float num){
	Saida *novo = malloc(sizeof(Saida));//ALOCANDO MEMORIA DINAMICAMENTE
	
	if(novo){//VERIFICA SE A MEMERIA FOI ALOCADA
		novo->dado = num;
		novo->outro = s;
		return novo;
		
	} else {
		printf("Erro ao alocar espaco na pilha.");
		return NULL;
		
	}
	
} 

//FUNCAO PARA REMOVER NUMERO NA PILHA
Saida* removerDaSaida(Saida **s){
	Saida *remover = NULL; 
	
	if(*s){//VERIFICA SE A PILHA EST� VAZIA
		remover = *s;
		*s = remover->outro; 
		return remover; 
		
	} else {
		printf("A pilha esta vazia RR."); 
		return NULL;
		
	} 
	
} 

//STRUCT INFIXA - PILHA 
typedef struct pilha{
	char dado;
	struct pilha *outro;
	
}Pilha; 

//FUNCAO QUE INSERI OS CARACTERIS LIDOS DO ARQUIVO NA PILHA
Pilha* inserir(Pilha *pilha, char valor){
	Pilha *novo = malloc(sizeof(Pilha));
	
	if(novo){//VERIFICA SE A MEM�RIA FOI ALOCADA
		novo->dado = valor;
		novo->outro = pilha;
		return novo;
		
	} else {
		printf("Erro ao alocar espaco na pilha.");
		return NULL;
		
	}
	
}

//FUNCAO QUE REMOVE OS CARACTERES LIDIS DA PILHA
Pilha* removerDaPilha(Pilha **pilha){
	Pilha *remover = NULL; 
	
	if(*pilha){ //VERIFICA SE A PILHA ESTA VAZIA
		remover = *pilha;
		*pilha = remover->outro;  
		return remover;
		
	} else {
		printf("A pilha esta vazia PP."); 
		return NULL; 
		
	}   
	
}//FIM DA PILHA PRINCIPAL

//STRUCT POSFIXA - FILA
typedef struct fila{
	char dado;
	struct fila *outro;
	
}Fila;  

//FUNCAO PARA INSERIR OS CARACTERES NA FILA E FORMAR A EXPRESSAO POSFIXA
Fila* enviarNaFila(Fila **f, char dado){
	Fila *novo = malloc(sizeof(Fila));
	
	if(novo){//VERIFICA SE A MEM�RIA FOI ALOCADA
		novo->dado = dado;
		novo->outro = NULL;
		
		if(*f == NULL){
			*f = novo;
			 
		}else{
			Fila *au = *f;
			while(au->outro){
				au = au->outro; 
				
			}
			au->outro = novo;
			
		} 
		
	} else {
		printf("Erro ao alocar espaco na pilha.");  
		
	} 

}

//FUNCAO QUE REMOVE OS CARACTERES DA PILHA
Fila* removerDaFila(Fila **f){
	Fila *remover = NULL; 
	
	if(*f){ //VERIFICA SE A FILA ESTA VAZIA
		remover = *f;
		*f = remover->outro;  
		return remover;
		
	} else {
		printf("A pilha esta vazia.");  
		return NULL;
		
	}   
	
} 

//DEFININDO QUAL OPERACAO REALIZAR PARA CADA OPERADOR MATEMATICO
float calcularValores(float n1, float n2, char sinal){ 
	
	switch(sinal){
		case '+': 
			return n1 + n2; 
			break;
			
		case '-': 
			return n1 - n2; 
			break;
			
		case '*': 
			return n1 * n2; 
			break;
			
		case '/':  
			return n1 / n2;  
			break;
			
		case '^':  
			return pow(n1, n2); 
			break;
			
		default:
			return 0.0;
			
	}
	
}

//VERIFICANDO A ORDEN DE PROCEDENCIA DOS OPERADORES E PARENTESES
int verificarOrdenDeProcedencia(char sa, char se){
	switch(sa){
		case ')':
			if(se == '('){
				return 1;//PARENTESES BALANCEADOS
				
			}else{
				return 0;
				
			}
			break;
		case '-':
		case '+':
			if(se == '*' || se == '/' || se == '^'){
				return 1;
				
			}else{
				return 0;
				
			}
			break;
		case '/':
		case '*':
			if(se == '^'){
				return 1;
				
			}else{
				return 0;
				
			}
			break;
		case '^':  
				return 0; 
				
			break;
				
	}
	
} 

//FUN��O QUE RETORNA O VALOR DE CADA EXPRESSAO MATEMATICA NO ARQUIVO
float calcularExpressao(char car[]){
	//ARQUIVOS DE TEXTO 
	FILE *file = fopen("out.txt", "a");
	Saida *s = NULL, *n1, *n2;
	float r;
	int divPorZero = 0; 
	char arg[255] = {0};
	strcpy(arg, car);
	
	//PILHAS,FILAS E PONTEIROS
	char *token;
	token = strtok(arg, " ");
	
	while(token){  
		if(token[0] != ' '){  
			if(token[0] == '+' || token[0] == '-' || token[0] == '/' || token[0] == '*' || token[0] == '^'){  
				  
				n2 = removerDaSaida(&s);  //REMOVE O NUMERO QUE ESTA NO TOPO  
				n1 = removerDaSaida(&s); //ESTE AGORA � O TOPO - REMOVE TAMBEM  
				r = calcularValores(n1->dado, n2->dado, token[0]);//PEGA OS VALORES N1 E N2 E REALIZA A OPERCAO	
				if(n2->dado == 0){ 
					divPorZero = 1;
					s = NULL;
					
				}
				
				s = guardarDadoDeSaida(s, r);    
				free(n1);
				free(n2);  
				
			} else{    
			   	r = strtof(token, NULL);//converte o token em decimal 
			    if(r > 0){
				s = guardarDadoDeSaida(s, r); 
				
			    }  
			 
			}    
		  
		}
		token = strtok(NULL, " "); 
		
	}    
	
	if(divPorZero != 0){
		fprintf(file, "\n Erro. Divisao por zero.");
		
	}else{   
	  
		n1 = removerDaSaida(&s);  
		r = n1->dado;  
		free(n1);
		fprintf(file, "\n %.2f ", r); //ESCREVE O RESULTADO NOM ARQUIVO OUT.TXT 
			
	}  
	    
	fclose(file);
	s = NULL;	   
	
}

//LENDO O ARQUIVO DE ENTRADA in.txt
float lerArquivo(char caminho[]){
	//ARQUIVOS DE TEXTO
	FILE *arquivo = fopen(caminho, "r"); 
	FILE *file = fopen("out.txt", "a");
	
	//PILHAS,FILAS E PONTEIROS
	Pilha *pilha = NULL, *remover; 
	Fila *f = NULL, *rf; 
	Saida *s = NULL, *rs;  
	char c;
	 
	int retorno, i = 0;
	char parentesA[1], parentesF[1];
	
	if(arquivo){
		while(fgets(caminho, 255, arquivo) != '\0'){//PEGAR CADA LINHA DO ARQUIVO
			int a = 0;
			while(caminho[a] != '\0'){  
				if(caminho[a] != ' '){  
				c = caminho[a];
					if(caminho[a] == '('){
						parentesA[0] = caminho[a]; 
						pilha = inserir(pilha, caminho[a]);
						
					}else if(caminho[a] == ')'){ 
						parentesF[0] = caminho[a];   
							remover = removerDaPilha(&pilha);//REMOVE DA PILHA INFIXA 
							retorno = verificarOrdenDeProcedencia(caminho[a], remover->dado); //ESTA A VERIFICAR OS PARENTESE 
							
							if(remover->dado != '('){  
								enviarNaFila(&f, remover->dado); 
								enviarNaFila(&f, ' '); 
								
							} 
							
							while(retorno != 1){  
								remover = removerDaPilha(&pilha); 
								retorno = verificarOrdenDeProcedencia(caminho[a], remover->dado);  
								   
								if(remover->dado != '('){  
									enviarNaFila(&f, remover->dado); //ADICIONA NA FILA PARA FORMAR A EXPRESSAO POSFIXA 
									enviarNaFila(&f, ' '); 
									
								} 
								if(pilha == NULL){
									retorno = 1;
									
								}
									 			 
							}  
							retorno = 0; 
						
					}else if(caminho[a] == '+' || caminho[a] == '-' || caminho[a] == '/' || caminho[a] == '*' || caminho[a] == '^'){
						if(pilha == NULL){
							pilha = inserir(pilha, caminho[a]);
							
						}  else { 
							retorno = verificarOrdenDeProcedencia(caminho[a], pilha->dado);  
							if(retorno == 1){
								do{  
									remover = removerDaPilha(&pilha);    
									retorno = verificarOrdenDeProcedencia(caminho[a], remover->dado);  
									
									if(remover->dado != '('){  
										enviarNaFila(&f, remover->dado); 
										enviarNaFila(&f, ' ');  
										
									} 
									free(remover);
									if(pilha == NULL){
										retorno = 0;
										
									} 
									 
								}while(retorno != 0);  
								pilha = inserir(pilha, caminho[a]);
								
							}else{
								pilha = inserir(pilha, caminho[a]);
								
							}
						
						}  
						retorno = 0;
						
					} else if(isalpha(c)){
						i = 2;
						
					}else{ 
						enviarNaFila(&f, caminho[a]);  
						enviarNaFila(&f, ' '); 
					 
					}   
					
				}    
			a++;
				
			}     
			 
			while(pilha){//VERIFICA SE A PILHA ESTA VAZIA
				remover = removerDaPilha(&pilha); //SE NAO REMOVE DA PILHA    
				enviarNaFila(&f, remover->dado); //INSERI NA FILA PARA FORMAR A EXPRESSAO POSFIXA  
				enviarNaFila(&f, ' ');   
				free(remover);  
				
			}  
			
			char npf[255] = {0};
			int contador = 0;   
			while(f){
				npf[contador++] = f->dado; 
				f = f->outro;
				
			}    
			
			//VERIFICANDO SE OS PARENTESES FORAM BEM BALANCEADOS
			if(i == 2){
				fprintf(file, "\n Erro: Caracteres invalidos");  
				
			} else if(parentesA[0] != '(' && parentesF[0] != ')' || parentesA[0] == '(' && parentesF[0] == ')'){
				calcularExpressao(npf);      
				
			}else{ 
				fprintf(file, "\n Erro. Parenteses desbalanceados."); 	
				
			}   
			
			f = NULL;
			pilha = NULL; 
			parentesA[0] = ' ';  
			parentesF[0] = ' ';  
			retorno = 0;
			i = 0;
			
		} 
	printf("\n\n Analize das expressoes terminada com sucesso. \n Verifique o arquivo out.txt. Obrigado!\n");
	
	fclose(arquivo);  
	fclose(file);  
		 	
	}else{
		printf("\n\n Erro ao pegar o arquivo.\n Certifiquese de que digitou correctamente o caminho.\n"); 
		
	}  
	
}  

int main(){  
	char nomearquivo[255] = {0};
	printf("\n\t********* Ola, bem-vindo ao analizador de expressoes ***********\n");
	printf("\n 1-Informe o caminho aonde esta guardado o arquivo in.txt\n");
	printf(" Obs: caminho deve ser separado por duas barras invertidas (ex: c:\\users\\desktop\\in.txt)\n");
	printf(" R: ");
	scanf(" %s", &nomearquivo);
	lerArquivo(nomearquivo);    
	
	return 0;
}
