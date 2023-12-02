
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int solveLine(const char* line)
{
  int8_t first;
  int8_t last;
  for (;;)
  {
    if (!*line) return -1;
    if (*line >= 0x30 && *line <= 0x39)
    {
      first = last = *line - 0x30;
      break;
    }
    ++line;
  }
  while (*++line)
  {
    if (*line < 0x30 || *line > 0x39) continue;
    last = *line - 0x30;
  }
  return 10 * first + last;
}

int main()
{
  int sum = 0;
  FILE* input = fopen("input.txt", "r");
  size_t linesize;
  int linelen;
  char* line = NULL;

  while ((linelen = getline(&line, &linesize, input)) != -1)
  {
    line[linelen - 1] = '\0';
    sum += solveLine(line);
  }

  free(line);
  fclose(input);

  printf("sum of solutions is %d\n", sum);
}

