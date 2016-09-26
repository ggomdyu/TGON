//---------------------------------------------------------------------------------
// Author : Cha Junho
// Date : 04/19/2016
//---------------------------------------------------------------------------------

#pragma once
#include <string>
#include <cstdint>
#include <bitset>

#include "../Math/TMath.h"


namespace tgon
{


struct TypeInfo;

namespace detail {
	template <typename Ty>
	struct TypeInfoImpl;
} /* namespace detail */

template <typename Ty>
inline const TypeInfo& GetType( )
{
	static detail::TypeInfoImpl<Ty> type;
	return type;
}

/* RTTI */
struct TypeInfo
{
	//
	// Enumerators
	//
protected:
	enum { MAX_BITSET_COUNT = 32, };
	enum BitsetIndex {
		isClass,
		isAbstract,
		isEnum,
		isArray,
		isReference,
		isPointer,
		isConst,
		isVolatile,
		isMemberFunctionPointer,
		isPOD,
	};

	//
	// Commands
	//
public:
	bool IsClass( ) const		{ return m_bits[isClass]; }
	bool IsAbstract( ) const	{ return m_bits[isAbstract]; }
	bool IsEnum( ) const		{ return m_bits[isEnum]; }
	bool IsArray( ) const		{ return m_bits[isArray]; }
	bool IsReference( ) const	{ return m_bits[isReference]; }
	bool IsPointer( ) const		{ return m_bits[isPointer]; }
	bool IsConst( ) const		{ return m_bits[isConst]; }
	bool IsVolatile( ) const	{ return m_bits[isVolatile]; }
	bool IsMemberFunctionPointer( ) const { return m_bits[isMemberFunctionPointer]; }
	bool IsPOD( ) const			{ return m_bits[isPOD]; }

	//
	// Gets
	//
	/* @return	Return stored hase code */
	uint32_t GetHashCode( ) const
	{
		return m_hashCode;
	}

	/* @return	Return name as const reference */
	const std::string& GetName( ) const
	{
		return m_name;
	}

	//
	// Ctor/Dtor
	//
protected:
	explicit TypeInfo( /*IN*/ const char* name,
					   /*IN*/ const std::size_t length,
					   /*IN*/ const std::bitset<MAX_BITSET_COUNT>& bits ) noexcept :
		m_hashCode( TMath::StringToHash( name, length )),
		m_name( name ),
		m_bits( bits )
	{
	}

public:
	~TypeInfo( ) = default;

	//
	// Private variables
	//
private:
	/* @note	Type name as string value */
	const std::string m_name;

	/* @note	Hash value of m_name */
	const uint32_t m_hashCode;

	/* @note	Attribute table of this type's owner */
	const std::bitset<MAX_BITSET_COUNT> m_bits;
};

namespace detail
{

template <typename Ty>
struct TypeInfoImpl final :
	public TypeInfo
{
	//
	// Ctor/Dtor
	//
public:
	TypeInfoImpl( ) noexcept :
		TypeInfoImpl( typeid( Ty ))
	{
	}
	TypeInfoImpl( const char* name, std::size_t length ) noexcept :
		TypeInfo( name, length, MakeBitSet( ))
	{
	}
protected:
	explicit TypeInfoImpl( const type_info& typeInfo ) noexcept :
		TypeInfo( typeInfo.name( ), std::strlen( typeInfo.name( )), MakeBitSet( ))
	{
	}
public:
	~TypeInfoImpl( ) = default;

	//
	// Internal works
	//
private:
	const std::bitset<MAX_BITSET_COUNT> MakeBitSet( ) const noexcept
	{
		std::bitset<MAX_BITSET_COUNT> bits;

		bits[isClass]		= std::is_class<Ty>::value;
		bits[isAbstract]	= std::is_abstract<Ty>::value;
		bits[isEnum]		= std::is_enum<Ty>::value;
		bits[isArray]		= std::is_array<Ty>::value;
		bits[isReference]	= std::is_reference<Ty>::value;
		bits[isPointer]		= std::is_pointer<Ty>::value;
		bits[isConst]		= std::is_const<Ty>::value;
		bits[isVolatile]	= std::is_volatile<Ty>::value;
		bits[isMemberFunctionPointer] = std::is_member_function_pointer<Ty>::value;
		bits[isPOD]			= std::is_pod<Ty>::value;
		
		return bits;
	}
};
} /*namespace detail*/


} /*namespace tgon*/