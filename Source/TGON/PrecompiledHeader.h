// PrecompiledHeader.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

#pragma once

// TODO: reference additional headers your program requires here

// Third-party headers are here
// boost
#include <boost/noncopyable.hpp>
#include <boost/config/suffix.hpp>
#include <boost/predef.h>


// Platform dependent headers are here
#if BOOST_OS_WINDOWS
	// Disable the min and max macros that defined in <windows.h>
#	ifndef NOMINMAX
#		define NOMINMAX
#	endif
#		include <windows.h>
#endif


// Standard C headers are here

// Standard C++ headers are here
#include <cstdint>
#include <cstdlib>
#include <cassert>
#include <memory>
#include <string>
#include <vector>
#include <initializer_list>
#include <type_traits>
#include <deque>
#include <map>
#include <unordered_map>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
