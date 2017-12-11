/**
 * @filename    File.h
 * @author      ggomdyu
 * @since       12/10/2017
 */

#pragma once
#include <cstdio>

namespace tgon
{
namespace file
{

class File
{
public:
    File(const char* filePath);
    ~File();

private:
    FILE* m_file;
};

} /* namespace file */
} /* namespace tgon */
