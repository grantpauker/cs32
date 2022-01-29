#include <stack>
#include <string>
#include <iostream>

class Coord
{
public:
  Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
  int r() const { return m_r; }
  int c() const { return m_c; }

private:
  int m_r;
  int m_c;
};

/* Return true if there is a path from (sr,sc) to (er,ec) through the maze; return false otherwise */
bool pathExists(std::string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
  std::stack<Coord> coord_stack;
  coord_stack.push(Coord(sr, sc));
  maze[sr][sc] = '@';
  while (!coord_stack.empty())
  {
    Coord top = coord_stack.top();
    coord_stack.pop();
    // std::cout << "(" << top.r() << ", " << top.c() <<")" << std::endl; // for question 2
    if (top.r() == er && top.c() == ec)
    {
      return true;
    }
    Coord west(top.r(), top.c() - 1);
    Coord south(top.r() + 1, top.c());
    Coord east(top.r(), top.c() + 1);
    Coord north(top.r() - 1, top.c());
    Coord directions[4] = {west, south, east, north};
    for (int i = 0; i < 4; i++)
    {
      int r = directions[i].r();
      int c = directions[i].c();
      if ((0 <= r && r < nRows) && (0 <= c && c < nCols) && maze[r][c] == '.')
      {
        coord_stack.push(directions[i]);
        maze[r][c] = '@';
      }
    }
  }
  return false;
}
