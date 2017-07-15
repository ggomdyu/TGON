/**
 * @filename    Expression.h
 * @author      ggomdyu
 * @since       06/20/2016
 * @brief       Utility support for Expression template.
 * @see         https://en.wikipedia.org/wiki/Expression_templates
 */

#pragma once
#include <cstdint>

namespace tgon
{
namespace utility
{

template <typename _FirstOperandTy, typename _SecondOperandTy>
struct ArithmeticOperationBase
{
    /* @section Type definition */
public:
    using FirstOperandTy = _FirstOperandTy;
    using SecondOperandTy = _SecondOperandTy;

    /* @section Ctor/Dtor */
public:
    constexpr ArithmeticOperationBase(const _FirstOperandTy& firstOperand, const _SecondOperandTy& secondOperand) noexcept;

    /* @section Public method */
public:
    constexpr const _FirstOperandTy& GetFirstOperand() const { return m_firstOperand; }
    constexpr const _SecondOperandTy& GetSecondOperand() const { return m_secondOperand; }

    /* @section Protected variable */
protected:
    const _FirstOperandTy& m_firstOperand;
    const _SecondOperandTy& m_secondOperand;

};

template <typename _FirstOperandTy, typename _SecondOperandTy>
constexpr ArithmeticOperationBase<_FirstOperandTy, _SecondOperandTy>::ArithmeticOperationBase(const _FirstOperandTy& firstOperand, const _SecondOperandTy& secondOperand) noexcept :
    m_firstOperand(firstOperand),
    m_secondOperand(secondOperand)
{
}

template <typename _FirstOperandTy, typename _SecondOperandTy>
struct Addition :
    public ArithmeticOperationBase<_FirstOperandTy,_SecondOperandTy>
{
/* @section Ctor/Dtor */
public:
    using ArithmeticOperationBase<_FirstOperandTy,_SecondOperandTy>::ArithmeticOperationBase;

/* @section Protected variable */
protected:
    using ArithmeticOperationBase<_FirstOperandTy,_SecondOperandTy>::m_firstOperand;
    using ArithmeticOperationBase<_FirstOperandTy,_SecondOperandTy>::m_secondOperand;

/* @section Operator */
public:
    auto operator[](std::size_t index) const -> decltype(m_firstOperand[index] + m_secondOperand[index]);
};

template <typename _FirstOperandTy, typename _SecondOperandTy>
auto Addition<_FirstOperandTy, _SecondOperandTy>::operator[](std::size_t index) const -> decltype(m_firstOperand[index] + m_secondOperand[index])
{
    return m_firstOperand[index] + m_secondOperand[index];
}

template <typename _FirstOperandTy, typename _SecondOperandTy>
struct Subtraction :
    public ArithmeticOperationBase<_FirstOperandTy,_SecondOperandTy>
{
/* @section Ctor/Dtor */
public:
    using ArithmeticOperationBase<_FirstOperandTy,_SecondOperandTy>::ArithmeticOperationBase;

/* @section Protected variable */
protected:
    using ArithmeticOperationBase<_FirstOperandTy,_SecondOperandTy>::m_firstOperand;
    using ArithmeticOperationBase<_FirstOperandTy,_SecondOperandTy>::m_secondOperand;

/* @section Operator */
public:
    auto operator[](std::size_t index) const -> decltype(m_firstOperand[index] - m_secondOperand[index]);
};

template <typename _FirstOperandTy, typename _SecondOperandTy>
auto Subtraction<_FirstOperandTy, _SecondOperandTy>::operator[](std::size_t index) const -> decltype(m_firstOperand[index] - m_secondOperand[index])
{
    return m_firstOperand[index] - m_secondOperand[index];
}

template <typename _ExpressionPolicyType>
struct ExpressionTemplate :
    public _ExpressionPolicyType
{
/* @section Type definition */
public:
    using _ExpressionPolicyType::_ExpressionPolicyType;

/* @section Operator */
public:
    auto operator[](std::size_t index) const -> decltype(_ExpressionPolicyType::operator[](index));

    template <typename SecondOperandTy2>
    constexpr const ExpressionTemplate<Addition<_ExpressionPolicyType, typename _ExpressionPolicyType::SecondOperandTy>> operator+(const SecondOperandTy2& rhs) const noexcept;

    template <typename SecondOperandTy2>
    constexpr const ExpressionTemplate<Subtraction<_ExpressionPolicyType, typename _ExpressionPolicyType::SecondOperandTy>> operator-(const SecondOperandTy2& rhs) const noexcept;
};

template <typename _ExpressionPolicyType>
auto ExpressionTemplate<_ExpressionPolicyType>::operator[](std::size_t index) const -> decltype(_ExpressionPolicyType::operator[](index))
{
    return _ExpressionPolicyType::operator[](index);
}

template <typename _ExpressionPolicyType>
template <typename SecondOperandTy2>
constexpr const ExpressionTemplate<Addition<_ExpressionPolicyType, typename _ExpressionPolicyType::SecondOperandTy>> ExpressionTemplate<_ExpressionPolicyType>::operator+(const SecondOperandTy2& rhs) const noexcept
{
    return {*this, rhs};
}

template <typename _ExpressionPolicyType>
template <typename SecondOperandTy2>
constexpr const ExpressionTemplate<Subtraction<_ExpressionPolicyType, typename _ExpressionPolicyType::SecondOperandTy>> ExpressionTemplate<_ExpressionPolicyType>::operator-(const SecondOperandTy2& rhs) const noexcept
{
    return {*this, rhs};
}

} /* namespace utility */
} /* namespace tgon */
