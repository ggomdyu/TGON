/*
* Author : Cha Junho
* Date : 05/24/2016
* Latest author :
* Latest date :
*/


#pragma once


namespace tgon
{

template <typename>
struct member_function_traits;

template <typename RetTy, typename ClassTy, typename... Args>
struct member_function_traits<RetTy( ClassTy::* )( Args... )>
{
	using return_type = RetTy;
	using class_type = ClassTy;
	enum
	{
		argument_count = sizeof...( Args ),
	};
};

/* Simillar with std::result_of but more useful */
template <typename T>
struct result_of
{
	using b = member_function_traits<T>;
};

} /*namespace tgon*/
