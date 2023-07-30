/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
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
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


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

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

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
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
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
// 1
/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y)
{
  // 结合异或的定义: x^y = (x & ~y) | (~x  & y) , 德摩根定律以及结合律可推导
  // 参考：https://zh.wikipedia.org/wiki/%E9%80%BB%E8%BE%91%E5%BC%82%E6%88%96
  // 参考: https://zh.wikipedia.org/wiki/%E5%BE%B7%E6%91%A9%E6%A0%B9%E5%AE%9A%E5%BE%8B
  return ~(x & y) & ~((~x & ~y));
}
/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void)
{
  // 表达整型的最小补码, 也就是符号位为1, 尾数31个0. 可以对1使用左移运算, 向左移动31位
  return 0x1 << 31;
}
// 2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x)
{
  // 最大的补码x为0x7FFFFFFF，其满足x = ~(x + 1)。除了0x7FFFFFFF以外，-1也满足该表达式。
  // ~(-1)=0，而~(0x7FFFFFFF)=-1，因此，可以使用!!(~x)排除掉-1
  return !(~(x + 1) ^ x) & !!(~x);
}
/*
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x)
{
  // 那么我们可以先设定一个基准，其必定是技术为为1，偶数位位0
  // 0xAAAAAAAA -> 10101010101010101010101010101010
  // 但是限制了常量的范围，所以需要先构造基准  Illegal constant (0xAAAAAAAA) (only 0x0 - 0xff allowed)
  // 0xAA -> 10101010
  int mask = 0xAA;
  // (10101010 | 1010101000000000) = 1010101010101010, 得到低16位合法的位表达
  mask |= (mask << 8);
  // 同理可得
  mask |= (mask << 16);
  // 然后将给定整数与该基准进行按位与(&), 如果是符合规则的数, 结果必定与基准相等
  return !((x & mask) ^ mask);
}
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x)
{
  // 补码的加法逆元
  // 通过补码运算求取加法逆元
  // 当前x就是使用补码表示的 a
  // 对x按位取反获得反码 b, 而后+1 c
  // 原理 a+b=-1, a+c=0, 所以c是a的加法逆元
  return ~x + 1;
}
// 3
/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x)
{
  // 观察[0x30,0x39]的二进制表达, 可知:
  // 若前3位=110，则x一定位于30~39之间;
  // 若前5位=11100，则x一定位于30~39之间
  // 位级表达也可以进行范围表达
  return !((x >> 3) ^ 0x6) | !((x >> 1) ^ 0x1c);
}
/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z)
{
  // 0&x=0, ~0&x=x, ~0+1=0, 0|x=x
  // 利用上述规则即可求取结果
  int mask = !x + ~0x0;
  return (mask & y) | (~mask & z);
}
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y)
{
  // x的符号位
  int sign_x = x >> 31;
  // y的符号位
  int sign_y = y >> 31;
  // x和y是否相同符号
  int sign_xy = sign_x ^ sign_y;
  // y-x，即差值
  int diff = y + (~x + 1);
  // 差值的符号位
  int diff_sign = diff >> 31;
  // 符号位不同时正数为大, 符号位相同时看差值符号(y-x >=0, 则diff_sign >=0, 则符号位为0)
  return (!!(sign_xy & sign_x)) | (!sign_xy & !diff_sign);
}
// 4
/*
 * logicalNeg - implement the ! operator, using all of
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int logicalNeg(int x)
{
  // 核心，只需要判定x是否等于0
  // 0和其相反数0执行按位或运算，结果的符号位为0；除0以外，任何一个数和它的相反数执行按位或运算，结果的符号位为1
  // 这里+1的原因：是由于对于有符号数右移的问题，C语言中虽然未明文规定，但是实际上，几乎所有的编译器/机器组合
  // 都对有符号数使用算数右移. 所以这里除0以外, 其他数与自身加法逆元做|运算的结果的符号位均为1, 右移将填充1
  return ((x | (~x + 1)) >> 31) + 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x)
{
  int b16, b8, b4, b2, b1;
  int sign_x = x >> 31;
  // 将负数取反, 这样都是找1
  x = (sign_x & ~x) | (~sign_x & x);
  // 二分
  // 1.若高16位有1，则至少需要16位
  b16 = (!!(x >> 16)) << 4;
  x >>= b16;
  // 2.若高8位有1，则还需要8位
  b8 = (!!(x >> 8)) << 3;
  x >>= b8;
  // 3.若高4位有1，则还需要4位
  b4 = (!!(x >> 4)) << 2;
  x >>= b4;
  // 4.若高2位有1，则还需要2位
  b2 = (!!(x >> 2)) << 1;
  x >>= b2;
  // 5.若高1位有1，则还需要1位
  b1 = (!!(x >> 1));
  x >>= b1;
  // 6.加上符号位
  return b16 + b8 + b4 + b2 + b1 + x + 1;
}
// float
/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf)
{
  const unsigned sign_mask = 0x1 << 31;
  const unsigned exp_mask = 0xFF << 23;
  const unsigned exp_plus_one = 0x1 << 23;
  const unsigned tail_mask = 0x007FFFFF;
  unsigned exp = uf & exp_mask;

  // 1.若阶码均为1
  if (exp == exp_mask)
  {
    return uf;
  }

  // 2.若阶码为0，即输入为0或者接近0的小数
  if (exp == 0)
  {
    unsigned sign = uf & sign_mask;
    unsigned tail = uf & tail_mask;
    return sign | (tail << 1);
  }

  // 3.否则, 则为规格化的值，阶码+1
  uf += exp_plus_one;
  return uf;
}
/*
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf)
{
  const unsigned sign_mask = 0x1 << 31;
  const unsigned exp_mask = 0xFF << 23;
  const unsigned tail_mask = 0x007FFFFF;
  int sign = uf & sign_mask;
  int exp = uf & exp_mask;
  int tail = uf & tail_mask;
  exp = (exp >> 23) - 127;
  // 1.若指数为负数
  if (exp < 0)
  {
    return 0;
  }
  // 2.若指数超出了范围
  if (exp > 31)
  {
    return sign_mask;
  }
  // 3.加上隐含位1
  tail |= 1 << 23;
  if (exp <= 23)
  {
    tail >>= 23 - exp;
  }
  else
  {
    tail <<= exp - 23;
  }
  // 4.若结果为负数
  if (sign)
  {
    return ~tail + 1;
  }
  return tail;
}
/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatPower2(int x)
{
  // reference: https://www.hegongshan.com/2021/05/06/csapp-1-data-lab/
  // 常量 INF 表示正无穷大的浮点数表示。在单精度浮点数中，正无穷大的表示是指数部分全为1，尾数部分全为0，即0xFF << 23
  const int INF = 0xFF << 23;
  int exp = x + 127;
  // 1.若为0或者负数
  if (exp <= 0)
  {
    return 0;
  }
  // 2.阶码太大, 溢出
  if (exp >= 0xFF)
  {
    return INF;
  }
  return exp << 23;
}
