#include "PrecompiledHeader.h"
#include "Object.h"


namespace tgon
{

Object::Object( )
{
}

Object::~Object( )
{
}

bool Object::operator==( const Object& rhs ) const
{
	return this->Equals( rhs );
}

bool Object::operator!=( const Object& rhs ) const
{
	return !this->Equals( rhs );
}

bool Object::Equals( const Object& lhs, const Object& rhs )
{
	return lhs.Equals( rhs );
}

bool Object::Equals( const Object& rhs ) const
{
	return ( this == &rhs );
}

bool Object::ReferenceEquals( const Object& lhs, const Object& rhs )
{
	return ( &lhs == &rhs );
}

} /*namespace tgon*/