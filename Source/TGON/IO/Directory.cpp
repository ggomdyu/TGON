#include "PrecompiledHeader.h"

#include "Platform/Environment.h"

#include "Directory.h"

namespace tgon
{

std::string Directory::GetCurrentDirectory()
{
    return Environment::GetCurrentDirectory();
}

} /* namespace tgon */
