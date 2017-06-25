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
struct BaseExpression
{
public:
    
};

template <typename FirstOperandTy, typename SecondOperandTy>
struct PlusExpression
{
public:
    using _FirstOperandTy = FirstOperandTy;
    using _SecondOperandTy = SecondOperandTy;

public:
    //using BaseExpression<PlusExpression<FirstOperandTy, SecondOperandTy>>::BaseExpression;
};

} /* namespace utility */
} /* namespace tgon */
