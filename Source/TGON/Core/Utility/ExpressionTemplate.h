/**
 * @filename    ExpressionTemplate.h
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
struct PlusExpression;

template <typename _FirstOperandType, typename _SecondOperandType>
struct MinusExpression;

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
    constexpr const PlusExpression<_DerivedExpressionType, _SecondOperandType> operator+(const _SecondOperandType& rhs) const noexcept;

    template <typename _SecondOperandType>
    constexpr const MinusExpression<_DerivedExpressionType, _SecondOperandType> operator-(const _SecondOperandType& rhs) const noexcept;

    template <typename _SecondOperandType>
    constexpr const MultiplyExpression<_DerivedExpressionType, _SecondOperandType> operator*(const _SecondOperandType& rhs) const noexcept;

    template <typename _SecondOperandType>
    constexpr const DivideExpression<_DerivedExpressionType, _SecondOperandType> operator/(const _SecondOperandType& rhs) const noexcept;
    
/* @section Public method */
public:
    constexpr const auto& GetFirstOperand() const noexcept;
    constexpr const auto& GetSecondOperand() const noexcept;
};

template <typename _DerivedExpressionType>
constexpr const auto& BaseExpression<_DerivedExpressionType>::GetFirstOperand() const noexcept
{
    return reinterpret_cast<const _DerivedExpressionType&>(*this).GetFirstOperand();
}

template <typename _DerivedExpressionType>
constexpr const auto& BaseExpression<_DerivedExpressionType>::GetSecondOperand() const noexcept
{
    return reinterpret_cast<const _DerivedExpressionType&>(*this).GetSecondOperand();
}

template <typename _FirstOperandType, typename _SecondOperandType>
struct PlusExpression :
    public BaseExpression<PlusExpression<_FirstOperandType, _SecondOperandType>>
{
/* @section Public type */
public:
    using FirstOperandType = _FirstOperandType;
    using SecondOperandType = _SecondOperandType;

/* @section Public constructor */
public:
    constexpr PlusExpression(const _FirstOperandType& firstOperand, const _SecondOperandType& secondOperand) noexcept;

/* @section Public operator */
public:
    constexpr const auto operator[](std::size_t index) const;

/* @section Public method */
public:
    constexpr const _FirstOperandType& GetFirstOperand() const noexcept;
    constexpr const _SecondOperandType& GetSecondOperand() const noexcept;

/* @section Private variable */
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

template <typename _FirstOperandType, typename _SecondOperandType>
constexpr const auto PlusExpression<_FirstOperandType, _SecondOperandType>::operator[](std::size_t index) const
{
    return m_firstOperand[index] + m_secondOperand[index];
}

template <typename _FirstOperandType, typename _SecondOperandType>
constexpr const _FirstOperandType& PlusExpression<_FirstOperandType, _SecondOperandType>::GetFirstOperand() const noexcept
{
    return m_firstOperand;
}

template <typename _FirstOperandType, typename _SecondOperandType>
constexpr const _SecondOperandType& PlusExpression<_FirstOperandType, _SecondOperandType>::GetSecondOperand() const noexcept
{
    return m_secondOperand;
}

template <typename _FirstOperandType, typename _SecondOperandType>
struct MinusExpression :
    public BaseExpression<MinusExpression<_FirstOperandType, _SecondOperandType>>
{
/* @section Public type */
public:
    using FirstOperandType = _FirstOperandType;
    using SecondOperandType = _SecondOperandType;

/* @section Public constructor */
public:
    constexpr MinusExpression(const _FirstOperandType& firstOperand, const _SecondOperandType& secondOperand) noexcept;

/* @section Public operator */
public:
    constexpr const auto operator[](std::size_t index) const;

/* @section Public method */
public:
    constexpr const _FirstOperandType& GetFirstOperand() const noexcept;
    constexpr const _SecondOperandType& GetSecondOperand() const noexcept;

/* @section Private variable */
private:
    _FirstOperandType m_firstOperand;
    _SecondOperandType m_secondOperand;
};

template <typename _FirstOperandType, typename _SecondOperandType>
constexpr const auto MinusExpression<_FirstOperandType, _SecondOperandType>::operator[](std::size_t index) const
{
    return m_firstOperand[index] - m_secondOperand[index];
}

template <typename _FirstOperandType, typename _SecondOperandType>
constexpr MinusExpression<_FirstOperandType, _SecondOperandType>::MinusExpression(const _FirstOperandType& firstOperand, const _SecondOperandType& secondOperand) noexcept :
    m_firstOperand(firstOperand),
    m_secondOperand(secondOperand)
{
}

template <typename _FirstOperandType, typename _SecondOperandType>
constexpr const _FirstOperandType& MinusExpression<_FirstOperandType, _SecondOperandType>::GetFirstOperand() const noexcept
{
    return m_firstOperand;
}

template <typename _FirstOperandType, typename _SecondOperandType>
constexpr const _SecondOperandType& MinusExpression<_FirstOperandType, _SecondOperandType>::GetSecondOperand() const noexcept
{
    return m_secondOperand;
}

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
    constexpr MultiplyExpression(const _FirstOperandType& firstOperand, const _SecondOperandType& secondOperand) noexcept;

/* @section Public operator */
public:
    constexpr const auto operator[](std::size_t index) const;

/* @section Public method */
public:
    constexpr const _FirstOperandType& GetFirstOperand() const noexcept;
    constexpr const _SecondOperandType& GetSecondOperand() const noexcept;

/* @section Private variable */
private:
    _FirstOperandType m_firstOperand;
    _SecondOperandType m_secondOperand;
};

