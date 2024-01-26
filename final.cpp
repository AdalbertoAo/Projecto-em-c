#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include<string.h>
#include <windows.h>

//_______registos________
//CONTA
struct CONTA{
	int numero_conta;
	float saldo;
	int estado;
	int codigo_conta;
};
//PESSOA
struct PESSOA{
	int codigo;
	char nome[80];
	char morada[100];
	char bi_nif[20];
	int telefone;
};
typedef struct PESSOA pessoa;
typedef struct CONTA conta;
//__________________________

//__________funcoes de pesquisa_________
//pesquisar conta...
int pesquisar_conta (int codigo);
//pesquisar cliente...	
int pesquisar_registo (int codigo);
//pesquisar conta pelo numero de conta
int pesquisar_pelo_numero_conta (int numero_conta);
//_________-FUNCOES_____________________
bool cadastrar_cliente(pessoa p);
void listar_clientes ();
bool abertura_conta (pessoa p, int tipo_conta);
bool atualizar_dados (pessoa p, int codigo_cliente);
bool depositar_dinheiro (int numero_conta, float valor);
bool levantar_dinheiro (int numero_conta, float valor);
float consultar_saldo (int numero_conta);
bool transferir_dinheiro (int numero_conta_enviar, int numero_conta_receber, float valor);
//______________________________________

//variaveis de escopo global
conta v_contas[1000];
pessoa v_clientes[1000];
int total_clientes, total_contas;
FILE *Base_dados;

//____FUNCOES MANIPULADORAS DO FICHEIRO_____________
//FUNCAO CRIAR FICHEIRO
 void criarficheiro(){

Base_dados=fopen("banco_de_dados.txt","a");
if(Base_dados==NULL){
    printf("Base dados nao existe\n");
}
printf("Ficheiro criado! \n");
fclose(Base_dados);
 }
//FUNCAO ESCREVER
void escrever_ficheiro(){
    Base_dados= fopen("banco_de_dados.txt","w");
      int n;
    if(Base_dados==NULL){
        printf("Impossivel escrever\n");
    }

    for(n=0;n<total_clientes;n++){


        fprintf(Base_dados,"%d;%s;%s;%s;%d;",v_clientes[n].codigo,v_clientes[n].nome,v_clientes[n].bi_nif,v_clientes[n].morada,v_clientes[n].telefone);
		int i = pesquisar_conta(v_clientes[n].codigo);
		if (i != -1){
			fprintf(Base_dados,"%i;%f;%i;%i" , v_contas[i].numero_conta, v_contas[i].saldo, v_contas[i].estado, v_contas[i].codigo_conta);

		}
		fprintf(Base_dados, "\n");
    }
    fclose(Base_dados);
}
//FUNCAO CARREGAR DADOS DO FICHEIRO NOS VECTORES
void carregar_ficheiro(){
    pessoa p;
	conta c;
     Base_dados = fopen("banco_de_dados.txt", "r");
	 char linhas[1000];
    if (Base_dados == NULL){
        printf("Houve um erro ao abrir o ficheiro.");
    }else if (Base_dados != NULL){
    	printf("Ficheiro aberto!");
	}

		while(fscanf(Base_dados, "%[^\n]\n", &linhas) == 1){

			char *quebras=strtok(linhas, ";");
			char *linha_quebrada[10];


			int search = 0;
			while (quebras != NULL) {
				linha_quebrada[search] = quebras;
				quebras = strtok(NULL, ";");

				search++;
			}

		    sscanf(linha_quebrada[0], "%d", &p.codigo);
			strcpy(p.nome, linha_quebrada[1]);
			strcpy(p.bi_nif, linha_quebrada[2]);
			strcpy(p.morada, linha_quebrada[3]);
			sscanf(linha_quebrada[4], "%d", &p.telefone);
			v_clientes[total_clientes] = p;
			total_clientes++;

			if (search == 5){
				continue;
			}else{

				sscanf(linha_quebrada[5], "%d", &c.numero_conta);
				sscanf(linha_quebrada[6], "%f", &c.saldo);
				sscanf(linha_quebrada[7], "%d", &c.estado);
				sscanf(linha_quebrada[8], "%d", &c.codigo_conta);
				v_contas[total_contas] = c;
				total_contas++;
			}

		}

		fclose(Base_dados);
}

