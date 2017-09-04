#include <stdio.h>
#include <locale.h>

FILE *arq;

struct FDA
{
	char letEnt[20];
	int sttOrig[20];
	int cont;
}stat[20];

void arquivo(char str1[100]);
void arqTr(char str2[100],int limite);
int contArq(void);
int NumSimb(char a[100],char b[100]);
int NumStt(char a[100],char c[100]);
int transicao(struct FDA estado[4],char simbol);
void printStt(int sttIni,char simb, int sttFin);

int i=0,j=0,numStat,numSimb,sttAtual=0;
char strDig[10];

int main()
{
	setlocale(LC_ALL,"portuguese");
	char str[100];
				
	arquivo(str);
	
	char strAux[100];
	
	numSimb = NumSimb(str,strAux);
		
	printf("Número de simbolos: %i\n",numSimb);	
	printf("%s\n",strAux);
	
	printf("\n");

	numStat = NumStt(str,strAux);
	
	printf("Número de estados: %i\n",numStat);	
	printf("%s\n",strAux);
	
	printf("\n");
	
	char letra,teste;
	
	int w, NumLin = contArq();
	i=1;
	
	for(w = 0;w<=20;w++)
		stat[w].cont = 0;
		
	printf("Função de transição:\n");
	while(i < NumLin)
	{
		arqTr(str,i);
	
		if(str[8] == 'f')
		{
			stat[numStat-1].letEnt[stat[numStat-1].cont] = (char)str[4];
			stat[numStat-1].sttOrig[stat[numStat-1].cont] = (int)str[1]-48;
			stat[numStat-1].cont++;
		}else
		{
			stat[(str[8]-48)].letEnt[stat[(str[8]-48)].cont] = (char)str[4];
			stat[(str[8]-48)].sttOrig[stat[(str[8]-48)].cont] = (int)str[1]-48; 
			stat[(str[8]-48)].cont++;
		}
		i++;
	}
	
	printf("\n");
	
    i=0;
	j=0;
	
	printf("Digite a palavra: ");
	scanf("%s",strDig);
	
	do
	{
		letra = strDig[j];
		i = transicao(stat,letra);
		j++;
	}while(strDig[j] != '\0' && i != -1);
	
	if(strDig[j] == '\0' && i != -1)
		printf("Palavra recusada!");
	
	return 0;
}

void arquivo(char str1[100])
{
	arq = fopen("automato.txt","r");
	
  	if(arq == NULL)
		printf("Não é possível ler o arquivo!\n");
	else 
	{
		fscanf(arq,"%[^\n]",str1);
		printf("%s",str1);
	}
		
	fclose(arq);
	
	printf("\n");	
}

void arqTr(char str2[100],int limite)
{
	int line = 0;
	char holder;
	
	arq = fopen("automato.txt","r");
	
	while((holder = fgetc(arq)) != EOF) 
	{
		if(holder == '\n') 
	 		line++;
     	if(line == limite) 
		 	break; 
    }
    
    if(arq == NULL) 
	{
	   	printf("Não é possível ler o arquivo!\n"); 
   	}else
	   	{    
   			fscanf(arq,"%[^\n]",str2);
   			printf("%s",str2);
   		}
  		
   	fclose(arq);
   	
   	printf("\n");
}

int contArq(void)
{
	char holder;
	int cont=1;
	
	arq = fopen("automato.txt","r");
	
	while((holder = fgetc(arq)) != EOF)
		if(holder == '\n')
			cont++;
	
	fclose(arq);
	
	return cont;
}

int NumSimb(char a[100],char b[100])
{
	int i=2,j=0;
	
		do
	{
		if(a[i] >= 'a' && a[i] <= 'z')
		{
			b[j] = a[i];
			j++;
		}
		i++;
	}while(a[i] != '\0' && a[i] != 'q');
	
	b[j] = '\0';
	
	return j;
}

int NumStt(char a[100],char c[100])
{
	int i=2,j=0;
	
		do
	{
		if(a[i] >= '0' && a[i] <= '9' || a[i] == 'f')
		{
			c[j] = a[i];
			j++;
		}
		i++;
	}while(a[i] != '\0' && a[i] != '&');
	
	c[j] = '\0';
	
	return j;
}

int transicao(struct FDA estado[4],char simbol)
{
	int k,i=0;
	
	do
	{	
		for(k = 0;k <= stat[i].cont;k++)
		{
			if(estado[i].letEnt[k] == simbol && estado[i].sttOrig[k] == sttAtual)
			{
				printStt(sttAtual,simbol,i);
				if(i == numStat-1)
				{
					if(strDig[j+1] != '\0')
					{
						printf("Palavra recusada!");
						return -1;
					}
					printf("Palavra aceita!");
					return -1;
				}
				sttAtual = i;
				return 0;
			}
		}
		i++;
	}while(i <= numStat-1);
	
	printf("Palavra recusada!");
	
	return -1;
}

void printStt(int sttIni,char simb, int sttFin)
{
	printf("q%i -> ",sttIni);
	printf("%c",simb);
	if(sttFin == numStat-1)
		printf(" -> qf \n");
	else
		printf(" -> q%i \n",sttFin);
}

