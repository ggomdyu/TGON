#pragma once

#include <cstdint>
#include <type_traits>

namespace tg
{

struct Plus
{
    template <typename _FirstOperand, typename _SecondOperand>
    constexpr _FirstOperand operator()(const _FirstOperand& lhs, const _SecondOperand& rhs) const
    {
        return lhs + rhs;
    }
};

struct Minus
{
    template <typename _FirstOperand, typename _SecondOperand>
    constexpr _FirstOperand operator()(const _FirstOperand& lhs, const _SecondOperand& rhs) const
    {
        return lhs - rhs;
    }
};

struct Multiply
{
    template <typename _FirstOperand, typename _SecondOperand>
    constexpr _FirstOperand operator()(const _FirstOperand& lhs, const _SecondOperand& rhs) const
    {
        return lhs * rhs;
    }
};

struct Divide
{
    template <typename _FirstOperand, typename _SecondOperand>
    constexpr _FirstOperand operator()(const _FirstOperand& lhs, const _SecondOperand& rhs) const
    {
        return lhs / rhs;
    }
};

template <typename _Operator, typename _FirstOperand, typename _SecondOperand>
struct ExpressionTemplate final
{
/**@section Constructor */
public:
    constexpr ExpressionTemplate(const _FirstOperand& firstOperand, const _SecondOperand& secondOperand) noexcept;

/**@section Operator */
public:
    constexpr auto operator[](int32_t index) const;
    template <typename _SecondOperand2>
    constexpr ExpressionTemplate<Plus, ExpressionTemplate, _SecondOperand2> operator+(const _SecondOperand2& rhs) const noexcept;
    template <typename _SecondOperand2>
    constexpr ExpressionTemplate<Minus, ExpressionTemplate, _SecondOperand2> operator-(const _SecondOperand2& rhs) const noexcept;
    template <typename _SecondOperand2>
    constexpr ExpressionTemplate<Multiply, ExpressionTemplate, _SecondOperand2> operator*(const _SecondOperand2& rhs) const noexcept;
    template <typename _SecondOperand2>
    constexpr ExpressionTemplate<Divide, ExpressionTemplate, _SecondOperand2> operator/(const _SecondOperand2& rhs) const noexcept;

/**@section Method */
public:
    [[nodiscard]] constexpr const _FirstOperand& GetFirstOperand() const noexcept;
    [[nodiscard]] constexpr const _SecondOperand& GetSecondOperand() const noexcept;

/**@section Variable */
private:
    const _FirstOperand& m_firstOperand;
    const _SecondOperand& m_secondOperand;
};

template <typename _Operator, typename _FirstOperand, typename _SecondOperand>
constexpr ExpressionTemplate<_Operator, _FirstOperand, _SecondOperand>::ExpressionTemplate(const _FirstOperand& firstOperand, const _SecondOperand& secondOperand) noexcept :
    m_firstOperand(firstOperand),
    m_secondOperand(secondOperand)
{
}

template <typename _Operator, typename _FirstOperand, typename _SecondOperand>
constexpr auto ExpressionTemplate<_Operator, _FirstOperand, _SecondOperand>::operator[](int32_t index) const
{
    return _Operator{}(m_firstOperand[index], m_secondOperand[index]);
}

template <typename _Operator, typename _FirstOperand, typename _SecondOperand>
template <typename _SecondOperand2>
constexpr ExpressionTemplate<Plus, ExpressionTemplate<_Operator, _FirstOperand, _SecondOperand>, _SecondOperand2> ExpressionTemplate<_Operator, _FirstOperand, _SecondOperand>::operator+(const _SecondOperand2& rhs) const noexcept
{
    return {*this, rhs};
}

template <typename _Operator, typename _FirstOperand, typename _SecondOperand>
template <typename _SecondOperand2>
constexpr ExpressionTemplate<Minus, ExpressionTemplate<_Operator, _FirstOperand, _SecondOperand>, _SecondOperand2> ExpressionTemplate<_Operator, _FirstOperand, _SecondOperand>::operator-(const _SecondOperand2& rhs) const noexcept
{
    return {*this, rhs};
}

template <typename _Operator, typename _FirstOperand, typename _SecondOperand>
template <typename _SecondOperand2>
constexpr ExpressionTemplate<Multiply, ExpressionTemplate<_Operator, _FirstOperand, _SecondOperand>, _SecondOperand2> ExpressionTemplate<_Operator, _FirstOperand, _SecondOperand>::operator*(const _SecondOperand2& rhs) const noexcept
{
    return {*this, rhs};
}

template <typename _Operator, typename _FirstOperand, typename _SecondOperand>
template <typename _SecondOperand2>
constexpr ExpressionTemplate<Divide, ExpressionTemplate<_Operator, _FirstOperand, _SecondOperand>, _SecondOperand2> ExpressionTemplate<_Operator, _FirstOperand, _SecondOperand>::operator/(const _SecondOperand2& rhs) const noexcept
{
    return {*this, rhs};
}

template <typename _Operator, typename _FirstOperand, typename _SecondOperand>
constexpr const _FirstOperand& ExpressionTemplate<_Operator, _FirstOperand, _SecondOperand>::GetFirstOperand() const noexcept
{
    return m_firstOperand;
}

template <typename _Operator, typename _FirstOperand, typename _SecondOperand>
constexpr const _SecondOperand& ExpressionTemplate<_Operator, _FirstOperand, _SecondOperand>::GetSecondOperand() const noexcept
{
    return m_secondOperand;
}

namespace detail
{

template <typename>
struct IsExpressionTemplate : std::false_type {};

template <typename _Operator, typename _FirstOperand, typename _SecondOperand>
struct IsExpressionTemplate<ExpressionTemplate<_Operator, _FirstOperand, _SecondOperand>> : std::true_type {};

}

template <typename _Type>
concept Expression = detail::IsExpressionTemplate<_Type>::value;

}
