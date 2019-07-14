#include "PrecompiledHeader.h"

#include <filesystem>

#include "String/Encoding.h"

#include "File.h"

namespace tgon
{
namespace
{

thread_local char g_tempPathBuffer[2048];

} /* namespace */

File::File()
{
}

File::~File()
{
}

bool File::Delete(const std::string_view& path)
{
    return std::filesystem::remove(path);
}

} /* namespace tgon */