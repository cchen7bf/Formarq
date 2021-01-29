#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int i;
char pgm_entrada[100];
char variavel, extensao[4], chave[100];
char nome[20];

//---------------------------FUNÇÃO INVERTER-----------------------------------
void inverter() { 
    int dado1, dado2;
    FILE *cadent, *cadsai;
    
    cadent=fopen(pgm_entrada, "rb");
   
    if (strcmp(extensao, "txt")==0)      //caso a ext for .txt vira . inv, se .inv vira .dnv
        strcat(nome, "inv");
     else 
        strcat(nome,"dnv");
    
    cadsai=fopen(nome, "wb");

    dado1=fgetc(cadent);
    while(!feof(cadent)) {
        dado2 = ~dado1;
        fputc(dado2, cadsai);
        dado1=fgetc(cadent);
    }
    fclose(cadent);
    fclose(cadsai);
}

//---------------------------FUNÇÃO CRIPTOGRAFAR-------------------------------
void criptografar() {

    int dado1, dado2, tamanho, incremento=0;
    FILE *cadent, *cadsai;


    cadent=fopen(pgm_entrada, "rb");
    if (strcmp(extensao, "dat")==0)      //caso a ext for .dat vira . crp, se .crp vira .drp
        strcat(nome, "crp");
     else 
        strcat(nome,"drp");
    
    cadsai=fopen(nome, "wb");
    tamanho = strlen(chave);
    dado1 = fgetc(cadent);
    while (!feof(cadent)) {
        dado2 = dado1^chave[incremento];
        fputc(dado2, cadsai);
        dado1 = fgetc(cadent);
        incremento++;
        if (incremento==tamanho)
            incremento=0;
    }
    fclose(cadent);
    fclose(cadsai);
}

//---------------------------FUNÇÃO DOS----------------------------------------
void unixtodos(void) {
    int dado1;
    FILE *cadent, *cadsai;
    strcat(nome, "dos");
    cadent = fopen(pgm_entrada, "rb");
    cadsai = fopen(nome, "wb");
    dado1=fgetc(cadent);
    while (!feof(cadent)) {
        if (dado1==10) {
            fputc(13, cadsai);
    	}
		fputc(dado1, cadsai);
		dado1=fgetc(cadent);
	}
    fclose(cadent);
    fclose(cadsai);
}

//---------------------------FUNÇÃO UNIX---------------------------------------
void dostounix(void) {
    int dado1;
    FILE *cadent, *cadsai;
    strcat(nome, "unx");
    cadent = fopen(pgm_entrada, "rb");
    cadsai = fopen(nome, "wb");
    dado1=fgetc(cadent);
    while (!feof(cadent)) {
        if (dado1 !=13) {
            fputc(dado1, cadsai);
        }
    	dado1=fgetc(cadent);
	}
    fclose(cadent);
    fclose(cadsai);
}


//---------------------------FUNÇÃO PRINCIPAL----------------------------------
int main(int argc, char *argv[]) {
    FILE *entrada;
    strcpy(pgm_entrada,argv[1]);
    entrada=fopen(pgm_entrada,"r");

    strcpy(nome, pgm_entrada); //copia o nome do arquivo de entrada sem a extensão.
    nome[strlen(nome)-3]='\0';

    for (i=strlen(pgm_entrada)-1; i && pgm_entrada[i]!= '.'; i--) { //copia a extensão do arquivo.
        strcpy(extensao, pgm_entrada+i); 
    }
    
    if (entrada==NULL) {
        printf("Arquivo de entrada não existe\n");
        system("pause");
        return(1);
    } else if (argv[2][0]== 'i' || argv[2][0]=='I') {
        inverter(); 
    } else if (argv[2][0]== 'c' || argv[2][0]=='C') {
        if (argv[3]==NULL) {
            printf("Falta digitar o valor da chave\n");
            system("pause");
            return(1);
        } else {                    
            strcpy(chave, argv[3]);            
            criptografar();
    } 
    } else if (argv[2][0]== 'd' || argv[2][0]=='D') {
        unixtodos(); 
    } else if (argv[2][0]== 'u' || argv[2][0]=='U') {
        dostounix(); 
    } else {
        printf("Comando não reconhecido\n");
    }
	return 0;
}
