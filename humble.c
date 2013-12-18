/*
  PROG: humble
  LANG: C
  ID: ranmocy1
*/

#include <stdio.h>
#include <limits.h>
typedef enum { false, true } bool;
#define MAX_N 100000
#define MAX_K 100

int K;
long N;
long humbles[MAX_N+1];
int primes[MAX_K+1], min_index[MAX_K+1];

int i,j;
long next;


/*
  Find the next humble number by searching:

  // humbles[i] * primes[j] > humbles[next - 1]
  humble[next] = min(humbles[i] * primes[j])

  Since for every primes[j], if humbles[i] * primes[j] <= humbles[next-1],
  then it will always humbels[i] * primes[j] <= humbles[next - 1].
  So we can save the minimal possible i for primes[j] into min_index[j].

  // i >= min_index[j]
  // humbles[i] * primes[j] > humbles[next - 1]
  humble[next] = min(humbles[i] * primes[j])
 */
int main()
{
    FILE *fin = fopen("humble.in", "r");
    FILE *fout = fopen("humble.out", "w");

    fscanf(fin, "%d %ld", &K, &N);
    for (i = 1; i <= K; i++){
        fscanf(fin, "%d", &primes[i]);
    }

    humbles[0] = 1;
    for (next = 1; next <= N; next++){
        humbles[next] = LONG_MAX;
        for (j = 1; j <= K; j++){
            while (humbles[min_index[j]] * primes[j] <= humbles[next-1]) {
                min_index[j]++;
            }
            if (humbles[min_index[j]] * primes[j] < humbles[next]){
                humbles[next] = humbles[min_index[j]] * primes[j];
            }
        }
    }

    fprintf(fout, "%ld\n", humbles[N]);
    fclose(fin);
    fclose(fout);
    return 0;
}
