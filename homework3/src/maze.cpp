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
  if (sr == er && sc == ec)
  {
    return true;
  }
  maze[sr][sc] = '@';
  Coord west(sr, sc - 1);
  Coord south(sr + 1, sc);
  Coord east(sr, sc + 1);
  Coord north(sr - 1, sc);
  Coord directions[4] = {west, south, east, north};
  for (int i = 0; i < 4; i++)
  {
    int r = directions[i].r();
    int c = directions[i].c();
    if ((0 <= r && r < nRows) && (0 <= c && c < nCols) && maze[r][c] == '.' && pathExists(maze, nRows, nCols, r, c, er, ec)){
        return true;
    }
  }
  return false;
}
