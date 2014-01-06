/*
  PROG: spin
  LANG: C
  ID: ranmocy1
*/

#include <stdio.h>
#define ROUND 360
#define N 5
typedef enum { false, true } bool;
typedef struct wedge {
    int start, end;
} wedge;
typedef struct wheel {
    int speed, size;  /* number of wedges */
    wedge wedges[5];
} wheel;

wheel wheels[5];


bool aligned(int i, int j, int position)
{
    if (wheels[i].wedges[j].start <= wheels[i].wedges[j].end){
        return (wheels[i].wedges[j].start <= position) && (position <= wheels[i].wedges[j].end);
    } else {
        return (wheels[i].wedges[j].start <= position) || (position <= wheels[i].wedges[j].end);
    }
}

void add(int *a, int b)
{
    *a = (*a + b + ROUND) % ROUND;
    return;
}

/*
  Brute Force
 */
int main()
{
    FILE *fin = fopen("spin.in", "r");
    FILE *fout = fopen("spin.out", "w");

    int i,j;
    for (i = 0; i < N; i++){
        fscanf(fin, "%d %d", &wheels[i].speed, &wheels[i].size);
        for (j = 0; j < wheels[i].size; j++){
            fscanf(fin, "%d %d", &wheels[i].wedges[j].start, &wheels[i].wedges[j].end);
            add(&wheels[i].wedges[j].end, wheels[i].wedges[j].start);
        }
    }

    int time, position;
    for (time = 0; time < ROUND; time++){
        /* Check if aligned */
        for (position = 0; position < ROUND; position++){
            for (i = 0; i < N; i++){
                for (j = 0; j < wheels[i].size; j++)
                    if (aligned(i,j,position)) break; /* some wedge contains position */
                if (j == wheels[i].size) break; /* no wedge contains position */
            }
            if (i == N) break; /* if all wheel contain position */
        }
        if (position != ROUND) break; /* if some position all aligned */

        /* Update the positions of wedges */
        for (i = 0; i < N; i++){
            for (j = 0; j < wheels[i].size; j++){
                add(&wheels[i].wedges[j].start, wheels[i].speed);
                add(&wheels[i].wedges[j].end, wheels[i].speed);
            }
        }
    }

    if (time == ROUND)
        fprintf(fout, "none\n");
    else
        fprintf(fout, "%d\n", time);

    fclose(fin);
    fclose(fout);
    return 0;
}
