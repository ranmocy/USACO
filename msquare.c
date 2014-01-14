/*
  PROG: msquare
  LANG: C
  ID: ranmocy1
*/

#include <stdio.h>
#include <string.h>
#define N 8
#define N_FAC 40320  /* 8! */
#define INF N_FAC+1
typedef enum { false, true } bool;

const int fac[N+1] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320};
unsigned int queue[N_FAC], p[N_FAC], step[N_FAC], target;
bool visited[N_FAC];


void get_digits(long input, int *d)
{
    int i;
    for (i = N-1; i >= 0; i--) {
        d[i] = input % 10;
        input /= 10;
    }
}

long build_digits(int *d)
{
    int i;
    long ans = 0;
    for (i = 0; i < N; i++){
        ans = ans * 10 + d[i];
    }
    return ans;
}

/* cantor extent */
unsigned int encode(long input)
{
    int i, j, t, d[N], ans = 0;
    get_digits(input, d);
    for (i = 0; i < N; i++){
        t = 0;
        for (j = 0; j < i; j++) if (d[i] > d[j]) t++;
        ans += fac[N - i - 1] * (d[i] - 1 - t);
    }
    return ans;
}

/* Anti-cantor extent */
long decode(unsigned int x)
{
    int i, j, d[N];
    bool appeared[N+1];
    for (i = 1; i <= N; i++) appeared[i] = false;
    for (i = 0; i < N; i++) {
        d[i] = x / fac[N - i - 1] + 1;
        x %= fac[N - i - 1];
        for (j = 1; j <= d[i]; j++) if (appeared[j]) d[i]++;
        appeared[d[i]] = true;
    }
    return build_digits(d);
}

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

/*
  12345678 => 87654321
*/
unsigned int A(unsigned int a)
{
    long t = decode(a);
    int d[N];
    get_digits(t, d);
    swap(&d[0], &d[7]);
    swap(&d[1], &d[6]);
    swap(&d[2], &d[5]);
    swap(&d[3], &d[4]);
    t = build_digits(d);
    return encode(t);
}

/*
  12345678 => 41236785
*/
unsigned int B(unsigned int a)
{
    long t = decode(a);
    int d[N];
    get_digits(t, d);
    swap(&d[0], &d[1]);  /* 2134 5678 */
    swap(&d[0], &d[2]);  /* 3124 5678 */
    swap(&d[0], &d[3]);  /* 4123 5678 */
    swap(&d[7], &d[6]);  /* 4123 5687 */
    swap(&d[7], &d[5]);  /* 4123 5786 */
    swap(&d[7], &d[4]);  /* 4123 6785 */
    t = build_digits(d);
    return encode(t);
}

/*
  1234 5678 => 1724 5368
*/
unsigned int C(unsigned int a)
{
    long t = decode(a);
    int d[N];
    get_digits(t, d);
    swap(&d[1], &d[2]);  /* 1324 5678 */
    swap(&d[1], &d[5]);  /* 1624 5378 */
    swap(&d[1], &d[6]);  /* 1724 5368 */
    t = build_digits(d);
    return encode(t);
}



/*
  BFS
  Use N numbers to indicate a state.
  Encode the state to a long by contor method.

  queue[i] indicates the encoded number.
  p[i] indicates the position of queue[i]'s parent.
  step[i] indicates how to transform from its parent.
*/
int main()
{
    FILE *fin = fopen("msquare.in", "r");
    FILE *fout = fopen("msquare.out", "w");

    int i, t;
    long temp = 0;
    for (i = 0; i < N; i++) {
        fscanf(fin, "%d", &t);
        temp = temp * 10 + t;
    }
    target = encode(temp);

    int qhead = 0, qtail = 0;
    for (i = 1; i < N_FAC; i++) visited[i] = false;
    queue[0] = 0;
    visited[0] = true;

    while (qhead <= qtail) {
        unsigned int current_state = queue[qhead], parent = qhead, t;
        qhead++;
        if (current_state == target) break;

        t = A(current_state);
        if (!visited[t]){
            visited[t] = true;
            queue[++qtail] = t;
            p[qtail] = parent;
            step[qtail] = 1;
        }

        t = B(current_state);
        if (!visited[t]){
            visited[t] = true;
            queue[++qtail] = t;
            p[qtail] = parent;
            step[qtail] = 2;
        }

        t = C(current_state);
        if (!visited[t]){
            visited[t] = true;
            queue[++qtail] = t;
            p[qtail] = parent;
            step[qtail] = 3;
        }
    }

    int count = 0, current = qhead - 1, res[N_FAC];
    while (current != 0) {
        res[count] = step[current];
        count++;
        current = p[current];
    }
    fprintf(fout, "%d\n", count);

    while (--count >= 0) fprintf(fout, "%c", res[count] + 64);
    fprintf(fout, "\n");

    fclose(fin);
    fclose(fout);
    return 0;
}
