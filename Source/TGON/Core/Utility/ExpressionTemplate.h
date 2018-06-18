/**
 * @file    ExpressionTemplate.h
 * @author  ggomdyu
 * @since   06/20/2017
 * @brief   Utility support for Expression template.
 * @see     https://en.wikipedia.org/wiki/Expression_templates
 */

#pragma once
#include <cstddef>
#include <type_traits>

namespace tgon
{

template <typename _FirstOperandType, typename _SecondOperandType>
struct AddExpression;

template <typename _FirstOperandType, typename _SecondOperandType>
struct SubtractExpression;

template <typename _FirstOperandType, typename _SecondOperandType>
struct MultiplyExpression;

template <typename _FirstOperandType, typename _SecondOperandType>
struct DivideExpression;

template <typename _DerivedExpressionType>
struct BaseExpression
{
/* @section Public operator */
public:
    constexpr const auto operator[](std::size_t index) const
    {
        return reinterpret_cast<const _DerivedExpressionType&>(*this).operator[](index);
    }

    template <typename _SecondOperandType>
    constexpr const AddExpression<_DerivedExpressionType, _SecondOperandType> operator+(const _SecondOperandType& rhs) const noexcept;

    template <typename _SecondOperandType>
    constexpr const SubtractExpression<_DerivedExpressionType, _SecondOperandType> operator-(const _SecondOperandType& rhs) const noexcept;

    template <typename _SecondOperandType>
    constexpr const MultiplyExpression<_DerivedExpressionType, _SecondOperandType> operator*(const _SecondOperandType& rhs) const noexcept;

    template <typename _SecondOperandType>
    constexpr const DivideExpression<_DerivedExpressionType, _SecondOperandType> operator/(const _SecondOperandType& rhs) const noexcept;
    
/* @section Public method */
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
struct AddExpression :
    public BaseExpression<AddExpression<_FirstOperandType, _SecondOperandType>>
{
/* @section Public type */
public:
    using FirstOperandType = _FirstOperandType;
    using SecondOperandType = _SecondOperandType;

/* @section Public constructor */
public:
    constexpr AddExpression(const _FirstOperandType& firstOperand, const _SecondOperandType& secondOperand) noexcept :
        m_firstOperand(firstOperand),
        m_secondOperand(secondOperand)
    {
    }

/* @section Public method */
public:
    constexpr const _FirstOperandType& GetFirstOperand() const noexcept
    {
        return m_firstOperand;
    }

    constexpr const _SecondOperandType& GetSecondOperand() const noexcept
    {
        return m_secondOperand;
    }

/* @section Private variable */
private:
    _FirstOperandType m_firstOperand;
    _SecondOperandType m_secondOperand;


/* @section Public operator */
public:
    constexpr auto operator[](std::size_t index) const
    {
        return m_firstOperand[index] + m_secondOperand[index];
    }
};

template <typename _FirstOperandType, typename _SecondOperandType>
struct SubtractExpression :
    public BaseExpression<SubtractExpression<_FirstOperandType, _SecondOperandType>>
{
/* @section Public type */
public:
    using FirstOperandType = _FirstOperandType;
    using SecondOperandType = _SecondOperandType;

/* @section Public constructor */
public:
    constexpr SubtractExpression(const _FirstOperandType& firstOperand, const _SecondOperandType& secondOperand) noexcept :
        m_firstOperand(firstOperand),
        m_secondOperand(secondOperand)
    {
    }

/* @section Public operator */
public:
    constexpr const auto operator[](std::size_t index) const
    {
        return m_firstOperand[index] - m_secondOperand[index];
    }

/* @section Public method */
public:
    constexpr const _FirstOperandType& GetFirstOperand() const noexcept
    {
        return m_firstOperand;
    }

    constexpr const _SecondOperandType& GetSecondOperand() const noexcept
    {
        return m_secondOperand;
    }

/* @section Private variable */
private:
    _FirstOperandType m_firstOperand;
    _SecondOperandType m_secondOperand;
};

template <typename _FirstOperandType, typename _SecondOperandType>
struct MultiplyExpression :
    public BaseExpression<MultiplyExpression<_FirstOperandType, _SecondOperandType>>
{
/* @section Public type */
public:
    using FirstOperandType = _FirstOperandType;
    using SecondOperandType = _SecondOperandType;

/* @section Public constructor */
public:
    constexpr MultiplyExpression(const _FirstOperandType& firstOperand, const _SecondOperandType& secondOperand) noexcept :
        m_firstOperand(firstOperand),
        m_secondOperand(secondOperand)
    {
    }

/* @section Public operator */
public:
    constexpr const auto operator[](std::size_t index) const
    {
        return m_firstOperand[index] * m_secondOperand[index];
    }

/* @section Public method */
public:
    constexpr const _FirstOperandType& GetFirstOperand() const noexcept
    {
        return m_firstOperand;
    }

    constexpr const _SecondOperandType& GetSecondOperand() const noexcept
    {
        return m_secondOperand;
    }

/* @section Private variable */
private:
    _FirstOperandType m_firstOperand;
    _SecondOperandType m_secondOperand;
};

template <typename _FirstOperandType, typename _SecondOperandType>
struct DivideExpression :
    public BaseExpression<DivideExpression<_FirstOperandType, _SecondOperandType>>
{
/* @section Public type */
public:
    using FirstOperandType = _FirstOperandType;
    using SecondOperandType = _SecondOperandType;

/* @section Public constructor */
public:
    constexpr DivideExpression(const _FirstOperandType& firstOperand, const _SecondOperandType& secondOperand) noexcept :
        m_firstOperand(firstOperand),
        m_secondOperand(secondOperand)
    {
    }

/* @section Public operator */
public:
    constexpr const auto operator[](std::size_t index) const
    {
        return m_firstOperand[index] / m_secondOperand[index];
    }

/* @section Public method */
public:
    constexpr const _FirstOperandType& GetFirstOperand() const noexcept
    {
        return m_firstOperand;
    }

    constexpr const _SecondOperandType& GetSecondOperand() const noexcept
    {
        return m_secondOperand;
    }

/* @section Private variable */
private:
    _FirstOperandType m_firstOperand;
    _SecondOperandType m_secondOperand;
};

template <typename _DerivedExpressionType>
template <typename _SecondOperandType>
constexpr const AddExpression<_DerivedExpressionType, _SecondOperandType> BaseExpression<_DerivedExpressionType>::operator+(const _SecondOperandType& rhs) const noexcept
{
    return {reinterpret_cast<const _DerivedExpressionType&>(*this), rhs};
}

template <typename _DerivedExpressionType>
template <typename _SecondOperandType>
constexpr const SubtractExpression<_DerivedExpressionType, _SecondOperandType> BaseExpression<_DerivedExpressionType>::operator-(const _SecondOperandType& rhs) const noexcept
{
    return {reinterpret_cast<const _DerivedExpressionType&>(*this), rhs};
}

template <typename _DerivedExpressionType>
template <typename _SecondOperandType>
constexpr const MultiplyExpression<_DerivedExpressionType, _SecondOperandType> BaseExpression<_DerivedExpressionType>::operator*(const _SecondOperandType& rhs) const noexcept
{
    return {reinterpret_cast<const _DerivedExpressionType&>(*this), rhs};
}

template <typename _DerivedExpressionType>
template <typename _SecondOperandType>
constexpr const DivideExpression<_DerivedExpressionType, _SecondOperandType> BaseExpression<_DerivedExpressionType>::operator/(const _SecondOperandType& rhs) const noexcept
{
    return {reinterpret_cast<const _DerivedExpressionType&>(*this), rhs};
}

} /* namespace tgon */
