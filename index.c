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
	
	if(*s){//VERIFICA SE A PILHA ESTÁ VAZIA
		remover = *s;
		*s = remover->outro;  
		
	} else {
		printf("A pilha esta vazia RR."); 
		
	}
	return remover;
	
} 

//STRUCT INFIXA - PILHA 
typedef struct lista{
	char dado;
	struct lista *outro;
	
}Pilha; 

//FUNCAO QUE INSERI OS CARACTERIS LIDOS DO ARQUIVO NA PILHA
Pilha* inserir(Pilha *pilha, char valor){
	Pilha *novo = malloc(sizeof(Pilha));
	
	if(novo){//VERIFICA SE A MEMÓRIA FOI ALOCADA
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
		
	} else {
		printf("A pilha esta vazia PP.");  
		
	}  
	return remover;
	
}//FIM DA PILHA PRINCIPAL

//STRUCT POSFIXA - FILA
typedef struct fila{
	char dado;
	struct fila *outro;
	
}Fila; 

//FUNCAO PARA INSERIR OS CARACTERES NA FILA E FORMAR A EXPRESSAO POSFIXA
Fila* enviarNaFila(Fila **f, char dado){
	Fila *au, *novo = malloc(sizeof(Saida));
	
	if(novo){//VERIFICA SE A MEMÓRIA FOI ALOCADA
		novo->dado = dado;
		novo->outro = NULL;
		if(*f == NULL){
			*f = novo;
			 
		}else{
			au = *f;
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
		
	} else {
		printf("A pilha esta vazia.");  
		
	}  
	return remover;
	
} 

//DEFININDO QUAL OPERACAO REALIZAR PARA CADA OPERADOR MATEMATICO
float calcularEpressao(float n1, float n2, char sinal){ 
	
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
			if(se == '*' || se == '/' || se == '+' || se == '-'){
				return 1;
				
			}else{
				return 0;
				
			}
			break;
				
	}
	
} 

//FUNÇÃO QUE RETORNA O VALOR DE CADA EXPRESSAO MATEMATICA NO ARQUIVO
float calcular(char car[]){
	//ARQUIVOS DE TEXTO
	FILE *file = fopen("out.txt", "a");
	Saida *s = NULL, *n1, *n2;
	float r; 
	char arg[255];
	strcpy(arg, car);
	
	//PILHAS,FILAS E PONTEIROS
	char *token;
	token = strtok(arg, " ");
	
	while(token){ 
	char c = token[0]; 
	if(token[0] != ' '){  
		if(token[0] == '+' || token[0] == '-' || token[0] == '/' || token[0] == '*' || token[0] == '^'){  
			  
			n2 = removerDaSaida(&s);  //REMOVE O NUMERO QUE ESTA NO TOPO
			n1 = removerDaSaida(&s); //ESTE AGORA É O TOPO - REMOVE TAMBEM
			r = calcularEpressao(n1->dado, n2->dado, token[0]);//PEGA OS VALORES N1 E N2 E REALIZA A OPERCAO
			s = guardarDadoDeSaida(s, r);
			free(n1);
			free(n2);  
			
		} else{    
		   	r = strtol(token, NULL, 10);//converte o token em decimal
			s = guardarDadoDeSaida(s, r);
		 
		}    
	  
	}
		token = strtok(NULL, " "); 
		
	}   
	
	if(s != NULL){
		n1 = removerDaSaida(&s);  
		r = n1->dado; 
		free(n1);  
				fprintf(file, "\n %.2f ", r); //ESCREVE O RESULTADO NOM ARQUIVO OUT.TXT
			fclose(file); 
		return r;
		
	}	   
	
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
	char ep[255];
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
			
			label:
			if(pilha){//VERIFICA SE A PILHA ESTA VAZIA
				remover = removerDaPilha(&pilha); //SE NAO REMOVE DA PILHA    
				enviarNaFila(&f, remover->dado); //INSERI NA FILA PARA FORMAR A EXPRESSAO POSFIXA  
				enviarNaFila(&f, ' '); 
				goto label;    
				
			} 
			  
			int b = 0;   
			while(f){
				ep[b] = f->dado; 
				f = f->outro;
				b++;
				
			}
			char dest[255];
			strcpy(dest, ep);        
			
			//VERIFICANDO SE OS PARENTESES FORAM BEM BALANCEADOS
			if(i == 2){
				fprintf(file, "\nErro: Caracteres invalidos"); 
				printf("\nErro: Caracteres invalidos"); 
				
			} else { 
			if(parentesA[0] != '(' && parentesF[0] != ')'){  
				printf("\nResultado: %.2f ", calcular(ep)); 
				
			} else if(parentesA[0] == '(' && parentesF[0] == ')'){
				printf("\nResultado: %.2f ", calcular(ep));      
				
			}else{ 
				fprintf(file, "Erro. Parenteses desbalanceados.\n"); 	
				
			}   
			
			}
				fclose(file);
			
			f = '\0';
			pilha = '\0';
			s = '\0';
			parentesA[0] = ' ';  
			parentesF[0] = ' ';  
			retorno = 0;
			i = 0;
			
		} 
	
	fclose(arquivo);  
	fclose(file);  	 	
	}else{
		printf("Erro ao pegar o arquivo.\n Certifiquese de que digitou correctamente o caminho."); 
		
	}  
	
}  

int main(){ 
	char nomearquivo[255] = "c:\\users\\euricoAntonio\\desktop\\in.txt";
	lerArquivo(nomearquivo);   
	/*char nomearquivo[255];
	printf("\nInforme o caminho aonde esta guardado o arquivo in.txt\n");
	printf("Obs: caminho deve ser separado por duas barras invertidas (ex: c:\\users\\desktop\\in.txt)\n");
	scanf("%s", &nomearquivo);
	lerArquivo(nomearquivo);*/   
	
	return 0;
}
