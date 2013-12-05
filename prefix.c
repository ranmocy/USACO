/*
  PROG: prefix
  LANG: C
  ID: ranmocy1
*/

#include <stdio.h>
#include <string.h>
typedef enum { false, true } bool;
#define max_primitives 200
/* final char must be '\0' */
#define max_length 11
#define max_sequence 200000

int prim_counter = 0;
char prim[max_primitives][max_length];
int l[max_primitives];
char seq[max_sequence];
bool f[max_sequence];


/*
  Dynamic Programming problem:
  Table: f[i] indicates whether the prefix with i chars can be presented by the prims.
  Function: f[i] = OR(f[i-prim[j].length]) if seq[i-prim[j].length..i] == prim[j]
*/
int main()
{
    FILE *fin = fopen("prefix.in", "r");
    FILE *fout = fopen("prefix.out", "w");

    /* read primitives */
    char t = fgetc(fin);
    while (t != '.'){
        if ((t == ' ') || (t == '\n')){
            l[prim_counter] = strlen(prim[prim_counter]);
            prim_counter++;
        } else {
            prim[prim_counter][strlen(prim[prim_counter])] = t;
        }
        t = fgetc(fin);
    }

    fgetc(fin);  /* the newline char */

    /* read sequence */
    t = fgetc(fin);
    long pos = 0;
    while (t != EOF){
        if (t != '\n'){
            seq[pos] = t;
            pos++;
        }
        t = fgetc(fin);
    }

    /* dp */
    long i,j,k,len;
    bool flag;
    len = strlen(seq);
    for (i=0; i<len; i++){ f[i] = false; }

    for (i=0; i<len; i++){
        for (j=0; j<prim_counter; j++){
            if ((i+1 == l[j]) || ((i+1 > l[j]) && (f[i-l[j]]))) {
                flag = true;
                long offset = strlen(prim[j]);
                for (k=0; k<offset; k++){
                    if (seq[i-offset+k+1] != prim[j][k]){
                        flag = false;
                        break;
                    }
                }
                if (flag){
                    f[i] = true;
                    break;
                }
            }
        }
    }

    /* find the longest one */
    long ans = len;
    while ((ans > 0) && (!f[ans-1])) { ans--; }
    fprintf(fout, "%ld\n", ans);

    fclose(fin);
    fclose(fout);
    return 0;
}
