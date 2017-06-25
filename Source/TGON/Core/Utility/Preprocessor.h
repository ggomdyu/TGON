/**
 * @filename    TPreprocessor.h
 * @author      ggomdyu
 * @since       04/09/2017
 */

#pragma once
#include <type_traits>

#define TGON_DELETE_CTOR_DTOR(className)\
    className() = delete;\
    ~className() = delete

#define Cplusplus98 199711
#define Cplusplus11 201103
#define Cplusplus14 201300
