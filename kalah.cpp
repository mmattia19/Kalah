#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void clearConsole()
{
#if defined(_WIN32) || defined(_WIN64)
  system("cls");
#else
  system("clear");
#endif
}

struct s_giocatore
{
  char nome[100];
};
typedef struct s_giocatore giocatore;

struct s_mosse
{
  int giocatore;
  int casa;
};
typedef struct s_mosse mosse;

void rotazione(int c[])
{
  for (int i=0; i<7; i++)
  {
    int t=c[i];
    c[i]=c[i+7];
    c[i+7]=t;
  }
}

int main(void)
{
  int c[14], e=0, m, v, indice=0;
  mosse mosse[1000];
  giocatore g[2];
  srand(time(NULL));
  clearConsole();
  printf("KALAH\n\nInserire il nome del giocatore 1:\n> ");
  scanf("%s", g[0].nome);
  getchar();
  clearConsole();
  printf("KALAH\n\nInserire il nome del giocatore 2:\n> ");
  scanf("%s", g[1].nome);
  getchar();
  while (strcmp(g[0].nome, g[1].nome)==0)
  {
    printf("NOME NON VALIDO\n\nInserire il nome del giocatore 2:\n> ");
    scanf("%s", g[1].nome);
    getchar();
  }
  clearConsole();
  c[6]=0, c[13]=0;
  for (int i=0; i<6; i++)
  {
    c[i]=3;
    c[5-i]=6-c[i];
  }
  for (int i=7; i<13; i++)
  {
    c[i]=rand()%3+2;
    c[19-i]=6-c[i];
  }
  do
  {
    clearConsole();
    printf("Mossa di %s\n\n%s:\n    %d  %d  %d  %d  %d  %d\n\n%d                       %d\n\n%s:\n    %d  %d  %d  %d  %d  %d\n\nInserire l'indice della casa (da 1 a 6):\n> ", g[e].nome, g[1-e].nome, c[12], c[11], c[10], c[9], c[8], c[7], c[13], c[6], g[e].nome, c[0], c[1], c[2], c[3], c[4], c[5]);
    scanf("%d", &m);
    m--;
    while (c[m]==0 || m<0 || m>5)
    {
      printf("CASA NON VALIDA\n\nInserire l'indice della casa (da 1 a 6):\n> ");
      scanf("%d", &m);
      m--;
    }
    mosse[indice].giocatore=e+1;
    mosse[indice].casa=m+1;
    int i=1;
    do
    {
      c[(m+i)%14]++;
      c[m]--;
      i++;
    }
    while (c[m]!=0);
    m=(m+i-1)%14;
    if (m!=6)
    {
      if(m<6 && c[m]==1)
      {
        c[6]=c[6]+c[m]+c[12-m];
        c[m]=0, c[12-m]=0;
      }
      e=1-e;
      rotazione(c);
    }
    indice++;
  }
  while (c[0]+c[1]+c[2]+c[3]+c[4]+c[5]!=0 && c[7]+c[8]+c[9]+c[10]+c[11]+c[12]!=0);
  FILE *fp;
  fp=fopen("Mosse.txt", "w");
  for(int i=0; i<indice; i++)
  {
    fprintf(fp, "%d |", mosse[i].giocatore);
    fprintf(fp, "%d \n", mosse[i].casa);
  }
  fclose(fp);
  c[6]=c[6]+c[0]+c[1]+c[2]+c[3]+c[4]+c[5];
  c[13]=c[13]+c[7]+c[8]+c[9]+c[10]+c[11]+c[12];
  c[0]=0, c[1]=0, c[2]=0, c[3]=0, c[4]=0, c[5]=0;
  c[7]=0, c[8]=0, c[9]=0, c[10]=0, c[11]=0, c[12]=0;
  clearConsole();
  if (c[6]==c[13])
  {
    printf("Pareggio!\n\n%s:\n    %d  %d  %d  %d  %d  %d\n\n%d                       %d\n\n%s:\n    %d  %d  %d  %d  %d  %d\n", g[1-e].nome, c[12], c[11], c[10], c[9], c[8], c[7], c[13], c[6], g[e].nome, c[0], c[1], c[2], c[3], c[4], c[5]);
  }
  else
  {
    if (c[6]>c[13])
    {
      v=e;
    }
    else
    {
      v=1-e;
    }
    printf("Ha vinto %s!\n\n%s:\n    %d  %d  %d  %d  %d  %d\n\n%d                       %d\n\n%s:\n    %d  %d  %d  %d  %d  %d\n", g[v].nome, g[1-e].nome, c[12], c[11], c[10], c[9], c[8], c[7], c[13], c[6], g[e].nome, c[0], c[1], c[2], c[3], c[4], c[5]);
  }
}
