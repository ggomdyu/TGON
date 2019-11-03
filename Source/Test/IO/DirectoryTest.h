/**
 * @file    DirectoryTest.h
 * @author  ggomdyu
 * @since   10/30/2019
 */

#pragma once
#include <cassert>

#include "IO/Path.h"
#include "IO/File.h"
#include "Platform/Environment.h"
#include "Diagnostics/Debug.h"

#include "../Test.h"

namespace tgon
{

class DirectoryTest :
    public Test
{
/**@section Method */
public:
    virtual void Evaluate() override
    {
        using namespace tgon;
        
        auto desktopPath = Environment::GetFolderPath(Environment::SpecialFolder::Desktop);
        auto newDirPath = Path::Combine(desktopPath, "WA3eERCWER3ni");
        Directory::CreateDirectory(newDirPath.c_str());
        
        assert(Directory::Exists(newDirPath.c_str()) == true);
        
        auto newDirPath2 = Path::Combine(desktopPath, "oiwjciohwu");
        assert(Directory::Move(newDirPath.c_str(), newDirPath2.c_str()) == true);
        assert(Directory::Exists(newDirPath.c_str()) == false);
        assert(Directory::Exists(newDirPath2.c_str()) == true);
        
#if TGON_PLATFORM_WINDOWS
        assert(Path::GetPathRoot("/Users/chajunho/") == "\\");
        assert(Path::GetPathRoot("/") == "\\");
        assert(Path::GetPathRoot("/Users") == "\\");
        assert(Path::GetPathRoot("") == "");
        assert(Path::GetPathRoot("C:/") == "C:\\");
        assert(Path::GetPathRoot("C:") == "C:");
        assert(Path::GetPathRoot("C://") == "C:\\");
        assert(Path::GetPathRoot("C:\\") == "C:\\");
        assert(Path::GetPathRoot("\\Users\\chajunho\\") == "\\");
        assert(Path::GetPathRoot("\\") == "\\");
#else
        assert(Path::GetPathRoot("/Users/chajunho/") == "/");
        assert(Path::GetPathRoot("/") == "/");
        assert(Path::GetPathRoot("/Users") == "/");
        assert(Path::GetPathRoot("") == "");
        assert(Path::GetPathRoot("C:/") == "");
        assert(Path::GetPathRoot("C:") == "");
        assert(Path::GetPathRoot("C://") == "");
        assert(Path::GetPathRoot("C:\\") == "");
        assert(Path::GetPathRoot("\\Users\\chajunho\\") == "");
        assert(Path::GetPathRoot("\\") == "");
#endif
        
        assert(Directory::Delete(newDirPath2.c_str()) == true);
    }

private:

};

} /* namespace tgon */
