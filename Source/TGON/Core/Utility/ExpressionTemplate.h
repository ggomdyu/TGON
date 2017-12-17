/**
 * @filename    Expression.h
 * @author      ggomdyu
 * @since       06/20/2017
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

template <typename _DerivedExpressionType>
struct BaseExpression
{
public:
    constexpr const auto operator[](std::size_t index) const
    {
        return reinterpret_cast<const _DerivedExpressionType&>(*this).operator[](index);
    }

public:
    constexpr const auto& GetFirstOperand() const noexcept
    {
        return reinterpret_cast<const _DerivedExpressionType&>(*this).GetFirstOperand();
    }

    constexpr const auto& GetSecondOperand() const noexcept
    {
        return reinterpret_cast<const _DerivedExpressionType&>(*this).GetSecondOperand();
    }
};

template <typename _FirstOperandType, typename _SecondOperandType>
struct PlusExpression :
    public BaseExpression<PlusExpression<_FirstOperandType, _SecondOperandType>>
{
public:
    using FirstOperandType = _FirstOperandType;
    using SecondOperandType = _SecondOperandType;

public:
    constexpr PlusExpression(const _FirstOperandType& firstOperand, const _SecondOperandType& secondOperand) noexcept;

    constexpr const auto operator[](std::size_t index) const
    {
        return m_firstOperand[index] + m_secondOperand[index];
    }


public:
    template <typename Ty>
    constexpr PlusExpression<PlusExpression, Ty> operator+(const Ty& rhs) noexcept
    {
        return {*this, rhs};
    }

public:
    constexpr const _FirstOperandType& GetFirstOperand() const noexcept
    {
        return m_firstOperand;
    }

    constexpr const _SecondOperandType& GetSecondOperand() const noexcept
    {
        return m_secondOperand;
    }

private:
    _FirstOperandType m_firstOperand;
    _SecondOperandType m_secondOperand;
};

template <typename _FirstOperandType, typename _SecondOperandType>
constexpr PlusExpression<_FirstOperandType, _SecondOperandType>::PlusExpression(const _FirstOperandType& firstOperand, const _SecondOperandType& secondOperand) noexcept :
    m_firstOperand(firstOperand),
    m_secondOperand(secondOperand)
{
}

} /* namespace utility */
} /* namespace tgon */