//ESCOPO LOCAL
int main() {
	pessoa p;
	int codigo;
	int numero_conta, numero_conta_enviar,numero_conta_receber, numero_conta1, indice;
	float valor1, valor;
	bool verificar;
	setlocale(LC_ALL,"Portuguese");
	criarficheiro();
	carregar_ficheiro();
	printf("\n _____________Bem-Vindo______________ \n ");
	int opcao;

		do{
		printf("\n 1- Cadastrar Clientes \n");
		printf(" 2- Listar Clientes \n");
		printf(" 3- Abertura de conta \n");
		printf(" 4- Depositar dinheiro \n");
		printf(" 5- Levantar dinheiro \n");
		printf(" 6- Consultar saldo  \n");
		printf(" 7- Transferir Dinheiro  \n");
		printf(" 8- Actualizar Dados do cliente  \n");
		printf(" 9- Terminar  \n");
		printf( " Opcao:" );
		scanf("%d", &opcao);
		switch(opcao) {
			case 1:

				printf("Digite o seu nome: ");
				scanf("%s", p.nome );
				printf("Bilhete de identidade/Nif: ");
				scanf("%s", p.bi_nif);
				printf("Digite a sua morada: ");
				scanf("%s", p.morada);
				printf("Digite o seu o numero de telefone: ");
				scanf("%d", &p.telefone);
			verificar=	cadastrar_cliente(p);

				break;
			case 2:
				listar_clientes();
				break;


			case 3:
				printf("Digite o seu codigo pessoal : ");
				scanf("%d", &codigo);

				 indice = pesquisar_registo(codigo);

				if (indice != -1){

					int tipo_de_conta;
					printf ("Insira o tipo de conta \n0-para particular \n1-para empresarial:");
					scanf("%d", &tipo_de_conta);
						fflush(stdin);
				verificar=	abertura_conta(v_clientes[indice], tipo_de_conta);

				}
				break;
			case 4:
			
			printf ("Digite o numero da conta: ");
			scanf ("%d",&numero_conta1);
             indice = pesquisar_pelo_numero_conta(numero_conta1);
            if(indice==-1){
                printf("Impossivel\n");
            }
            else{
                printf("Pessoa encontrada\n");
                printf("Digite valor\n");
                scanf("%f",&valor1);
                bool verificar_deposito=depositar_dinheiro(numero_conta1,valor1);
                if(verificar_deposito==false){
                    printf("Nao depositado\n");
                }else{
                    printf("Deposito realizado\n");
                }
            }
			
				break;
			case 5:

printf ("Digite o numero da conta: ");
			scanf ("%d",&numero_conta1);
             indice =pesquisar_pelo_numero_conta(numero_conta1);
            if(indice==-1){
                printf("Impossivel\n");
            }
            else{
                printf("Pessoa encontrada\n");
                printf("Digite valor a levantar\n");
                scanf("%f",&valor1);
                bool verificar_levantamento=levantar_dinheiro(numero_conta1,valor1);
                if(verificar_levantamento==false){
                    printf("Erro!\n");
                }else{
                    printf("Levantamento realizado\n");
                }

            }
			 break;

		 case 6:

		printf("Digite o numero da conta");
		scanf("%d",&numero_conta);
		consultar_saldo(numero_conta);

				break;
			case 7:

			  printf("Digite a conta enviar");
			  scanf("%d",&numero_conta_enviar);
			  printf("Conta recber");
			  scanf("%d",&numero_conta_receber);
			  printf("Valor");
			  scanf("%f",&valor);
			verificar =  transferir_dinheiro (numero_conta_enviar,numero_conta_receber, valor);
				break;
			case 8:


			printf ("Insira o seu codigo pessoal: ");
			scanf ("%d",&codigo);

			 indice = pesquisar_registo(codigo);

			pessoa p;

			printf ("Digite o seu nome: ");
			scanf ("%s",p.nome);
			printf ("Digite o seu bilhete: ");
			scanf ("%s", p.bi_nif);
			printf ("Digite a sua morada: ");
			scanf ("%s", p.morada);
			printf ("Digite o seu telefone: ");
			scanf ("%d", &p.telefone);

			verificar= atualizar_dados(p, codigo);
				break;


			case 9:
				break;
		}
		
		if (verificar == true){

escrever_ficheiro();
		}
		


	}while ( opcao != 9 );
	return 0;
}

