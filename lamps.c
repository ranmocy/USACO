/*
  PROG: lamps
  LANG: C
  ID: ranmocy1
*/

#include <stdio.h>
#include <stdlib.h>
typedef enum { false, true, any } bool;
#define MAX_BUTTONS 4
#define MAX_STATES 6
#define MAX_ANS 16

int n,c;
bool button[MAX_BUTTONS];  /* true for odd, false for even */
bool states[MAX_STATES]; /* true for on, false for off, any for any */

bool lamps[MAX_STATES];  /* true for on, false for off */
int total_ans=0;
bool ans[MAX_ANS][MAX_STATES];  /* same with the states */


int classify(const int i)
{
    return i % MAX_STATES;
}

bool check_buttons()
{
    int i,odd = 0;
    for (i=0; i<MAX_BUTTONS; i++){
        if (button[i]) { odd++; }
    }
    if (odd > c) { return false; }
    if ((c - odd) % 2 == 0){
        return true;
    } else {
        return false;
    }
}



bool check_lamps()
{
    int i;
    for (i=0; i<MAX_STATES; i++){ lamps[i] = true; }

    /* generate the states */
    for (i=0; i<MAX_STATES; i++){
        if (button[0]){ lamps[i] ^= true; }
        if (button[1] && (i % 2 == 1)){ lamps[i] ^= true; }
        if (button[2] && (i % 2 == 0)){ lamps[i] ^= true; }
        if (button[3] && (i % 3 == 1)){ lamps[i] ^= true; }
    }

    /* check conflicts between lamps and states */
    for (i=0; i<MAX_STATES; i++){
        if ((states[i] != any) && (states[i] != lamps[i])){
            return false;
        }
    }

    return true;
}


bool check_dup_ans()
{
    int i,j;
    for (i=0; i<total_ans; i++){
        int flag = true;  /* flag for dup exists */
        for (j=0; j<MAX_STATES; j++){
            if (ans[i][j] != lamps[j]){
                flag = false;
                break;
            }
        }
        if (flag) { return false; }
    }
    return true;
}


void search(int i)
{
    if (i >= MAX_BUTTONS){
        if (check_buttons() && check_lamps() && check_dup_ans()){
            /* add to ans */
            int j;
            for (j=0; j<MAX_STATES; j++){
                ans[total_ans][j] = lamps[j];
            }
            total_ans++;
        }
    } else {
        button[i] = true;
        search(i+1);
        button[i] = false;
        search(i+1);
    }
}


int cmp_states(const void *a, const void *b)
{
    int i;
    for (i=1; i<MAX_STATES; i++){
        if (((int *)a)[i] == ((int *)b)[i]){
            continue;
        } else {
            return ((int *)a)[i] - ((int *)b)[i];
        }
    }
    return ((int *)a)[0] - ((int *)b)[0];
}



/*
  Since all the buttons are toggle the state,
  the effects of the buttons are only depend on
  the number of the button presses is odd or even.
  So four buttons, there are only 2^4=16 situations.
  button1: true
  button2: i % 2 == 1
  button3: i % 2 == 0
  button4: i % 3 == 1
  So case n % 6:
  0: 1+3
  1: 1+2+4
  2: 1+3
  3: 1+2
  4: 1+3+4
  5: 1+2
*/
int main()
{
    FILE *fin = fopen("lamps.in", "r");
    FILE *fout = fopen("lamps.out", "w");
    int i,t;
    for (i=0; i<MAX_STATES; i++){states[i] = any;}

    fscanf(fin, "%d\n%d\n", &n, &c);
    fscanf(fin, "%d", &t);
    while(t != -1){
        states[classify(t)] = true;
        fscanf(fin, "%d", &t);
    }
    fscanf(fin, "%d", &t);
    while(t != -1){
        states[classify(t)] = false;
        fscanf(fin, "%d", &t);
    }

    search(0);

    /* Sort */
    qsort(ans, total_ans, sizeof(int)*MAX_STATES, cmp_states);
    /* todo */

    //OUT:
    if (total_ans == 0){
        fprintf(fout, "IMPOSSIBLE\n");
    }
    int j;
    for (i=0; i<total_ans; i++){
        for (j=1; j<=n; j++){
            fprintf(fout, "%d", ans[i][classify(j)]);
        }
        fprintf(fout, "\n");
    }
    fclose(fin);
    fclose(fout);
    return 0;
}
