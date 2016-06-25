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
// Additionally, Find out what cannot be selected both flags, and invoke assert.
//
uint32_t Convert_WindowStyle_To_SDLStyle( const struct WindowStyle& );


}