//_____________FUNCOES OPERANDO____________
bool cadastrar_cliente(pessoa p){
 	p.codigo = total_clientes + 1;
 	v_clientes[total_clientes] = p;
 	total_clientes++;
 	return true;

 }

//__________funcoes de pesquisa_________
//pesquisar conta...
int pesquisar_conta (int codigo){
	int i;
	for (i=0; i< total_contas; i++) {
			conta c = v_contas[i];
		if(c.codigo_conta == codigo) {
			return i;
		}
	}
	return -1;
}
//________________________________________

 //LISTAR CLIENTES
void listar_clientes (){
	
		int i;
		pessoa p;
	for(i =0; i < total_clientes; i++) {
		p= v_clientes[i];
		printf("________DADOS PESSOAIS_________________ \n"); 
		printf("Codigo: %d \n", p.codigo);
		printf("Nome: %s \n", p.nome); 
		printf("Telefone: %d \n", p.telefone); 
		printf("Identificao: %s \n", p.bi_nif); 
		printf("Morada: %s \n\n", p.morada); 

		int pesquisar = pesquisar_conta(p.codigo);

	if(pesquisar != -1 ) {
		conta c = v_contas[pesquisar];
		printf("____________Dados da Conta:______________ \n"); 
		printf("Numero de conta: %d \n", c.numero_conta); 
		printf("Saldo: %f\n", c.saldo); 
		printf("Estado: %d \n", c.estado); 
		printf("Codigo cliente; %d \n", c.codigo_conta); 	
		printf("_________________________________________ \n");
		}
	}	
}

   // pesquisar cliente...
int pesquisar_registo (int codigo){
	int i;
	for (i=0; i< total_clientes; i++) {
			pessoa p = v_clientes[i];
		if(p.codigo == codigo) {
			return i;
		}
	}
	return -1;
}

bool abertura_conta (pessoa p, int tipo_conta){
	conta c;
	c.codigo_conta = p.codigo;
	c.numero_conta = total_contas + 1;
	c.saldo = 0;
	c.estado = 0;
	v_contas[total_contas] = c;
	total_contas ++;
	
	return true;
}

	 int pesquisar_pelo_numero_conta (int numero_conta){
	int i;
	for (i =0; i < total_contas;i++) {
		conta c= v_contas[i];
		if (c.numero_conta == numero_conta) {
			return i;
		}
	}
	return -1;
    }

	bool depositar_dinheiro (int numero_conta, float valor){
	int indice = pesquisar_pelo_numero_conta (numero_conta);
    if(indice == -1){

        return false;
    }
    v_contas[indice].saldo +=valor;
	v_contas[indice].estado=1;
    return true;

	}

bool levantar_dinheiro (int numero_conta, float valor) {
	int indice =pesquisar_pelo_numero_conta (numero_conta);

	if (indice == -1) {
		return false;
	}
	if (v_contas[indice].saldo < valor) {
		return false;
	}
	v_contas[indice].saldo =v_contas[indice].saldo - valor;
	return true;
}
float consultar_saldo (int numero_conta) {
	int indice =pesquisar_pelo_numero_conta (numero_conta);
	if (indice == -1) {
		return -1;
	}
	printf ("O seu saldo e de: %2.f\n",v_contas[indice].saldo);

	return 1;
}

bool transferir_dinheiro (int numero_conta_enviar, int numero_conta_receber, float valor){
	int conta_enviar = pesquisar_pelo_numero_conta (numero_conta_enviar);

	 if (conta_enviar == -1) {
	 	return false;
	 }

	int conta_receber = pesquisar_pelo_numero_conta (numero_conta_receber);

	 if (conta_receber == -1) {
	 	return false;
	 }else{
	 	printf("conta encontrada\n");
	}


	if (v_contas[conta_enviar].saldo < valor) {
		return false;
	}
	v_contas[conta_enviar].saldo  -= valor;
	v_contas[conta_receber].saldo += valor;

	return true;
}

 bool atualizar_dados (pessoa p, int codigo_cliente){
	int indice = pesquisar_registo(codigo_cliente);

	if (indice == -1){
		return false;
	}

	p.codigo = codigo_cliente;
	v_clientes[indice] = p;

	return true;
 }

