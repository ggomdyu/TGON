#pragma once

#include <cstdint>
#include <type_traits>

namespace tg
{

template <typename _Operator, typename _FirstOperand, typename _SecondOperand>
struct Expression;

namespace detail
{

template <typename _Type>
concept HasBracketOperator = requires(_Type value) {
    value[0];
};
    
template <typename>
struct IsExpression : std::false_type {};

template <typename _Operator, typename _FirstOperand, typename _SecondOperand>
struct IsExpression<Expression<_Operator, _FirstOperand, _SecondOperand>> : std::true_type {};

}

template <typename _Type>
concept StructuredExpression = detail::IsExpression<_Type>::value;

struct Add
{
    template <typename _FirstOperand, typename _SecondOperand>
    constexpr _FirstOperand operator()(const _FirstOperand& lhs, const _SecondOperand& rhs) const
    {
        return lhs + rhs;
    }
};

struct Subtract
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

template <typename _FirstOperand, typename _SecondOperand>
using AddExpression = Expression<Add, _FirstOperand, _SecondOperand>;

template <typename _FirstOperand, typename _SecondOperand>
using SubtractExpression = Expression<Add, _FirstOperand, _SecondOperand>;

template <typename _FirstOperand, typename _SecondOperand>
using MultiplyExpression = Expression<Multiply, _FirstOperand, _SecondOperand>;

template <typename _FirstOperand, typename _SecondOperand>
using DivideExpression = Expression<Divide, _FirstOperand, _SecondOperand>;

template <typename _Operator, typename _FirstOperand, typename _SecondOperand>
struct Expression final
{
/**@section Constructor */
public:
    constexpr Expression(const _FirstOperand& firstOperand, const _SecondOperand& secondOperand) noexcept :
        m_firstOperand(firstOperand),
        m_secondOperand(secondOperand)
    {
    }

/**@section Operator */
public:
    auto operator[](int32_t index)
    {
        /*if constexpr (detail::HasBracketOperator<decltype(m_firstOperand)> && detail::HasBracketOperator<decltype(m_secondOperand)>)
        {*/
            return _Operator{}(m_firstOperand[index], m_secondOperand[index]);
        //}
        //else if (detail::HasBracketOperator<decltype(m_firstOperand)>)
        //{
        //    return _Operator{}(m_firstOperand[index], m_secondOperand);
        //}
        //else
        //{
        //    return _Operator{}(m_firstOperand, m_secondOperand[index]);
        //}
    }

    template <typename _SecondOperand2>
    constexpr AddExpression<Expression, _SecondOperand2> operator+(const _SecondOperand2& rhs) const noexcept
    {
        return {*this, rhs};
    }

    template <typename _SecondOperand2>
    constexpr SubtractExpression<Expression, _SecondOperand2> operator-(const _SecondOperand2& rhs) const noexcept
    {
        return {*this, rhs};
    }

    template <typename _SecondOperand2>
    constexpr MultiplyExpression<Expression, _SecondOperand2> operator*(const _SecondOperand2& rhs) const noexcept
    {
        return {*this, rhs};
    }

    template <typename _SecondOperand2>
    constexpr Expression<Divide, Expression, _SecondOperand2> operator/(const _SecondOperand2& rhs) const noexcept
    {
        return {*this, rhs};
    }

/**@section Method */
public:
    [[nodiscard]] constexpr const _FirstOperand& GetFirstOperand() const noexcept
    {
        return m_firstOperand;
    }

    [[nodiscard]] constexpr const _SecondOperand& GetSecondOperand() const noexcept
    {
        return m_secondOperand;
    }

/**@section Variable */
private:
    const _FirstOperand& m_firstOperand;
    const _SecondOperand& m_secondOperand;
};

//template <typename _Operator, typename _FirstOperand, typename _SecondOperand>
//Expression(const _FirstOperand& firstOperand, const _SecondOperand& secondOperand) -> Expression<_Operator, _FirstOperand, _SecondOperand>;

//template <bool _IsIndexable>
//struct Foo
//{
//    template <typename _Operator, typename _FirstOperand, typename _SecondOperand>
//    static auto Foo2(const _FirstOperand& first, const _SecondOperand& second, int32_t index);
//};
//
//template <>
//template <typename _Operator, typename _FirstOperand, typename _SecondOperand>
//auto Foo<true>::Foo2(const _FirstOperand& first, const _SecondOperand& second, int32_t index)
//{
//    return _Operator{}(first[index], second[index]);
//}
//
//template <>
//template <typename _Operator, typename _FirstOperand, typename _SecondOperand>
//auto Foo<false>::Foo2(const _FirstOperand& first, const _SecondOperand& second, int32_t index)
//{
//    if constexpr (detail::HasBracketOperator<decltype(first)>)
//    {
//        return _Operator{}(first[index], second);
//    }
//    else
//    {
//        return _Operator{}(first, second[index]);
//    }
//}

//template <typename _Operator, typename _FirstOperand, typename _SecondOperand>
//constexpr auto Expression<_Operator, _FirstOperand, _SecondOperand>::operator[](int32_t index) const
//{
//    return Foo<detail::HasBracketOperator<_FirstOperand>&& detail::HasBracketOperator<_SecondOperand>>::Foo2<_Operator, _FirstOperand, _SecondOperand>(m_firstOperand, m_secondOperand, index);
//}

}
