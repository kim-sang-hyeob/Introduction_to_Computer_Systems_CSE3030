/*
 * conditional(x, y, z): Return z if x is 0, return y otherwise.
 * - Ex) conditional(2, 4, 5) = 4, conditional(0, 1, 2) = 2
 */
int conditional(int x, int y, int z)
{
  int mask = ((!!x) << 31) >> 31; // !!x : 0인경우 return 0; else return 1; 이후 shift 를 통해서 모은 비트 같도록 설정.
  int cal = ((~mask) & z) + ((mask)&y);

  return cal; // TODO
}
