/**
 * @filename    TClassPreprocessor.h
 * @author      ggomdyu
 * @since       04/09/2017
 */

#pragma once

#define TGON_DELETE_CTOR_DTOR(className)\
    className() = delete;\
    ~className() = delete