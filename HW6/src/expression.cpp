#include "expression.h"

Complex Const::eval(std::map<std::string, Complex> const & /*value*/) const
{
    return m_number;
}

Complex Variable::eval(std::map<std::string, Complex> const & values) const
{
    return values.at(m_var);
}

Expression * Const::clone() const
{
    return new Const(*this);
}

Expression * Variable::clone() const
{
    return new Variable(*this);
}

std::ostream & operator<<(std::ostream & out, const Expression & expression)
{
    expression.print(out);
    return out;
}

void Const::print(std::ostream & out) const
{
    out << m_number;
}

void Variable::print(std::ostream & out) const
{
    out << m_var;
}
