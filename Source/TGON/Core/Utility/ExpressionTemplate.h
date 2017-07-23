/**
 * @filename    ExpressionTemplate.h
 * @author      ggomdyu
 * @since       06/20/2016
 * @brief       Utility support for Expression template.
 * @see         https://en.wikipedia.org/wiki/Expression_templates
 */

#pragma once
#include <cstddef>

namespace tgon
{
namespace utility
{

template <typename _FirstOperandType, typename _SecondOperandType>
struct ArithmeticOperationBase
{
/* @section Type definition */
public:
    using FirstOperandType = _FirstOperandType;
    using SecondOperandType = _SecondOperandType;

/* @section Ctor/Dtor */
public:
    constexpr ArithmeticOperationBase(const _FirstOperandType& firstOperand, const _SecondOperandType& secondOperand) noexcept;

/* @section Public method */
public:
    constexpr const _FirstOperandType& GetFirstOperand() const noexcept;
    constexpr const _SecondOperandType& GetSecondOperand() const noexcept;

/* @section Protected variable */
protected:
    const _FirstOperandType& m_firstOperand;
    const _SecondOperandType& m_secondOperand;
};

template <typename _FirstOperandType, typename _SecondOperandType>
constexpr ArithmeticOperationBase<_FirstOperandType, _SecondOperandType>::ArithmeticOperationBase(const _FirstOperandType& firstOperand, const _SecondOperandType& secondOperand) noexcept :
    m_firstOperand(firstOperand),
    m_secondOperand(secondOperand)
{
}

template <typename _FirstOperandType, typename _SecondOperandType>
constexpr const _FirstOperandType& ArithmeticOperationBase<_FirstOperandType, _SecondOperandType>::GetFirstOperand() const noexcept
{
    return m_firstOperand;
}

template <typename _FirstOperandType, typename _SecondOperandType>
constexpr const _SecondOperandType& ArithmeticOperationBase<_FirstOperandType, _SecondOperandType>::GetSecondOperand() const noexcept
{
    return m_secondOperand;
}


template <typename _FirstOperandType, typename _SecondOperandType>
struct Addition :
    public ArithmeticOperationBase<_FirstOperandType,_SecondOperandType>
{
/* @section Ctor/Dtor */
public:
    using ArithmeticOperationBase<_FirstOperandType,_SecondOperandType>::ArithmeticOperationBase;

/* @section Protected variable */
protected:
    using ArithmeticOperationBase<_FirstOperandType,_SecondOperandType>::m_firstOperand;
    using ArithmeticOperationBase<_FirstOperandType,_SecondOperandType>::m_secondOperand;

/* @section Operator */
public:
    auto operator[](std::size_t index) const -> decltype(m_firstOperand[index] + m_secondOperand[index]);
};

template <typename _FirstOperandType, typename _SecondOperandType>
auto Addition<_FirstOperandType, _SecondOperandType>::operator[](std::size_t index) const -> decltype(m_firstOperand[index] + m_secondOperand[index])
{
    return m_firstOperand[index] + m_secondOperand[index];
}

template <typename _FirstOperandType, typename _SecondOperandType>
struct Subtraction :
    public ArithmeticOperationBase<_FirstOperandType,_SecondOperandType>
{
/* @section Ctor/Dtor */
public:
    using ArithmeticOperationBase<_FirstOperandType,_SecondOperandType>::ArithmeticOperationBase;

/* @section Protected variable */
protected:
    using ArithmeticOperationBase<_FirstOperandType,_SecondOperandType>::m_firstOperand;
    using ArithmeticOperationBase<_FirstOperandType,_SecondOperandType>::m_secondOperand;

/* @section Operator */
public:
    auto operator[](std::size_t index) const -> decltype(m_firstOperand[index] - m_secondOperand[index]);
};

template <typename _FirstOperandType, typename _SecondOperandType>
auto Subtraction<_FirstOperandType, _SecondOperandType>::operator[](std::size_t index) const -> decltype(m_firstOperand[index] - m_secondOperand[index])
{
    return m_firstOperand[index] - m_secondOperand[index];
}

template <typename _FirstOperandType, typename _SecondOperandType>
struct Multiplication :
    public ArithmeticOperationBase<_FirstOperandType,_SecondOperandType>
{
/* @section Ctor/Dtor */
public:
    using ArithmeticOperationBase<_FirstOperandType,_SecondOperandType>::ArithmeticOperationBase;

/* @section Protected variable */
protected:
    using ArithmeticOperationBase<_FirstOperandType,_SecondOperandType>::m_firstOperand;
    using ArithmeticOperationBase<_FirstOperandType,_SecondOperandType>::m_secondOperand;

/* @section Operator */
public:
    auto operator[](std::size_t index) const -> decltype(m_firstOperand[index] * m_secondOperand[index]);
};

template <typename _FirstOperandType, typename _SecondOperandType>
auto Multiplication<_FirstOperandType, _SecondOperandType>::operator[](std::size_t index) const -> decltype(m_firstOperand[index] * m_secondOperand[index])
{
    return m_firstOperand[index] * m_secondOperand[index];
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

    template <typename _SecondOperandType2>
    constexpr const ExpressionTemplate<Addition<_ExpressionPolicyType, typename _ExpressionPolicyType::SecondOperandType>> operator+(const _SecondOperandType2& rhs) const noexcept;

    template <typename _SecondOperandType2>
    constexpr const ExpressionTemplate<Subtraction<_ExpressionPolicyType, typename _ExpressionPolicyType::SecondOperandType>> operator-(const _SecondOperandType2& rhs) const noexcept;

    template <typename _SecondOperandType2>
    constexpr const ExpressionTemplate<Multiplication<_ExpressionPolicyType, typename _ExpressionPolicyType::SecondOperandType>> operator*(const _SecondOperandType2& rhs) const noexcept;
};

template <typename _ExpressionPolicyType>
auto ExpressionTemplate<_ExpressionPolicyType>::operator[](std::size_t index) const -> decltype(_ExpressionPolicyType::operator[](index))
{
    return _ExpressionPolicyType::operator[](index);
}

template <typename _ExpressionPolicyType>
template <typename _SecondOperandType2>
constexpr const ExpressionTemplate<Addition<_ExpressionPolicyType, typename _ExpressionPolicyType::SecondOperandType>> ExpressionTemplate<_ExpressionPolicyType>::operator+(const _SecondOperandType2& rhs) const noexcept
{
    return {*this, rhs};
}

template <typename _ExpressionPolicyType>
template <typename _SecondOperandType2>
constexpr const ExpressionTemplate<Subtraction<_ExpressionPolicyType, typename _ExpressionPolicyType::SecondOperandType>> ExpressionTemplate<_ExpressionPolicyType>::operator-(const _SecondOperandType2& rhs) const noexcept
{
    return {*this, rhs};
}

template <typename _ExpressionPolicyType>
template <typename _SecondOperandType2>
constexpr const ExpressionTemplate<Multiplication<_ExpressionPolicyType, typename _ExpressionPolicyType::SecondOperandType>> ExpressionTemplate<_ExpressionPolicyType>::operator*(const _SecondOperandType2& rhs) const noexcept
{
    return {*this, rhs};
}

} /* namespace utility */
} /* namespace tgon */
