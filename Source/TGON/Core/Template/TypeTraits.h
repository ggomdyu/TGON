/*
 * author   ggomdyu
 * since    05/24/2016


*/


#pragma once


namespace tgon
{


template <typename>
struct function_traits;

template <typename RetTy, typename... Args>
struct function_traits<RetTy( Args... )>
{
public:
	using return_type = RetTy;
	using function_type = RetTy( Args... );

	enum { argument_count = sizeof...( Args ), };

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

template <typename RetTy, typename ClassTy, typename... Args>
struct function_traits<RetTy( ClassTy::* )( Args... ) const> :
	public function_traits<RetTy( Args... )>
{
	using class_type = ClassTy;
};


template <typename RetTy, typename ClassTy, typename... Args>
struct function_traits<RetTy( ClassTy::* )( Args... ) volatile> :
	public function_traits<RetTy( Args... )>
{
	using class_type = ClassTy;
};

template <typename RetTy, typename ClassTy, typename... Args>
struct function_traits<RetTy( ClassTy::* )( Args... ) const volatile> :
    public function_traits<RetTy( Args... )>
{
    using class_type = ClassTy;
};

} /*namespace tgon*/
