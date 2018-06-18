/**
 * @file    StaticInvoke.h
 * @author  ggomdyu
 * @since   05/06/2018
 */

#pragma once

#define TGON_STATIC_INVOKE(function)\
    {\
        static void* dummy = [&]() -> void*\
        {\
            function();\
            return nullptr;\
        } ();\
        dummy = nullptr;\
    }
