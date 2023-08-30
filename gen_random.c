#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
  FILE *fwr;
  for (int i = 0; i < 17; i++)
  {
    char *str = (char *)calloc(100, sizeof(char));
    sprintf(str, "E:\\collage\\c\\sorting\\resources\\nums2^%d.txt", i);
    fwr = fopen(str, "w");
    int p = pow(2, i);
    for (int j = 0; j < p; j++)
    {
      int a = rand() % 2;
      if (a == 0)
      {
        fprintf(fwr, "%d\n", rand());
      }
      else
      {
        fprintf(fwr, "%d\n", (-1) * rand());
      }
    }
    fclose(fwr);
  }
  return 0;
}

// E:\collage\c\sorting\resources