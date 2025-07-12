/*
 * absVal(x): return the absolute value of x.
 * - Assume that INT_MIN (-2^31) is not provided as an input.
 * - Ex) absVal(2) = 2, absVal(-1) = 1
 */
int absVal(int x)
{

  int mask = (x >> 31);              // 음수:1111 , 양수:0000
  int cal = (x ^ mask) + (1 & mask); // xor 계산 + (양수면 +0 , 음수면 +1)

  return cal; // TODO
}
