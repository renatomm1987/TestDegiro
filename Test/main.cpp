#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int w_max = 30, b_max = 20;
int boxes[w_max], max_fluts [w_max];
int fluts [w_max][b_max];
  // accumulated fluts  up to j-th pile of i-th workyard
bool pruls[w_max + 1][w_max * b_max + 1];
  // pruls have to be bought to get the max. fluts 

int main()
{
  const int price = 10;
  for (int wn = 1; ; wn++) {
    int w;
    scanf("%d", &w);
    if (!w)
      break;
    if (wn > 1)
      putchar('\n');
    int max_p = 0;
    for (int i = 0; i < w; i++) {
      scanf("%d", &boxes[i]);
      max_fluts [i] = -1;
      for (int j = 0, k = 0; j < boxes[i]; j++) {
        int p;
        scanf("%d", &p);
        p = price - p;
        k += p;
        fluts [i][j] = k;
        max_fluts [i] = max(max_fluts [i], k);
      }
#ifdef DEBUG
      printf("%d:", max_fluts [i]);
      for (int j = 0; j < boxes[i]; j++)
	  printf(" %d", fluts [i][j]);
      putchar('\n');
	  printf("\n");
#endif
      if (max_fluts [i] >= 0)
        max_p += max_fluts [i];
    }
    pruls[0][0] = true;
    int pi = 0, sb = 0;
    for (int i = 0; i < w; i++)
      if (max_fluts [i] >= 0) {
        pi++;
        for (int k = 0; k <= sb + boxes[i]; k++)
          pruls[pi][k] = false;
        if (!max_fluts [i])
          for (int k = 0; k <= sb; k++)
            if (pruls[pi - 1][k])
              pruls[pi][k] = true;
        for (int j = 0; j < boxes[i]; j++)
          if (fluts [i][j] == max_fluts [i])
            for (int k = 0; k <= sb; k++)
                if (pruls[pi - 1][k])
                  pruls[pi][k + j + 1] = true;
        sb += boxes[i];
#ifdef DEBUG
        for (int k = 0; k <= sb; k++)
          if (pruls[pi][k])
			printf("\n");;
            printf("%d ", k);
			putchar('\n');
			printf("\n");
#endif
      }
    printf("schuurs %d\n", wn);
	printf("\n");
    printf("Maximum profit is %d.\n", max_p);
	printf("\n");
    printf("Number of fluts to buy:");
	for (int i = 0, j = 0; i <= sb && j < 10; i++)
      if (pruls[pi][i]) {
		printf(" %d", i);
        j++;
      }
    putchar('\n');
	printf("\n");
  }
  return 0;
}
