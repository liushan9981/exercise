#include <stdio.h>
#include "combination.h"

long mynum(long num)
{
  long remain = num, remain_temp;
  long sum = 0, sum_temp, num_temp;


  while (remain > 0)
  {
        remain_temp = remain;
        num_temp = num;
        sum_temp = 1;
        while (remain_temp > 0)
        {
              sum_temp *= num_temp;
              num_temp--;
              remain_temp--;
        }
        sum += sum_temp;
        remain--;
  }

  // printf("sum: %ld\n", sum);
  return sum;

}
