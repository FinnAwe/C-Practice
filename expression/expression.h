#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include <string>
#include <map>

#define FROM_RIGHT_TO_LEFT 0;
#define FROM_LEFT_TO_RIGHT 1;

class Expression
{
public:
    Expression()
    {
        m_operator_priority.insert(std::make_pair('+', 1));
        m_operator_priority.insert(std::make_pair('-', 1));
        m_operator_priority.insert(std::make_pair('*', 2));
        m_operator_priority.insert(std::make_pair('/', 3));
        m_operator_priority.insert(std::make_pair('(', 4));
        m_operator_priority.insert(std::make_pair(')', 5));

        // m_operater_direction.insert(std::make_pair('+', (FROM_LEFT_TO_RIGHT)));
        // m_operater_direction.insert(std::make_pair('-', (FROM_LEFT_TO_RIGHT)));
        // m_operater_direction.insert(std::make_pair('*', (FROM_LEFT_TO_RIGHT)));
        // m_operater_direction.insert(std::make_pair('/', (FROM_LEFT_TO_RIGHT)));
        // m_operater_direction.insert(std::make_pair('(', (FROM_LEFT_TO_RIGHT)));
        // m_operater_direction.insert(std::make_pair(')', (FROM_LEFT_TO_RIGHT)));
    };
    ~Expression(){};

    int ResolveExpression(std::string expression, int & retCode);

private:
    std::map<char, int> m_operator_priority;
    std::map<char, int> m_operater_direction;
};

#endif