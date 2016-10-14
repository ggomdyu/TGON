/*
 * Author : Cha Junho
 * Date : 05/24/2016
 * Latest author :
 * Latest date :
 * Description : Extension of type_traits header
*/


#pragma once


namespace tgon
{


/* 
 * For function_traits 
*/
template <typename>
struct function_traits;

template <typename RetTy, typename... Args>
struct function_traits<RetTy( Args... )>
{
public:
	using return_type = RetTy;
	enum
	{
		argument_count = sizeof...( Args ),
	};

public:
	function_traits<RetTy( Args... )>( ) = delete;
};

template <typename RetTy, typename... Args>
struct function_traits<RetTy(*)( Args... )> :
	public function_traits<RetTy( Args... )>
{
};

template <typename RetTy, typename ClassTy, typename... Args>
struct function_traits<RetTy( ClassTy::* )( Args... )> :
	public function_traits<RetTy( Args... )>
{
	using class_type = ClassTy;
};


} /*namespace tgon*/
