/*
  PROG: contact
  LANG: C
  ID: ranmocy1
*/

#include <stdio.h>
#include <string.h>
typedef enum { false, true } bool;
#define PATTERN_LENGTH_MAX 12
#define PATTERN_MAX 8191

int A,B, /* 1~12 */ N; /* 1~50 */
/* 2^12*2-1 patterns with 12 length */
long count[PATTERN_MAX+1];  /* frequncies of patterns */


/*
  0 -> 10 -> 2
  1 -> 11 -> 3
  00 -> 100 -> 4
  01 -> 101 -> 5
  10 -> 110 -> 6
  11 -> 111 -> 7
 */
int encode(char input[PATTERN_LENGTH_MAX+1])
{
    int len = strlen(input);
    int ans = 1;
    while (len--) ans = ans * 2 + input[len] - 48;
    return ans;
}

void decode(int input, char ans[PATTERN_LENGTH_MAX+1])
{
    int len = 0;
    while (input > 1) {
        ans[len++] = input % 2 + 48;
        input /= 2;
    }
    ans[len] = 0;
}


/*
  Scan the input string, save the last B length chars.
  For every time, scan the last A~B length chars,
  and add one to the frequncies.
  Sort and output.
 */
int main()
{
    FILE *fin = fopen("contact.in", "r");
    FILE *fout = fopen("contact.out", "w");

    fscanf(fin, "%d %d %d", &A, &B, &N);

    char current[PATTERN_LENGTH_MAX+1] = "";
    while (!feof(fin)) {
        char t = fgetc(fin);
        if ((t < 48) || (t > 49)) continue;  /* besides 0 and 1 */

        /* Update current */
        int length = strlen(current);
        if (length == 12) length--;
        while (length--) current[length+1] = current[length];
        current[0] = t;

        /* Copy current */
        char temp[PATTERN_LENGTH_MAX+1];
        length = strlen(current) + 1;
        while (length--) temp[length] = current[length];

        /* Count all patterns with length A~B */
        length = strlen(temp);
        while (length > B) temp[--length] = 0;
        while ((length >= 0) && (length >= A)) {
            count[encode(temp)]++;
            temp[--length] = 0;
        }
    }

    int i;
    char pattern[PATTERN_LENGTH_MAX+1] = "";
    while (N--) {
        long max = 0, index = 0;
        for (i = 2; i <= PATTERN_MAX; i++)
            if (count[i] > max) {
                index = i;
                max = count[i];
            }
        if (max == 0) break;

        fprintf(fout, "%ld", max);

        int printed = 0;
        for (i = 2; i <= PATTERN_MAX; i++)
            if (count[i] == max) {
                if (printed % 6 == 0)
                    fprintf(fout, "\n");
                else
                    fprintf(fout, " ");
                printed++;

                count[i] = 0;
                decode(i, pattern);
                int length = strlen(pattern);
                while (length--) fprintf(fout, "%c", pattern[length]);
            }
        fprintf(fout, "\n");
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
