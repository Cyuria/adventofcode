
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void checkCol(int, char);
void checkList(char*);
int gameMinSetPower(char*);

static int minred;
static int mingreen;
static int minblue;

void checkCol(int num, char colour)
{
  if (colour == 'r')
  {
    if (num > minred) minred = num;
    return;
  }
  if (colour == 'g')
  {
    if (num > mingreen) mingreen = num;
    return;
  }
  if (colour == 'b')
  {
    if (num > minblue) minblue = num;
    return;
  }
}

void checkList(char* list)
{
  /* 6 red, 4 green, 1 blue; */
  while (*list)
  {
    int n = atoi(list);
    while (*list != ' ') ++list;
    checkCol(n, *++list);
    while (*list != ' ')
    {
      if (*list == ';' || !*list) return;
      ++list;
    }
    ++list;
  }
}

/* returns 0 if not possible or the gameID if possible */
int gameMinSetPower(char* game)
{
  minred = mingreen = minblue = 0;

  game += 5; // skip to data
  int gid = atoi(game);
  while (*game != ' ') ++game; ++game;

  for (;;)
  {
    checkList(game);

    while (*game != ';') {
      if (!*game) return minred * mingreen * minblue;
      ++game;
    }
    game += 2;
  }

  return minred * mingreen * minblue;
}

int main(void)
{
  //printf("%d\n", gameMinSetPower("Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red"));
  int sum = 0;

  FILE* input = fopen("input.txt", "r");

  char* line = NULL;
  size_t size = 0;
  ssize_t len;

  while ((len = getline(&line, &size, input)) != -1)
  {
    line[len] = '\0';
    sum += gameMinSetPower(line);
  }

  free(line);
  fclose(input);

  printf("sum of possible game ids is %d\n", sum);
}

