/*
 * Pythagorean triples
 * 
 * http://www.spoj.com/problems/PYTRIP2/
 *
 */
#include <stdio.h>
#include <math.h>

int intsqrt(int num, int min);

int main(void)
{
    int i, j, t, start, end, d, diff;
    long numtriple;
    double numsq2;

    numsq2 = sqrt(2.0);

    //num testcases
    scanf("%d", &t);

    while(t-->0)
    {
        fflush(stdin);
        scanf("%d %d", &start, &end);
 
        numtriple = 0;
        
        // start from end, till (start - 2) as the hypotenuse
        for(i = end; i > start + 1 ; i--)
        {
              diff = 0;
              /* start from i-1 as the larger side till start - 1, considering 'start' will be the final minimum side
                 considering: side1 * side1 + side2 * side2 = hypotenuse * hypotenuse, ------- equation (A)
                 side 2 > side 1
                 => side 2 * side 2 > side 1 * side 1
                 => side 2 * side 2 + side 2 * side 2 > side 1 * side 1 + side 2 * side 2
                 => 2 * side 2 * side 2 > hypotenuse * hypotenuse (from equation (A))
                 => hypotenuse < square_root(2) * side 2 ------ this is checked in below condition (i < numsq2 * j)
                 this condition restricts the check till few instead of checking all numbers till (start - 1)  */
              for(j = i - 1; (j > start) && (i < numsq2 * j); j--)
              {
                    /* here the intention is find whether the diff of squares of i & j is a perfect square
                     on data analysis, we can arrive that the difference can be calculated as below without actually 
                     calculating the difference between squares:
                    num          square    difference = square(num) - square(num+1)
                    1	         1            1*2 + 1
                    2	         4            2*2 + 1
                    3	         9            3*2 + 1
                    4	         16           4*2 + 1
                    5	         25          */

                    diff += j*2 + 1;
                    // following function returns -1 if the diff is not a perfect square of an integer <= start
                    d = intsqrt(diff, start);
                    // if d is found to be perfect square but not equal to larger side, then increment the count
                    if ((d >0) && (d != j))
                      ++numtriple;
               }
        }
        printf("%ld\n", numtriple);
    }
    fflush(stdin);
    getchar();
    return 0;
}
int intsqrt(int num, int min)
{
    int sr, left, right;
    unsigned long d;

    // get the 1's digit
    d = num%10;
    // 1's digit of any perfect must be one of the digits in: 0, 1, 4, 5, 6, 9
    if(!((d == 0) || (d == 1) || (d == 4) || (d == 5) || (d == 6) || (d == 9)))
        return -1;
    // in case the number is not in the specified limit
    if(min * min > num)
        return -1;
    left = 0;
    right = num;

    // find the integer square root of given number
    while (sr = (left + right)/2)
    {
        if((d = sr*sr) > num)
              right = sr;
        else if (d < num)
             left = sr;
        else
             return sr;
        if(left == right - 1)
        {
              if(left * left == num)
                      return left;
              if(right * right == num)
                       return right;
              else
                       return -1;
        }
    }
    return -1;
}
