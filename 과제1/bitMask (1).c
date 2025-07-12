/*
 * bitMask(x): Return a mask that has (32 - x) zeros followed by x ones.
 * - Assume 0 <= x <= 31
 * - Ex) bitMask(0) = 000...000 in binary = 0
 * - Ex) bitMask(31) = 011...111 in binary = 0x7fffffff
 */
int bitMask(int x)
{
  // 이번 과제의 대전제 : >>(지금 가지고 있는 제일 왼쪽의 부호로 채워짐) ,  <<(0으로 채워짐) 직접 확인 완료.
  // x 의 개수만큼 오른쪽에 1표시 (31) -> 0111(1이 31개.)
  // x = 0 인경우 예외처리 해야 함. 32비트를 옮기는 연산 x --> 에러 발생함.
  // 에러가 너무 많이 생겨서 애초에 시작 비트 자체를 조정함.

  int bit_mask = ~((1) << 31);           // 01111... 로 시작
  int cal = bit_mask >> (31 + (~x + 1)); // 31 - x 만큼 shift

  return cal; // TODO
}
