/*
 * author   ggomdyu
 * since    04/24/2016


*/


#pragma once

/*
 * Dynamic-link library
*/
#ifndef TGON_STATIC_BUILD
#	ifdef TGON_API_EXPORT
#		define TGON_API __declspec( dllexport )
#	else
#		define TGON_API __declspec( dllimport )
#	endif
#else
/*
 * Staic library
*/
#	define TGON_API
#endif