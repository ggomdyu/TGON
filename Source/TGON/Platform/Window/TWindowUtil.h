/*
* Author : Junho-Cha
* Date : 11/12/2015
* Latest author :
* Latest date :
*/

#pragma once


namespace tgon
{

//
// Transform WindowStyle struct to SDL window style. 
// Additionally, Find out what cannot be selected both flags, and call assert.
//
uint32_t Convert_WndStyle_To_SDLFlag( const struct WindowStyle& );


}