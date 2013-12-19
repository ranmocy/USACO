/*
  PROG: rect1
  LANG: C
  ID: ranmocy1
*/

#include <stdio.h>
#include <math.h>

typedef enum { false, true } bool;
typedef struct Point{
    int x,y;
} Point;
typedef struct Rect{
    Point lb,rt;  /* left-bottom, right-top, 1~10000 */
    int color;  /* 1~2500 */
} Rect;

int A,B,N;
Rect rect[1001];  /* rect[0] is on the most bottom */
long total_area[2501];  /* maximum is A*B ~= 10^8 */


int min(int x, int y)
{
    return (x < y) ? x : y;
}

int max(int x, int y)
{
    return (x > y) ? x : y;
}

/* return 0 if it's invalid */
long area(Rect rect)
{
    return max(0, (rect.rt.x - rect.lb.x) * (rect.rt.y - rect.lb.y));
}

/*
  When a intersects b,
  it means point a.lb is at left-lower of point b.rt,
  and point a.rt is at right-upper of point b.lb.
*/
bool intersect(Rect a, Rect b)
{
    return (a.lb.x <= b.rt.x) && (a.lb.y <= b.rt.y) &&
            (a.rt.x >= b.lb.x) && (a.rt.y >= b.lb.y);
}

/*
  calc `rect[current]` with last `depth` level

  +-+-----------+-+ <- current.rt
  | |     2     | |
  + +-----------+ +
  |0|rect[depth]|1|
  + +-----------+ +
  | |     3     | |
  +-+-----------+-+
  ^
  |
  current.lb
*/
void calc(Rect current, int depth)
{
    if (depth > N){
        total_area[current.color] += area(current);
        return;
    }

    if (!intersect(current, rect[depth])){
        calc(current, depth+1);}
    else{
        Rect r[4] = {
            {current.lb,
             { rect[depth].lb.x, current.rt.y },
             current.color},
            {{ rect[depth].rt.x, current.lb.y },
             current.rt,
             current.color},
            {{ max(current.lb.x, rect[depth].lb.x), rect[depth].rt.y },
             { min(current.rt.x, rect[depth].rt.x), current.rt.y },
             current.color},
            {{ max(current.lb.x, rect[depth].lb.x), current.lb.y },
             { min(current.rt.x, rect[depth].rt.x), rect[depth].lb.y },
             current.color}
        };

        int i;
        for (i = 0; i < 4; i++)
            if (area(r[i]) > 0) {
                calc(r[i], depth+1);}
    }

    return;
}


int main()
{
    FILE *fin = fopen("rect1.in", "r");
    FILE *fout = fopen("rect1.out", "w");

    fscanf(fin, "%d %d %d", &A, &B, &N);
    rect[0] = (Rect){ {0, 0}, {A, B}, 1};

    int i;
    for (i = 1; i <= N; i++){
        fscanf(fin, "%d %d %d %d %d",
               &rect[i].lb.x, &rect[i].lb.y,
               &rect[i].rt.x, &rect[i].rt.y,
               &rect[i].color);}

    for (i = N; i >= 0; i--){
        calc(rect[i], i+1);}

    for (i = 1; i<= 2500; i++){
        if (total_area[i] > 0){
            fprintf(fout, "%d %ld\n", i, total_area[i]);}}

    fclose(fin);
    fclose(fout);
    return 0;
}
