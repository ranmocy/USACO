/*
  PROG: sort3
  LANG: C
  ID: ranmocy1
*/
#include <stdio.h>

int n, i, j;
FILE *fin;
FILE *fout;

int main(){
  fin = fopen("sort3.in", "r");
  fout = fopen("sort3.out", "w");
  fscanf(fin, "%d", &n);

  int num[1000];
  int num1 = 0;
  int num2 = 0;
  int num3 = 0;

  // read and count the numbers
  for(i=1; i<=n; i++){
    fscanf(fin, "%d", &num[i]);
    switch (num[i]) {
    case 1:
      num1++;
      break;
    case 2:
      num2++;
      break;
    case 3:
      num3++;
      break;
    default:
      printf("Error Range!\n");
      return 1;
    }
  }

  // unwilling pairs
  int d[4][4];
  for(i=1; i<=3; i++){
    for(j=1; j<=3; j++){
      d[i][j] = 0;
    }
  }
  for(i=1; i<=num1; i++){d[num[i]][1]++;}
  for(i=num1+1; i<=num1+num2; i++){d[num[i]][2]++;}
  for(i=num1+num2+1; i<=n; i++){d[num[i]][3]++;}

  // the reverse pairs
  int moves = 0;
  if(d[1][2] < d[2][1]){
    moves += d[1][2];
    d[2][1] -= d[1][2];
    d[1][2] = 0;
  }else{
    moves += d[2][1];
    d[1][2] -= d[2][1];
    d[2][1] = 0;
  }

  if(d[1][3] < d[3][1]){
    moves += d[1][3];
    d[3][1] -= d[1][3];
    d[1][3] = 0;
  }else{
    moves += d[3][1];
    d[1][3] -= d[3][1];
    d[3][1] = 0;
  }

  if(d[2][3] < d[3][2]){
    moves += d[2][3];
    d[3][2] -= d[2][3];
    d[2][3] = 0;
  }else{
    moves += d[3][2];
    d[2][3] -= d[3][2];
    d[3][2] = 0;
  }

  moves += d[1][2]*2;
  moves += d[2][1]*2;

  // output
  fprintf(fout, "%d\n", moves);

  fclose(fin);
  fclose(fout);
  return 0;
}
