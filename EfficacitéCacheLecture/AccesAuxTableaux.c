#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

int **a1, **a2, **a3; // Array pointer déclarations

// intel X86 time measurement, using clock ticks
static inline uint64_t getTicks()
{
  uint64_t a, d;
  asm volatile("rdtsc" : "=a" (a),"=d" (d));
  return (d << 32) | a;
}


int **allocAndFillArray(int LINES, int COLUMNS, int value)
{
  int ** arrayPointer;
  arrayPointer = malloc(LINES*sizeof(int *)); // Array alocation
  for (int line = 0; line < LINES; line++)
    {
      arrayPointer[line] = malloc(COLUMNS*sizeof(int));
    }
  for (int line = 0; line < LINES; line++) // Array value setting
    {
      for (int column = 0; column < COLUMNS; column++)
        {
          arrayPointer[line][column] = value;
        }
    }
  return arrayPointer;
}

long linearAccess (int **a, int LINES, int COLUMNS)
{
  long sum = 0;

  for (int line = 0; line < LINES; line++)
    {
      for (int column = 0; column < COLUMNS; column++)
        sum += a1[line][column];
    }
  return sum;
}  

long randomAccess (int **a, int LINES, int COLUMNS)
{
  long lrandom, crandom, sum = 0;
  for (int line = 0; line < LINES; line++)
    {
      for (int column = 0; column < COLUMNS; column++)
        {
          lrandom = rand() % LINES;
          crandom = rand() % COLUMNS;
          sum += a3[lrandom][crandom];
        }
    }
  return sum;
}
long columnAccess (int **a, int LINES, int COLUMNS)
{
  long sum = 0;

  for (int column = 0; column < COLUMNS; column++)
    {
      for (int line = 0; line < LINES; line++)
        sum += a2[line][column];
    }
  return sum;
}

int main(int argc, char *argv[])
{
  int LINES, COLUMNS;
  long sum = 0;
  uint64_t begin, end;

  if (argc < 3)
    {
      fprintf (stderr, "Give 2 parameters LINES and COLUMN size\n");
      fprintf (stderr, "./AccesAuxTableaux 100 1000\n");
        exit (-1);
    }
  LINES   = atoi(argv[1]);
  COLUMNS = atoi(argv[2]);

  a1 = allocAndFillArray(LINES, COLUMNS, 1);
  a2 = allocAndFillArray(LINES, COLUMNS, 42);
  a3 = allocAndFillArray(LINES, COLUMNS, 24);

  begin = getTicks();
  sum += linearAccess(a1, LINES, COLUMNS);
  end = getTicks();
  uint64_t time_spent1 = end - begin;

  begin = getTicks();
  sum += columnAccess(a2, LINES, COLUMNS);
  end = getTicks();
  uint64_t time_spent2 = end - begin;

  begin = getTicks();
  sum += randomAccess(a3, LINES, COLUMNS);
  end = getTicks();
  uint64_t time_spent3 = end - begin;
  // size (byte), ticks for linear, ticks for colum, ticks for random
  printf("%ld %ld %ld %ld \n", LINES*COLUMNS*sizeof (int), time_spent1, time_spent2, time_spent3);
  return sum%8;
}
