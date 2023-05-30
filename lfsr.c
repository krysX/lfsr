#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define uint unsigned int
#define DEFAULT_SEED __UINT32_MAX__ / 2;

uint count = 100;

int main(int argc, char* argv[]) {
  float from = 0;
  float to = 0;
  //int precision = 0;

  uint seed = DEFAULT_SEED;

  FILE* fptr = fopen("seed.txt", "r");
  if(fptr != NULL)   
     fscanf(fptr, "%u", &seed);
  if(seed == 0) 
    seed = DEFAULT_SEED;
  fclose(fptr);

  if(argc == 1) {
    printf("Random Number Generator by krastevs v1.0\n");
    printf("--------------------------------------- \n");
    printf("Input how many numbers you would like: ");
    scanf("%u", &count);
    printf("Input a lower bound: ");
    scanf("%f", &from);
    printf("Input an upper bound: ");
    scanf("%f", &to);
    //printf("Input how many digits of precision you want: ");
    //scanf("%u", &precision);
    printf("-------------------------------------\n");
    printf("Here are %d random numbers between %.2f and %.2f: \n", count, from, to);
  } else if(argc == 4){
    count = atoi(argv[1]);
    //printf("count: %u\n", count);
    from  = atof(argv[2]);
    //printf("from: %f\n", from);
    to    = atof(argv[3]);
    //printf("to: %f\n", to);
  } else if (argc == 2) {
    if(strcmp(argv[1], "-h") == 0) {
      printf("\nUSAGE: lfsr [count] [from] [to]\n");
      return 0;
    } 
  }

 
  for(uint i = 0; i < count; i++) {
    // The taps with the maximum length for 32 bits are [1, 5, 6, 31] (0-indexed)
    uint newDigit = (seed >> 30) ^ ((seed >> 26) & 1) ^ ((seed >> 25) & 1) ^ (seed & 1);
    seed = seed >> 1 | (newDigit << 31);
    float range = to - from;
    float randF = (float)seed / (float)__UINT32_MAX__ * range + from;
    printf("%.2f\n", randF);
    //char c = 0; scanf("%c", &c);
  }
  fptr = fopen("seed.txt", "w");
  fprintf(fptr, "%u", seed);
  fclose(fptr);
}
