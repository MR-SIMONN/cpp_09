#include "RPN.hpp"

void calculat_RPN(const std::string &expression)
{
    std::stack<int> stack;

    for (size_t i = 0; i < expression.size(); i++)
    {
        char c = expression[i];

        if (c == ' ')
            continue;
        
        if (std::isdigit(c))
            stack.push(c - '0');

        else if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            if (stack.size() < 2)
            {
                std::cerr << "Error" << std::endl;
                return;
            }

            int b = stack.top();
            stack.pop();
            int a = stack.top();
            stack.pop();

            if (c == '+')
                stack.push(a + b);
            else if (c == '-')
                stack.push(a - b);
            else if (c == '*')
                stack.push(a * b);
            else if (c == '/')
            {
                if (b == 0)
                {
                    std::cerr << "Error" << std::endl;
                    return;
                }
                stack.push(a / b);
            }
        }
        else
        {
            std::cerr << "Error" << std::endl; 
            return;
        }
    }

    if (stack.size() != 1)
    {
        std::cerr << "Error" << std::endl;
        return;
    }

    std::cout << stack.top() << std::endl;
}