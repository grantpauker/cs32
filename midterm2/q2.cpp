#include <cassert>
#include <iostream>
#include <list>
#include <vector>

#define PRINT(l)                                 \
  for (auto it = l.begin(); it != l.end(); it++) \
  {                                              \
    std::cout << *it << ", ";                    \
  }                                              \
  std::cout << std::endl;
// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AT THE END OF THE smallbig FUNCTION
bool smallbig(std::vector<int> &c1, std::list<int> &c2)
{
  if (c1.size() != c2.size())
  {
    return false;
  }
  int i = 0;
  for (auto it = c2.begin(); it != c2.end(); it++)
  {
    if (c1[i] > *it)
    {
      int tmp = c1[i];
      c1[i] = *it;
      *it = tmp;
    }
    i++;
  }
  return true;
}
// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AT THE START OF THE smallbig FUNCTION

int main()
{
  std::vector<int> v;
  std::list<int> li;
  assert(smallbig(v, li));

  int x[4] = {7, -5, 3, 6};
  int y[4] = {4, 1, 3, 2};
  int expectx[4] = {4, -5, 3, 2};
  int expecty[4] = {7, 1, 3, 6};
  std::vector<int> small(x, x + 4);
  std::list<int> big(y, y + 4);
  assert(smallbig(small, big));
  std::vector<int> expectsmall(expectx, expectx + 4);
  std::list<int> expectbig(expecty, expecty + 4);
  assert(small == expectsmall && big == expectbig);

  std::list<int> big2(y, y + 3);
  assert(!smallbig(small, big2)); // different num of elements

  std::cout << "All tests succeeded" << std::endl;
}
