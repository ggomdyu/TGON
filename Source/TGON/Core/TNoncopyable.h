/*
* Author : Junho-Cha
* Date : 04/16/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../Config/Build.h"



namespace tgon
{


class TGON_API TNoncopyable
{
protected:
	TNoncopyable( ) {};
	~TNoncopyable( ) {};

private:
	TNoncopyable( const TNoncopyable& ) {};
	const TNoncopyable& operator=( const TNoncopyable& ) {};
};


}