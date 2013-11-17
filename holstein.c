/*
  PROG: holstein
  LANG: C
  ID: ranmocy1
*/

typedef enum { false, true } bool;
#define DEBUG 1
#define MAX_V 25
#define MAX_G 15

#include <stdio.h>
#include <math.h>

int v, g;
int V[MAX_V];
int G[MAX_G][MAX_V];
bool res[MAX_G];
int total_res = INFINITY;


bool check(const bool current[MAX_G])
{
  int tmp[v];
  int i,j;
  for (j=0; j<v; j++){ tmp[j] = 0; }

  for (i=0; i<g; i++){
    if (current[i] == true){
      for (j=0; j<v; j++){
        tmp[j] += G[i][j];
      }
    }
  }

  bool flag = true;
  for (j=0; j<v; j++){
    if (tmp[j] < V[j]){
      flag = false;
      break;
    }
  }

  return flag;
}


void update(bool current[MAX_G])
{
  int total_tmp = 0;
  int i;
  for (i=0; i<g; i++){
    if (current[i] == true){
      total_tmp++;
    }
  }

  if (total_tmp < total_res){
    for (i=0; i<g; i++){
      res[i] = current[i];
    }
    total_res = total_tmp;
  }

  return;
}

void search(bool current[MAX_G], int i)
{
  if (i > g){
    if (check(current) == true){ update(current); }
    return;
  }
  current[i] = true;
  search(current, i+1);
  current[i] = false;
  search(current, i+1);
}


/*
  v is less than 25, g is less than 15.
  The combination of 15 is 2^15=32768.
  Times the time of checker 32768*25*15=12,288,000.
  Which is satisfied.
  So just enumerate all the combinations and check it.
  Search the one with small number first.
  If the result use less numbers of scoops, update.
 */
int main()
{
  FILE *fin = fopen("holstein.in", "r");
  FILE *fout = fopen("holstein.out", "w");
  int i,j;

  fscanf(fin, "%d", &v);
  for (i=0; i<v; i++){
    fscanf(fin, "%d", &V[i]);
  }

  fscanf(fin, "%d", &g);
  for (i=0; i<g; i++){
    for (j=0; j<v; j++){
      fscanf(fin, "%d", &G[i][j]);
    }
  }

  // search
  bool current[g];
  for (i=0; i<g; i++){ res[i] = false; current[i] = false; }
  search(current, 0);

  //output
  fprintf(fout, "%d", total_res);
  for (i=0; i<g; i++){
    if (res[i]){
      fprintf(fout, " %d", i+1);
    }
  }
  fprintf(fout, "\n");
  return 0;
}
