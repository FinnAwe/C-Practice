#include "expression.h"
#include <stack>

using namespace std;

int Expression::ResolveExpression(std::string expression, int & retCode)
{
    string posfix_exp;
    stack<char> op_stack;
    for(auto c : expression)
    {
        if(m_operator_priority.find(c) != m_operator_priority.end())//is an operator
        {
            if(op_stack.empty())
            {
                op_stack.push(c);
            }
            else if(m_operator_priority[op_stack.top()] <= m_operator_priority[c])
            {
                op_stack.push(c);
            }
            else
            {
                while(!op_stack.empty() && m_operator_priority[op_stack.top()] > m_operator_priority[c])
                {
                    posfix_exp.push_back(op_stack.top());
                    op_stack.pop();
                }
            }
            
        }
        else//is a number
        {
            posfix_exp.push_back(c);
        }
    }

    while(!op_stack.empty())
    {
        posfix_exp.push_back(op_stack.top());
        op_stack.pop();
    }

    

}