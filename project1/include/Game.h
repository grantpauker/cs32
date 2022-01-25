#ifndef GAME_H
#define GAME_H
class Mesa;

int decodeDirection(char dir); // TODO move

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nGarks);
    ~Game();

    // Mutators
    void play();

private:
    Mesa *m_mesa;
};
#endif