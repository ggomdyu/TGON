#pragma once
#include <functional>

namespace tgon
{
	namespace System {
		inline void RegisterEventCallback( const uint32_t eventType, const std::function<void()>& eventWork );
	}

	namespace Time {
		inline float GetElapsedTime( );
	}
}
