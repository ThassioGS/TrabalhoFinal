#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

/*Boa noite professor, minha equipe e Thassio G. Sabel, William Krauss e Gustavo Dias
Pra conseguir arrumar o erro de ele escrever e ler informacoes duplicadas, eu simplesmente pulei
a linha antes de gravar as informacoes no arquivo, isso nas linhas 34, 62, 69 e 76.*/

void cadastro(){
	
	FILE *notas;
	
	notas = fopen("notas-processar.txt", "a");
	
	if (notas == NULL){
		printf("Problemas na criação do arquivo\n");
	}else{
		
		char nome[100];
		float nota1, nota2, nota3;
		
		printf("Informe o nome do aluno: ");
		scanf("%s", &nome);
		
		printf("Informe a nota 1: ");
		scanf("%f", &nota1);
		
		printf("Informe a nota 2: ");
		scanf("%f", &nota2);
		
		printf("Informe a nota 3: ");
		scanf("%f", &nota3);
		
		fprintf(notas, "\n%s %.2f %.2f %.2f", nome, nota1, nota2, nota3);
	}
	fclose(notas);
}

void processo(){
	
	FILE *notas;
	
	notas = fopen("notas-processar.txt", "r");
	
	if (notas == NULL){
		printf("Não existem notas para processar.\n");
	}
	else{
		char nome[100];
		float nota1, nota2, nota3, media;
		
		while(1){
			if(feof(notas)){
				break;
			}
			fscanf(notas, "%s %f %f %f", &nome, &nota1, &nota2, &nota3);
			media = (nota1 * 0.25) + (nota2 * 0.35) + (nota3 * 0.4);
			if (media >= 6){
				
				FILE *aprovado;
				aprovado = fopen("alunos-aprovados.txt", "a");
				fprintf(aprovado, "\n%s %.2f %.2f %.2f %.2f", nome, nota1, nota2, nota3, media);
				fclose(aprovado);
				
			}else if (media >= 3 && media < 6){
				
				FILE *exame;
				exame = fopen("alunos-em-exame.txt", "a");
				fprintf(exame, "\n%s %.2f %.2f %.2f %.2f", nome, nota1, nota2, nota3, media);
				fclose(exame);
				
			}else if (media < 3){
				
				FILE *reprovado;
				reprovado = fopen("alunos-reprovados.txt", "a");
				fprintf(reprovado, "\n%s %.2f %.2f %.2f %.2f", nome, nota1, nota2, nota3, media);
				fclose(reprovado);
			}
		}
		printf("Processado com sucesso.\n");
	}
	
	fclose(notas);
	remove("notas-processar.txt");
}

void aprovados(){
	
	char nome[100];
	float nota1, nota2, nota3, media;
	FILE *aprovados;
	
	aprovados = fopen("alunos-aprovados.txt", "r");
	
	if (aprovados == NULL){
		printf("Nenehum aluno aprovado localizado.\n");
	}
	
	while(1){
	if(feof(aprovados)){
		break;
	}
	fscanf(aprovados, "%s %f %f %f %f", &nome, &nota1, &nota2, &nota3, &media);
	printf("%s %.2f %.2f %.2f %.2f\n", nome, nota1, nota2, nota3, media);
	}
	
	fclose(aprovados);
}

void exame(){
	
	char nome[100];
	float nota1, nota2, nota3, media;
	FILE *exame;
	
	exame = fopen("alunos-em-exame.txt", "r");
	
	if (exame == NULL){
		printf("Nenehum aluno em exame localizado.\n");
	}
	
	while(1){
	if(feof(exame)){
		break;
	}
	fscanf(exame, "%s %f %f %f %f", &nome, &nota1, &nota2, &nota3, &media);
	printf("%s %.2f %.2f %.2f %.2f\n", nome, nota1, nota2, nota3, media);
	}
	
	fclose(exame);
}

void reprovados(){
	
	char nome[100];
	float nota1, nota2, nota3, media;
	FILE *reprovados;
	
	reprovados = fopen("alunos-reprovados.txt", "r");
	
	if (reprovados == NULL){
		printf("Nenehum aluno reprovado localizado.\n");
	}
	
	while(1){
	if(feof(reprovados)){
		break;
	}
	fscanf(reprovados, "%s %f %f %f %f", &nome, &nota1, &nota2, &nota3, &media);
	printf("%s %.2f %.2f %.2f %.2f\n", nome, nota1, nota2, nota3, media);
	}
	
	fclose(reprovados);
}

void menu(){
	printf("\nSelecione uma opção:\n");
	printf("1. Cadastrar notas\n");
	printf("2. Processar medias\n");
	printf("3. Lista de alunos aprovados\n");
	printf("4. Lista de alunos em exame\n");
	printf("5. Lista de alunos reprovados\n");
	printf("0. Sair\n");
}

int main(){
	setlocale(LC_ALL, "Portuguese");
	
	int op = -1;
	menu();
	
	while (true){
		scanf("%d", &op);
		
		switch(op){
			case 1:{
				
				printf("\nCadastro:\n");
				cadastro();
				printf("\n-------------------------------------------\n");
				break;
				
			}
			case 2:{
				
				printf("\nProcessar medias:\n");
				processo();
				printf("\n-------------------------------------------\n");
				break;
				
			}
			case 3:{
				
				printf("\nAlunos aprovados:\n");
				aprovados();
				printf("\n-------------------------------------------\n");
				break;
				
			}
			case 4:{
				
				printf("\nAlunos em exame:\n");
				exame();
				printf("\n-------------------------------------------\n");
				break;
				
			}
			case 5:{
				
				printf("\nAlunos reprovados:\n");
				reprovados();
				printf("-------------------------------------------\n");
				break;
				
			}
			case 0:{
				
				printf("\nSair.\n");
				return false;
				
			}
			default:{
				
				printf("-------------------------------------------\nOpção inválida, tente novamente.\n\n");
				break;
				
			}
		}
		menu();
	}
}