template <typename _FirstOperandType, typename _SecondOperandType>
constexpr MultiplyExpression<_FirstOperandType, _SecondOperandType>::MultiplyExpression(const _FirstOperandType& firstOperand, const _SecondOperandType& secondOperand) noexcept :
    m_firstOperand(firstOperand),
    m_secondOperand(secondOperand)
{
}

template <typename _FirstOperandType, typename _SecondOperandType>
constexpr const auto MultiplyExpression<_FirstOperandType, _SecondOperandType>::operator[](std::size_t index) const
{
    return m_firstOperand[index] * m_secondOperand[index];
}

template <typename _FirstOperandType, typename _SecondOperandType>
constexpr const _FirstOperandType& MultiplyExpression<_FirstOperandType, _SecondOperandType>::GetFirstOperand() const noexcept
{
    return m_firstOperand;
}

template <typename _FirstOperandType, typename _SecondOperandType>
constexpr const _SecondOperandType& MultiplyExpression<_FirstOperandType, _SecondOperandType>::GetSecondOperand() const noexcept
{
    return m_secondOperand;
}

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
    constexpr DivideExpression(const _FirstOperandType& firstOperand, const _SecondOperandType& secondOperand) noexcept;

/* @section Public operator */
public:
    constexpr const auto operator[](std::size_t index) const;

/* @section Public method */
public:
    constexpr const _FirstOperandType& GetFirstOperand() const noexcept;
    constexpr const _SecondOperandType& GetSecondOperand() const noexcept;

/* @section Private variable */
private:
    _FirstOperandType m_firstOperand;
    _SecondOperandType m_secondOperand;
};

template <typename _FirstOperandType, typename _SecondOperandType>
constexpr DivideExpression<_FirstOperandType, _SecondOperandType>::DivideExpression(const _FirstOperandType& firstOperand, const _SecondOperandType& secondOperand) noexcept :
    m_firstOperand(firstOperand),
    m_secondOperand(secondOperand)
{
}

template <typename _FirstOperandType, typename _SecondOperandType>
constexpr const auto DivideExpression<_FirstOperandType, _SecondOperandType>::operator[](std::size_t index) const
{
    return m_firstOperand[index] / m_secondOperand[index];
}

template <typename _FirstOperandType, typename _SecondOperandType>
constexpr const _FirstOperandType& DivideExpression<_FirstOperandType, _SecondOperandType>::GetFirstOperand() const noexcept
{
    return m_firstOperand;
}

template <typename _FirstOperandType, typename _SecondOperandType>
constexpr const _SecondOperandType& DivideExpression<_FirstOperandType, _SecondOperandType>::GetSecondOperand() const noexcept
{
    return m_secondOperand;
}

template <typename _DerivedExpressionType>
template <typename _SecondOperandType>
constexpr const PlusExpression<_DerivedExpressionType, _SecondOperandType> BaseExpression<_DerivedExpressionType>::operator+(const _SecondOperandType& rhs) const noexcept
{
    return {reinterpret_cast<const _DerivedExpressionType&>(*this), rhs};
}

template <typename _DerivedExpressionType>
template <typename _SecondOperandType>
constexpr const MinusExpression<_DerivedExpressionType, _SecondOperandType> BaseExpression<_DerivedExpressionType>::operator-(const _SecondOperandType& rhs) const noexcept
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

} /* namespace utility */
} /* namespace tgon */