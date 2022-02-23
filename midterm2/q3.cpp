#include <cassert>
#include <iostream>

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AT THE END OF THE product FUNCTION

int product(int x, int y)
{
  if (x == 0 || y == 0)
  {
    return 0;
  }
  if (y < 0)
  {
    return -x + product(x, y + 1);
  }
  else
  {
    return x + product(x, y - 1);
  }
}
// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AT THE START OF THE product FUNCTION

int main()
{
  assert(product(7, 5) == 35);
  assert(product(-4, 8) == -32);
  assert(product(4, -8) == -32);
  assert(product(-4, -8) == 32);
  assert(product(-4, 0) == 0);
  assert(product(0, -8) == 0);
  assert(product(-4, 1) == -4);
  assert(product(1, -8) == -8);
  assert(product(4, 1) == 4);
  assert(product(1, 8) == 8);

  std::cout << "All tests succeeded" << std::endl;
}
