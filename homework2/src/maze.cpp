#include <string>
#include <iostream>
#include <cassert>
#include <algorithm>

void printMaze(std::string maze[])
{
  std::cout << " ";
  int cols = maze[0].length();
  for (int i = 0; i < cols; i++)
  {

    std::cout << i % 10;
  }
  std::cout << std::endl;
  int i = 0;
  while (true)
  {
    std::cout << i % 10 << maze[i] << std::endl;
    if (maze[i].find('@') == std::string::npos && maze[i].find('.') == std::string::npos && i != 0)
    {
      break;
    }
    i++;
  }
}

void resetMaze(std::string maze[])
{
  int i = 1;
  while (true)
  {
    if (maze[i].find('@') == std::string::npos && maze[i].find('.') == std::string::npos)
    {
      break;
    }
    std::replace(maze[i].begin(), maze[i].end(), '@', '.');
    i++;
  }
}

bool pathExists(std::string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);

int main()
{
  std::string spec_maze[10] = {
      "XXXXXXXXXX",
      "X.X..X...X",
      "X....XXX.X",
      "X.XXXX.X.X",
      "X......XXX",
      "X.XX.X...X",
      "X.X..X.X.X",
      "X.X.XXXX.X",
      "X.X...X..X",
      "XXXXXXXXXX"};
  std::string maze0[3] = {
      "XXXX",
      "X..X",
      "XXXX"};
  std::string maze1[3] = {
      "XXXXX",
      "X.X.X",
      "XXXXX"};
  std::string maze2[10] = {
      "XXXXXXXXXX",
      "X...X....X",
      "XXX.X..XXX",
      "X...XXX..X",
      "X.XX.....X",
      "X.....X..X",
      "XXXXXXX..X",
      "XXX...X..X",
      "X...X....X",
      "XXXXXXXXXX"};
  assert(pathExists(spec_maze, 10, 10, 4, 6, 1, 1));

  /*
  assert(pathExists(maze0, 3, 3, 1, 1, 1, 2));

  assert(!pathExists(maze1, 3, 4, 1, 1, 1, 3));

  assert(pathExists(maze2, 10, 10, 1, 1, 8, 1));
  resetMaze(maze2);

  assert(!pathExists(maze2, 10, 10, 1, 1, 1,8));
  resetMaze(maze2);

  assert(!pathExists(maze2, 10, 10, 1, 1, 2,5));
  resetMaze(maze2);
  */
}
