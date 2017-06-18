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
 * @section Type definition
 */
public:
    using ResultTy = int;//decltype(FirstOperandTy{}[0] + SecondOperandTy{}[0]);

/**
 * @section Ctor/Dtor
 */
public:
    constexpr BaseExpression() = default;

    constexpr BaseExpression(const FirstOperandTy& firstOperand, const SecondOperandTy& secondOperand) noexcept :
        m_firstOperand(firstOperand),
        m_secondOperand(secondOperand)
    {
    }

    template <typename Ty>
    ExpressionTy<BaseExpression, Ty> operator+(const Ty& rhs)
    {
        return {*this, rhs  };
    }

    constexpr const FirstOperandTy& GetFirstOperand() const noexcept
    {
        return m_firstOperand;
    }

    constexpr const SecondOperandTy& GetSecondOperand() const noexcept
    {
        return m_secondOperand;
    }

    ResultTy operator[](std::size_t index) const
    {
        return (*(ExpressionTy<FirstOperandTy, SecondOperandTy>*)(this))[index];
    }

private:
    const FirstOperandTy& m_firstOperand;
    const SecondOperandTy& m_secondOperand;
};

template <typename FirstOperandTy, typename SecondOperandTy>
struct PlusExpression :
    public BaseExpression<PlusExpression<FirstOperandTy, SecondOperandTy>>
{
/**
 * @section Type definition
 */
public:
    using ResultTy = int;//decltype(FirstOperandTy{}[0] + SecondOperandTy{}[0]);

/**
 * @section Ctor/Dtor
 */
public:
    constexpr PlusExpression(const FirstOperandTy& firstOperand, const SecondOperandTy& secondOperand) noexcept :
        BaseExpression<PlusExpression<FirstOperandTy, SecondOperandTy>>(firstOperand, secondOperand)
    {
    }
    
    ResultTy operator[](std::size_t index) const
    {
        return this->GetFirstOperand()[index] + this->GetSecondOperand()[index];
    }
};

} /* namespace utility */
} /* namespace tgon */
