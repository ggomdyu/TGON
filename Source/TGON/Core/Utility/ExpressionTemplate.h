/**
 * @filename    ExpressionTemplate.h
 * @author      ggomdyu
 * @since       06/20/2017
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
/* @section Public type */
public:
    using FirstOperandType = _FirstOperandType;
    using SecondOperandType = _SecondOperandType;

/* @section Public constructor */
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
/* @section Public constructor */
public:
    using ArithmeticOperationBase<_FirstOperandType,_SecondOperandType>::ArithmeticOperationBase;

/* @section Protected variable */
protected:
    using ArithmeticOperationBase<_FirstOperandType,_SecondOperandType>::m_firstOperand;
    using ArithmeticOperationBase<_FirstOperandType,_SecondOperandType>::m_secondOperand;

/* @section Public operator */
public:
    constexpr auto operator[](std::size_t index) const -> decltype(m_firstOperand[index] + m_secondOperand[index]);
};

template <typename _FirstOperandType, typename _SecondOperandType>
constexpr auto Addition<_FirstOperandType, _SecondOperandType>::operator[](std::size_t index) const -> decltype(m_firstOperand[index] + m_secondOperand[index])
{
    return m_firstOperand[index] + m_secondOperand[index];
}


template <typename _FirstOperandType, typename _SecondOperandType>
struct Subtraction :
    public ArithmeticOperationBase<_FirstOperandType,_SecondOperandType>
{
/* @section Public constructor */
public:
    using ArithmeticOperationBase<_FirstOperandType,_SecondOperandType>::ArithmeticOperationBase;

/* @section Protected variable */
protected:
    using ArithmeticOperationBase<_FirstOperandType,_SecondOperandType>::m_firstOperand;
    using ArithmeticOperationBase<_FirstOperandType,_SecondOperandType>::m_secondOperand;

/* @section Public operator */
public:
    constexpr auto operator[](std::size_t index) const -> decltype(m_firstOperand[index] - m_secondOperand[index]);
};

template <typename _FirstOperandType, typename _SecondOperandType>
constexpr auto Subtraction<_FirstOperandType, _SecondOperandType>::operator[](std::size_t index) const -> decltype(m_firstOperand[index] - m_secondOperand[index])
{
    return m_firstOperand[index] - m_secondOperand[index];
}


template <typename _FirstOperandType, typename _SecondOperandType>
struct Multiplication :
    public ArithmeticOperationBase<_FirstOperandType,_SecondOperandType>
{
/* @section Public constructor */
public:
    using ArithmeticOperationBase<_FirstOperandType,_SecondOperandType>::ArithmeticOperationBase;

/* @section Protected variable */
protected:
    using ArithmeticOperationBase<_FirstOperandType,_SecondOperandType>::m_firstOperand;
    using ArithmeticOperationBase<_FirstOperandType,_SecondOperandType>::m_secondOperand;

/* @section Public operator */
public:
    constexpr auto operator[](std::size_t index) const -> decltype(m_firstOperand[index] * m_secondOperand[index]);
};

template <typename _FirstOperandType, typename _SecondOperandType>
constexpr auto Multiplication<_FirstOperandType, _SecondOperandType>::operator[](std::size_t index) const -> decltype(m_firstOperand[index] * m_secondOperand[index])
{
    return m_firstOperand[index] * m_secondOperand[index];
}


template <typename _FirstOperandType, typename _SecondOperandType>
struct Division :
    public ArithmeticOperationBase<_FirstOperandType,_SecondOperandType>
{
/* @section Public constructor */
public:
    using ArithmeticOperationBase<_FirstOperandType,_SecondOperandType>::ArithmeticOperationBase;

/* @section Protected variable */
protected:
    using ArithmeticOperationBase<_FirstOperandType,_SecondOperandType>::m_firstOperand;
    using ArithmeticOperationBase<_FirstOperandType,_SecondOperandType>::m_secondOperand;

/* @section Public operator */
public:
    constexpr auto operator[](std::size_t index) const -> decltype(m_firstOperand[index] / m_secondOperand[index]);
};

template <typename _FirstOperandType, typename _SecondOperandType>
constexpr auto Division<_FirstOperandType, _SecondOperandType>::operator[](std::size_t index) const -> decltype(m_firstOperand[index] / m_secondOperand[index])
{
    return m_firstOperand[index] / m_secondOperand[index];
}


template <typename _ExpressionPolicyType>
struct ExpressionTemplate :
    public _ExpressionPolicyType
{
/* @section Public type */
public:
    using _ExpressionPolicyType::_ExpressionPolicyType;

/* @section Public operator */
public:
#ifndef _MSC_VER
    constexpr auto operator[](std::size_t index) const -> decltype(_ExpressionPolicyType::operator[](index));
#else
    constexpr auto operator[](std::size_t index) const;
#endif

    template <typename _SecondOperandType2>
    constexpr const ExpressionTemplate<Addition<_ExpressionPolicyType, typename _ExpressionPolicyType::SecondOperandType>> operator+(const _SecondOperandType2& rhs) const noexcept;

    template <typename _SecondOperandType2>
    constexpr const ExpressionTemplate<Subtraction<_ExpressionPolicyType, typename _ExpressionPolicyType::SecondOperandType>> operator-(const _SecondOperandType2& rhs) const noexcept;

    template <typename _SecondOperandType2>
    constexpr const ExpressionTemplate<Multiplication<_ExpressionPolicyType, typename _ExpressionPolicyType::SecondOperandType>> operator*(const _SecondOperandType2& rhs) const noexcept;
};

#ifndef _MSC_VER
template <typename _ExpressionPolicyType>
constexpr auto ExpressionTemplate<_ExpressionPolicyType>::operator[](std::size_t index) const -> decltype(_ExpressionPolicyType::operator[](index))
{
    return _ExpressionPolicyType::operator[](index);
}
#else
template <typename _ExpressionPolicyType>
constexpr auto ExpressionTemplate<_ExpressionPolicyType>::operator[](std::size_t index) const
{
    return _ExpressionPolicyType::operator[](index);
}
#endif

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
