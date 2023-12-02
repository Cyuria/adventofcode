
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void replaceLine(char*);
int solveLine(const char*);

static const char* numbers[] = {
  "one",
  "two",
  "three",
  "four",
  "five",
  "six",
  "seven",
  "eight",
  "nine",
};

void replaceLine(char* line)
{
  do {
    for (uint8_t n = 0; n < 9; ++n)
    {
      if (strncmp(line, numbers[n], strlen(numbers[n]))) continue;
      *line = (char) n + '1';
      break;
    }
  } while (*++line);
}

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

int main(void)
{
  int sum = 0;
  FILE* input = fopen("input.txt", "r");
  size_t linesize;
  ssize_t linelen;
  char* line = NULL;

  while ((linelen = getline(&line, &linesize, input)) != -1)
  {
    line[linelen - 1] = '\0';
    replaceLine(line);
    sum += solveLine(line);
  }

  free(line);
  fclose(input);

  printf("sum of solutions is %d\n", sum);
}

