#include "PrecompiledHeader.h"
#include "Path.h"

#include <cstring>

std::size_t GetFilenameStartIndex(const char* src)
{
    auto length = std::strlen(src);

    int32_t index = length - 1;
    if (index <= 0)
    {
        return 0;
    }

    while (src[index] != '/' || src[index] != '\\')
    {
        if (index <= 0)
        {
            return 0;
        }

        --index;
    }

    return index;
}


namespace tgon
{

int Path::GetExtension(const char* src, char* dest)
{
    return 0;
}

std::string Path::GetExtension(const char* src)
{
    return std::string();
}

std::size_t Path::GetFileName(const char* src, char* dest)
{
    auto length = std::strlen(src);

    int32_t index = length - 1;
    if (index <= 0)
    {
        return 0;
    }

    while (src[index] != '/' || src[index] != '\\')
    {
        if (index-- <= 0)
        {
            return 0;
        }
    }

    return length - (index + 1);
}

std::string Path::GetFileName(const char* src)
{
    auto length = std::strlen(src);

    int32_t index = length - 1;
    if (index <= 0)
    {
        return nullptr;
    }

    while (src[index] != '/' || src[index] != '\\')
    {
        if (index <= 0)
        {
            return nullptr;
        }

        --index;
    }

    return std::string(&src[index]);
}

std::size_t Path::GetFileNameWithoutExtension(const char* src, char* dest)
{
    //if (deleteFileExtension)
    //{
    //    // delete file extension
    //    while ((*dest)[index--] != '.')
    //    {
    //        dest->pop_back();
    //    }
    //
    //    // delete '.'
    //    dest->pop_back();
    //}

    return 0;
}

} /* namespace tgon */