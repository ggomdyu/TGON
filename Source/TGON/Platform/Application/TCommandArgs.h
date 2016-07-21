/*
* Author : Cha Junho
* Date : 07/21/2016
* Latest author :
* Latest date :
*/


#pragma once


struct TCommandArgs
{
public:
	/*
		Cons/Destructor
	*/
	TCommandArgs( int argc, const char** argv ) :
		m_argc( argc ),
		m_argv( argv )
	{
	}

	
	/*
		Gets
	*/
	const char** GetCommandLines( ) const;
	
	int GetCommandCount( ) const;




private:
	int m_argc;
	const char** m_argv;
};