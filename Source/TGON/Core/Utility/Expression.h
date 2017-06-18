/**
 * @filename    Expression.h
 * @author      ggomdyu
 * @since       06/20/2016
 * @brief       Utility support for Expression template.
 * @see         https://en.wikipedia.org/wiki/Expression_templates
 */

#pragma once
#include <cstddef>
#include <type_traits>

namespace tgon
{
namespace utility
{

template <typename ExpressionTy>
struct BaseExpression;

template <template <typename, typename> class ExpressionTy, typename FirstOperandTy, typename SecondOperandTy>
struct BaseExpression<ExpressionTy<FirstOperandTy, SecondOperandTy>>
{
/**
 * @section Private variable
 */
private:
    const FirstOperandTy& m_firstOperand;
    const SecondOperandTy& m_secondOperand;

/**
 * @section Ctor/Dtor
 */
public:
    constexpr BaseExpression(const FirstOperandTy& firstOperand, const SecondOperandTy& secondOperand) noexcept;

/**
 * @section Type definition
 */
public:
    using ResultTy = decltype(m_firstOperand[0] + m_secondOperand[0]);

/**
 * @section Operator
 */
public:
    ResultTy operator[](std::size_t index) const;
};

template <template <typename, typename> class ExpressionTy, typename FirstOperandTy, typename SecondOperandTy>
constexpr BaseExpression<ExpressionTy<FirstOperandTy, SecondOperandTy>>::BaseExpression(const FirstOperandTy& firstOperand, const SecondOperandTy& secondOperand) noexcept :
    m_firstOperand(firstOperand),
    m_secondOperand(secondOperand)
{
}

template <template <typename, typename> class ExpressionTy, typename FirstOperandTy, typename SecondOperandTy>
typename BaseExpression<ExpressionTy<FirstOperandTy, SecondOperandTy>>::ResultTy BaseExpression<ExpressionTy<FirstOperandTy, SecondOperandTy>>::operator[](std::size_t index) const
{
    return m_firstOperand[index] + m_secondOperand[index];
}

template <typename FirstOperandTy, typename SecondOperandTy>
struct PlusExpression :
    public BaseExpression<PlusExpression<FirstOperandTy, SecondOperandTy>>
{
/**
 * @section Ctor/Dtor
 */
public:
    constexpr PlusExpression(const FirstOperandTy& firstOperand, const SecondOperandTy& secondOperand) noexcept;

/**
 * @section Operator
 */
public:
    template <typename Ty>
    constexpr PlusExpression<PlusExpression, Ty> operator+(const Ty& rhs) noexcept
    {
        return {*this, rhs};
    }
};

template <typename FirstOperandTy, typename SecondOperandTy>
constexpr PlusExpression<FirstOperandTy, SecondOperandTy>::PlusExpression(const FirstOperandTy& firstOperand, const SecondOperandTy& secondOperand) noexcept :
    BaseExpression<PlusExpression<FirstOperandTy, SecondOperandTy>>(firstOperand, secondOperand)
{
}

} /* namespace utility */
} /* namespace tgon */
