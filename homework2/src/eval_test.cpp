
#include "Map.h"
#include <iostream>
#include <string>
#include <cctype>
#include <cassert>

int evaluate(std::string infix, const Map &values, std::string &postfix, int &result);

int main()
{
    char vars[] = {'a', 'e', 'i', 'o', 'u', 'y', '#'};
    int vals[] = {3, -9, 6, 2, 4, 1};
    Map m;
    for (int k = 0; vars[k] != '#'; k++)
    {
        m.insert(vars[k], vals[k]);
    }
    std::string pf;
    int answer;
    assert(evaluate("a+ e", m, pf, answer) == 0 &&
           pf == "ae+" && answer == -6);
    answer = 999;
    assert(evaluate("", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("a+", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("a i", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("ai", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("()", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("()o", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("y(o+u)", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("y(*o)", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("a+E", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("(a+(i-o)", m, pf, answer) == 1 && answer == 999);
    assert(evaluate(")a+(i-o)", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("+a", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("-a", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("a*b", m, pf, answer) == 2 &&
           pf == "ab*" && answer == 999);
    assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0 &&
           pf == "yoau-*+" && answer == -1);
    answer = 999;
    assert(evaluate("o/(y-y)", m, pf, answer) == 3 &&
           pf == "oyy-/" && answer == 999);
    assert(evaluate(" a  ", m, pf, answer) == 0 &&
           pf == "a" && answer == 3);
    assert(evaluate("((a))", m, pf, answer) == 0 &&
           pf == "a" && answer == 3);
    std::cout << "Passed all tests" << std::endl;
}
