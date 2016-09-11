/*
* Author : Cha Junho
* Date : 04/02/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "OSAL/PlatformApplication.h"


namespace tgon
{


class TGON_API TApplication :
	public ApplicationImpl
{
	/*
		Commands
	*/
public:

	/*
		Sets
	*/
	

	/*
		Gets
	*/
	// 
	// @return Return Global TApplication instance
	// 
	static TApplication* Get( );


	/*
		Con/Destructor
	*/
private:
	TApplication( ) = default;

	virtual ~TApplication( ) = default;


	/*
		Private variables
	*/
private:
};


inline TApplication* TApplication::Get( )
{
	static TApplication ret;
	return &ret;
}


} /*namespace tgon*/