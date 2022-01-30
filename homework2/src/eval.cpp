
#include "Map.h"
#include <string>
#include <cctype>
#include <stack>

#define IS_OPERATOR(c) ((c) == '+' || (c) == '-' || (c) == '*' || (c) == '/')

int precedence(char oper)
{
    switch (oper)
    {
    case '*':
    case '/':
        return 0;
    case '+':
    case '-':
        return 1;
    }
    return -1;
}

bool toPostfix(std::string infix, std::string &postfix)
{
    postfix = "";
    std::stack<char> operators;
    char prev_c = '(';
    for (auto c : infix)
    {
        if (islower(c))
        {
            if (prev_c == ')' || islower(prev_c))
            {
                return false;
            }
            postfix += c;
        }
        else if (c == '(')
        {
            if (prev_c == ')' || islower(prev_c))
            {
                return false;
            }
            operators.push(c);
        }
        else if (c == ')')
        {
            if (prev_c == '(' || IS_OPERATOR(prev_c))
            {
                return false;
            }
            while (!operators.empty() && operators.top() != '(')
            {
                postfix += operators.top();
                operators.pop();
            }
            if (operators.empty())
            {
                return false;
            }
            operators.pop();
        }
        else if (IS_OPERATOR(c))
        {
            if (prev_c == '(')
            {
                return false;
            }
            while (!operators.empty() && operators.top() != '(' && precedence(c) >= precedence(operators.top()))
            {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(c);
        }
        else if (c == ' ')
        {
            continue;
        }
        else
        {
            return false;
        }
        prev_c = c;
    }
    if (prev_c == '(' || IS_OPERATOR(prev_c))
    {
        return false;
    }
    while (!operators.empty())
    {
        if (operators.top() == '(' || operators.top() == ')')
        {
            return false;
        }
        postfix += operators.top();
        operators.pop();
    }
    return true;
}

/*
 * Evaluates an integer arithmetic expression.
 * If infix is a syntactically valid infix integer expression whose
 * only operands are single lower case letters (whether or not they
 * appear in the values map), then postfix is set to the postfix
 * form of the expression; otherwise postfix may or may not be
 * changed, result is unchanged, and the function returns 1.  If
 * infix is syntactically valid but contains at least one lower
 * case letter operand that does not appear in the values map, then
 * result is unchanged and the function returns 2.  If infix is
 * syntactically valid and all its lower case operand letters
 * appear in the values map, then if evaluating the expression
 * (using for each letter in the expression the value in the map
 * that corresponds to it) attempts to divide by zero, then result
 * is unchanged and the function returns 3; otherwise, result is
 * set to the value of the expression and the function returns 0.
 */
int evaluate(std::string infix, const Map &values, std::string &postfix, int &result)
{
    if (!toPostfix(infix, postfix))
    {
        return 1;
    }
    std::stack<int> operands;
    for (auto c : postfix)
    {
        if (islower(c))
        {
            int operand;
            if (!values.get(c, operand))
            {
                return 2;
            }
            operands.push(operand);
        }
        else
        {
            int operand2 = operands.top();
            operands.pop();
            int operand1 = operands.top();
            operands.pop();
            int result;
            switch (c)
            {
            case '+':
                result = operand1 + operand2;
                break;
            case '-':
                result = operand1 - operand2;
                break;
            case '*':
                result = operand1 * operand2;
                break;
            case '/':
                if (operand2 == 0)
                {
                    return 3;
                }
                result = operand1 / operand2;
                break;
            }
            operands.push(result);
        }
    }
    result = operands.top();
    return 0;
}
