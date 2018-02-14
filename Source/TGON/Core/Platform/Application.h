/**
 * @filename    Application.h
 * @author      ggomdyu
 * @since       04/01/2016
 */

#pragma once
#include "Config.h"

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

#include BOOST_PP_STRINGIZE(BOOST_PP_CAT(TGON_PLATFORM_NAME, BOOST_PP_CAT(/, BOOST_PP_CAT(TGON_PLATFORM_NAME, Application.h))))

namespace tgon
{
namespace core
{

class Application :
    public BOOST_PP_CAT(TGON_PLATFORM_NAME, Application)
{
public:
    TGON_RUNTIME_OBJECT(Application)

/* @section Public constructor */
public:
    using SuperType::SuperType;
};

} /* namespace core */
} /* namespace tgon */