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

template <typename _FirstOperandType, typename _SecondOperandType>
struct BaseExpression
{
public:
    constexpr BaseExpression(const _FirstOperandType& firstOperand, const _SecondOperandType& secondOperand) noexcept;

private:
    const _FirstOperandType& m_firstOperand;
    const _SecondOperandType& m_secondOperand;

public:
    auto operator[](std::size_t index) const;
};

template <typename _FirstOperandType, typename _SecondOperandType>
constexpr BaseExpression<_FirstOperandType, _SecondOperandType>::BaseExpression(const _FirstOperandType& firstOperand, const _SecondOperandType& secondOperand) noexcept :
    m_firstOperand(firstOperand),
    m_secondOperand(secondOperand)
{
}

template <typename _FirstOperandType, typename _SecondOperandType>
auto BaseExpression<_FirstOperandType, _SecondOperandType>::operator[](std::size_t index) const
{
    return m_firstOperand[index] + m_secondOperand[index];
}

template <typename _FirstOperandType, typename _SecondOperandType>
struct PlusExpression :
    public BaseExpression<_FirstOperandType, _SecondOperandType>
{
public:
    constexpr PlusExpression(const _FirstOperandType& firstOperand, const _SecondOperandType& secondOperand) noexcept;

public:
    template <typename Ty>
    constexpr PlusExpression<PlusExpression, Ty> operator+(const Ty& rhs) noexcept
    {
        return {*this, rhs};
    }
};

template <typename _FirstOperandType, typename _SecondOperandType>
constexpr PlusExpression<_FirstOperandType, _SecondOperandType>::PlusExpression(const _FirstOperandType& firstOperand, const _SecondOperandType& secondOperand) noexcept :
    BaseExpression<_FirstOperandType, _SecondOperandType>(firstOperand, secondOperand)
{
}

} /* namespace utility */
} /* namespace tgon */

