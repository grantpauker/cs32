#include <algorithm>
#include <cassert>
#include <iostream>
#include <list>
#include <vector>

std::vector<int> destroyedOnes;

class Movie
{
public:
    Movie(int r) : m_rating(r) {}
    ~Movie() { destroyedOnes.push_back(m_rating); }
    int rating() const { return m_rating; }

private:
    int m_rating;
};

//#define VECTOR
#ifdef VECTOR
/*
 * Remove the movies in v with a rating below 50 and destroy them.
 * It is acceptable if the order of the remaining movies is not
 * the same as in the original vector.
 */
void removeBad(std::vector<Movie *> &v);

#include "badvector.cpp"
std::vector<Movie *> x;
#else
/*
 * Remove the movies in li with a rating below 50 and destroy them.
 * It is acceptable if the order of the remaining movies is not
 * the same as in the original list.
 */
void removeBad(std::list<Movie *> &li);

#include "badlist.cpp"

std::list<Movie *> x;
#endif

int main()
{
    int a[8] = {85, 80, 30, 70, 20, 15, 90, 10};
    for (int k = 0; k < 8; k++)
    {
        x.push_back(new Movie(a[k]));
    }
    assert(x.size() == 8 && x.front()->rating() == 85 && x.back()->rating() == 10);
    removeBad(x);
    assert(x.size() == 4 && destroyedOnes.size() == 4);
    std::vector<int> v;
    for (auto movie : x)
    {
        v.push_back(movie->rating());
    }
    sort(v.begin(), v.end());
    int expect[4] = {70, 80, 85, 90};
    for (int k = 0; k < 4; k++)
    {
        assert(v[k] == expect[k]);
    }
    sort(destroyedOnes.begin(), destroyedOnes.end());
    int expectGone[4] = {10, 15, 20, 30};
    for (int k = 0; k < 4; k++)
    {
        assert(destroyedOnes[k] == expectGone[k]);
    }
    for (auto p = x.begin(); p != x.end(); p++)
    {
        delete *p;
    }
    std::cout << "Passed" << std::endl;
}
