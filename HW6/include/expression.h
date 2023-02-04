#pragma once

#include "complex.h"

#include <map>
#include <memory>
#include <ostream>
#include <string>

struct Expression
{
    virtual Complex eval(std::map<std::string, Complex> const & values = {}) const = 0;
    virtual Expression * clone() const = 0;
    virtual void print(std::ostream & out) const = 0;
    friend std::ostream & operator<<(std::ostream & out, const Expression & expression);
    virtual ~Expression() = default;
};

struct Const : public Expression
{
    Const(const Complex & number)
        : m_number(number)
    {
    }
    virtual Complex eval(std::map<std::string, Complex> const & /*value*/ = {}) const override;
    virtual Expression * clone() const override;
    virtual void print(std::ostream & out) const override;

private:
    Complex m_number;
};

struct Variable : public Expression
{
    Variable(const std::string_view & var)
        : m_var(var)
    {
    }
    virtual Complex eval(std::map<std::string, Complex> const & values = {}) const override;
    virtual Expression * clone() const override;
    virtual void print(std::ostream & out) const override;

private:
    std::string m_var;
};

template <char sign, class SubEval>
struct UnaryOperation : Expression
{
    UnaryOperation(const Expression & ex)
        : m_ex(ex.clone())
    {
    }

    virtual Complex eval(std::map<std::string, Complex> const & values = {}) const override
    {
        return subEvalObject(m_ex->eval(values));
    }

    virtual Expression * clone() const override
    {
        return new UnaryOperation(*this);
    }

private:
    virtual void print(std::ostream & out) const override
    {
        out << "(" << sign << *m_ex << ")";
    }
    const std::shared_ptr<const Expression> m_ex;
    [[no_unique_address]] SubEval subEvalObject;
};

using Conjugate = UnaryOperation<
        '~',
        std::bit_not<Complex>>;

using Negate = UnaryOperation<
        '-',
        std::negate<Complex>>;

template <char sign, class SubEval>
struct BinaryOperation : Expression
{
    BinaryOperation(const Expression & ex1, const Expression & ex2)
        : m_ex1(ex1.clone())
        , m_ex2(ex2.clone())
    {
    }

    virtual Complex eval(std::map<std::string, Complex> const & values = {}) const override
    {
        return subEvalObject(m_ex1->eval(values), m_ex2->eval(values));
    }

    virtual Expression * clone() const override
    {
        return new BinaryOperation(*this);
    }

private:
    virtual void print(std::ostream & out) const override
    {
        out << '(' << *m_ex1 << " " << sign << " " << *m_ex2 << ')';
    }
    const std::shared_ptr<const Expression> m_ex1;
    const std::shared_ptr<const Expression> m_ex2;
    [[no_unique_address]] SubEval subEvalObject;
};

using Add = BinaryOperation<
        '+',
        std::plus<Complex>>;

using Subtract = BinaryOperation<
        '-',
        std::minus<Complex>>;

using Multiply = BinaryOperation<
        '*',
        std::multiplies<Complex>>;

using Divide = BinaryOperation<
        '/',
        std::divides<Complex>>;

inline Negate operator-(const Expression & ex)
{
    return Negate(ex);
}

inline Conjugate operator~(const Expression & ex)
{
    return Conjugate(ex);
}

inline Add operator+(const Expression & ex1, const Expression & ex2)
{
    return Add(ex1, ex2);
}

inline Subtract operator-(const Expression & ex1, const Expression & ex2)
{
    return Subtract(ex1, ex2);
}

inline Multiply operator*(const Expression & ex1, const Expression & ex2)
{
    return Multiply(ex1, ex2);
}

inline Divide operator/(const Expression & ex1, const Expression & ex2)
{
    return Divide(ex1, ex2);
}
