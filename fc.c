/*
  PROG: fc
  LANG: C
  ID: ranmocy1
*/

#include <stdio.h>
#include <math.h>
#define MAX_N 10000
#define MAX_RANGE 1000000

int N;

double point[MAX_N][2];

int main()
{
  FILE *fin = fopen("fc.in", "r");
  FILE *fout = fopen("fc.out", "w");

  fscanf(fin, "%d", &N);

  // Start with the point at the most bottom
  int min_y = MAX_RANGE,
      start_index = -1;
  for (int i = 0; i < N; i++)
  {
    fscanf(fin, "%lf %lf", &point[i][0], &point[i][1]);
    if (point[i][1] < min_y)
    {
      min_y = point[i][1];
      start_index = i;
    }
  }

  double result = 0;
  if (N > 1)
  {
    // Initial line is horizontal
    double prevAngle = 0;
    int current_index = start_index;

    do
    {
      double min_diff = 7; // Angle diff in range of [0, 2pi]
      int next_index = -1;
      for (int i = 0; i < N; i++)
      {
        if (i == current_index)
          continue;

        // Find the min counter-clock-wise angel from the prev line
        double dx = point[i][0] - point[current_index][0],
               dy = point[i][1] - point[current_index][1];
        double angle = atan2f(dy, dx); // atan2f in range of [-pi,pi]
        double diff = angle - prevAngle; // diff in range of [0, 2pi]
        if (diff < 0)
        {
          diff += 2 * M_PI;
        }

        // fprintf(fout, "%d => %d, %lf\n", current_index, i, diff);
        if (diff < min_diff)
        {
          min_diff = diff;
          next_index = i;
        }
      }

      // Add the line to the result
      double dx = point[next_index][0] - point[current_index][0],
             dy = point[next_index][1] - point[current_index][1];
      result += sqrtf(dx * dx + dy * dy);
      prevAngle = atan2f(dy, dx);
      current_index = next_index;
      // fprintf(fout, "next_index: %d, result: %lf\n", next_index, result);

      // Repeat until we go back to the start point
    } while (current_index != start_index);
  }

  fprintf(fout, "%lf\n", result);
  fclose(fin);
  fclose(fout);
  return 0;
}
