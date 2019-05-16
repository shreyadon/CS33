/* 
 * CS:APP Data Lab 
 * 
 * <Shreya Donepudi 504795932 classsdo>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  int result;
  result  = ~x + 1;/* negation plus one by definition*/
  return result;
}
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {

  int flip;
  int result;
  flip = (~x | ~y); /*de morgan's laws*/
  result = ~flip;
  return result;

}
/* 
 * anyOddBit - return 1 if any odd-numbered bit in word set to 1
 *   Examples anyOddBit(0x5) = 0, anyOddBit(0x7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyOddBit(int x) {
   /*Since, we are not allowed to use the variables as big as 0xAAAAAAAA,
 * we split the 32 bit integer into four parts  */
   int mask, first, second, third, fourth, sum, result;
   mask = 0xAA; /* the mask is the 8 bit integer 10101010, that has 1's in all it's odd-numbered bits */
   /*check each of the four 8 bit parts using the & operator with the mask */
   first = x & mask;
   second = (x >> 8) & mask;
   third = (x >> 16) & mask;
   fourth = (x >> 24) & mask;
   /*add all the numbers to get back an accurate 32 bit representation*/
   sum = first + second + third + fourth;
   /*finally, use the ! twice to return 0 if there is no odd bit, else return 1*/ 
   result = !(!sum);
   
   return result;
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
  int remainder;
  int sign;
  int correction;
  remainder = (1 << n) + ~0; /* this is the highest remainder that you can get when you divide any number by n.*/
  /*right shift by 31 to see whether it is negative or positive.*/
  sign  = x >> 31; /* if it is negative or overflows - sign = -1 else sign = 0. */
  correction = remainder&sign; /* if it is negative or overflows - correction = remainder else correction = 0. */
  return ((x + correction) >> n); /* adding the correction to x will rectify the floor function problem when the number is negative. */
}
/* 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
  int sign_x, sign_y, sign_sum, samesign_xy, samesign_sum, result;
  sign_x = (x >> 31);
  sign_y = (y >> 31);
  sign_sum = ((x + y) >> 31);
  /* the sum of x and y overflows when the signs of x and y are the same but the sign of the sum is different */
  samesign_xy = sign_x ^ sign_y;
  /* samesign_xy will be 0 if x and y have the same sign, else it will be 1 */
  samesign_sum = sign_x ^ sign_sum;
  /*samesign_sum will be 0 if x and the sum (x + y) have the same sign, else it will be 1*/
  /*if x, y and the sum have the same sign then the result will be 1*/
  /*if x, y have the same sign but the sum doesn't the result will be 0*/
  result = (~samesign_xy & samesign_sum);
  /*in order for the function to return the correct integer we use the ! operator on the result*/
  return !result;
}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
  int sign_x, sign_y, temp, same_sign, result;
  sign_x = x >> 31;
  sign_y = y >> 31;
  temp = (x + ~y); /* sign bit of temp is 0 if x is greater, else it is 1*/
  same_sign = !(temp >> 31); /* here, if x is positive and y is negative, it will return 1 regardless of their values. 
  else, same_sign will be returned unless x is not negative when y is positive*/
  result = (!sign_x & sign_y) | (same_sign & (!sign_x | sign_y));
  return result; 
}
/* 
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c) {
  int bitmask, correction, result; /* 8 bits = 1 byte */
  bitmask = 0xff;/* all 111... of 8 bits*/
  correction = n << 3; /* multiply by 8*/
  bitmask = ~(bitmask << correction);/* shift by 8 bits, and use the ! operator to a 8 bit mask of all 000... */
  c = c << correction; /* shift the bits of c into the nth byte */
  result = (x & bitmask) | c; /* By using the & operator, change x's nth byte to 0 and replace it with c */
  return result;
}
/* 
 * tc2sm - Convert from two's complement to sign-magnitude 
 *   where the MSB is the sign bit
 *   You can assume that x > TMin
 *   Example: tc2sm(-5) = 0x80000005.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 4
 */
int tc2sm(int x) {
   int temp, sign;
   temp = (x >> 31); /*shift right by 31 to create a mask of either 1s or 0s*/ 
   sign = (temp & 0x1);/*use the & operator to figure find out the sign */
   return (sign<<31)+((x^temp)+sign);/*signs don't change*/
}
