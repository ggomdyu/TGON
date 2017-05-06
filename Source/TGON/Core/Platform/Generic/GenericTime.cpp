#include "PrecompiledHeader.h"
#include "GenericTime.h"

namespace tgon {
namespace platform {
namespace {

const std::size_t g_oldOSExecutionTime = GetOSExecutionTime();

} /* namespace */

std::size_t GetProcessExecutionTime()
{
    return GetOSExecutionTime() - g_oldOSExecutionTime;
}

} /* namespace platform */
} /* namespace tgon */