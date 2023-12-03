
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isSymbolAdjacent(char* intstart, const char* datastart, const char* dataend, int linewidth)
{
  if ((intstart - datastart) % linewidth)
    if (*--intstart != '.') return 1;

  do
  {
    if (intstart - linewidth >= datastart)
      if (*(intstart - linewidth) != '.')
        return 1;
    if (intstart + linewidth < dataend)
      if (*(intstart + linewidth) != '.')
        return 1;
    ++intstart;
  }
  while (*intstart >= 0x30 && *intstart < 0x3A);

  if (intstart >= dataend) return 0;

  if (intstart - linewidth >= datastart)
    if (*(intstart - linewidth) != '.')
      return 1;
  if (intstart + linewidth < dataend)
    if (*(intstart + linewidth) != '.')
      return 1;

  return *intstart != '.';
}

int countdata(char* const data, char* const dataend, int linewidth)
{
  char* addr = data;

  int sum = 0;

  for (;;)
  {
    // Go until we find a digit
    while (*addr < 0x30 || *addr >= 0x3A)
      if (!*++addr) return sum;

    if (isSymbolAdjacent(addr, data, dataend, linewidth))
      sum += atoi(addr);

    while (*addr >= 0x30 && *addr < 0x3A) ++addr;
  }
}

int main(void)
{
  FILE* input = fopen("input.txt", "r");

  fseek(input, 0, SEEK_END);
  long datasize = ftell(input);
  fseek(input, 0, SEEK_SET);

  char* const data = malloc(datasize);
  fread(data, datasize, 1, input);
  fclose(input);

  data[datasize - 1] = 0;

  char* addr = data;

  while (*addr != '\n' && *addr) ++addr;
  int linewidth = addr - data + 1;

  while (*addr)
  {
    *addr = '.';
    addr += linewidth;
  }

  const int sum = countdata(data, data + datasize, linewidth);

  printf("sum is %d\n", sum);

  free(data);
}

