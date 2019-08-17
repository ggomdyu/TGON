/**
 * @file    PathTest.h
 * @author  ggomdyu
 * @since   08/02/2019
 */

#pragma once
#include <cassert>

#include "IO/Path.h"
#include "IO/File.h"
#include "Diagnostics/Debug.h"

#include "../Test.h"

namespace tgon
{

class PathTest :
    public Test
{
/**@section Method */
public:
    virtual void Evaluate() override
    {
        assert(Path::GetExtension("/Users/chajunho/Desktop/1.png") == ".png");
        assert(Path::GetExtension("/Users/chajunho/Desktop/1") == "");
        assert(Path::GetExtension("1.png") == ".png");
        assert(Path::GetExtension("1") == "");
        assert(Path::GetFileNameWithoutExtension("") == "");
        assert(Path::GetExtension("") == "");
        assert(Path::GetFileName("/Users/chajunho/Desktop/1.png") == "1.png");
        assert(Path::GetFileName("") == "");
        assert(Path::GetFileNameWithoutExtension("/Users/chajunho/Desktop/123") == "123");
        assert(Path::GetFileNameWithoutExtension("/Users/chajunho/Desktop/1") == "1");
        assert(Path::GetFileNameWithoutExtension("/Users/123123.png") == "123123");
        assert(Path::GetFileNameWithoutExtension("/Users/chajunho/Desktop/1.png") == "1");
        assert(Path::GetFileNameWithoutExtension("/Users/chajunho/Desktop/1.1.png") == "1.1");
        assert(Path::GetFileNameWithoutExtension("123123") == "123123");
        assert(Path::GetFileNameWithoutExtension("1") == "1");
        assert(Path::GetFileNameWithoutExtension("1.png") == "1");
        assert(Path::GetDirectoryName("C:/1.png") == "C:");
        assert(Path::GetDirectoryName("C:\\1.png") == "");
        assert(Path::GetDirectoryName("C:/Dir/1.png") == "C:/Dir");
        assert(Path::GetDirectoryName("/Users/chajunho/Desktop/1.png") == "/Users/chajunho/Desktop");
        assert(Path::GetDirectoryName("") == "");
        assert(Path::GetDirectoryName("abc.png") == "");
        assert(Path::GetDirectoryName("abc") == "");
        assert(Path::HasExtension("/Users/chajunho/Desktop/1.png") == true);
        assert(Path::HasExtension("/Users/chajunho/Desktop/1") == false);
        assert(Path::HasExtension("/Users/chajunho/Desktop/") == false);
        assert(Path::HasExtension("/Users/chajunho/Desktop") == false);
        assert(Path::HasExtension("1.png") == true);
        assert(Path::HasExtension(".png") == true);
        assert(Path::HasExtension("png") == false);
        assert(Path::ChangeExtension("/Users/chajunho/Desktop/1.png", "ext") == "/Users/chajunho/Desktop/1.ext");
        assert(Path::ChangeExtension(".png", "ext") == ".ext");
        assert(Path::ChangeExtension("/Users/chajunho/Desktop", "ext") == "/Users/chajunho/Desktop.ext");
        assert(Path::ChangeExtension("/Users/chajunho/Desktop/", "ext") == "/Users/chajunho/Desktop/.ext");
        assert(Path::ChangeExtension("1.png", "ext") == "1.ext");
        assert(Path::ChangeExtension("png", "ext") == "png.ext");
        assert(Path::ChangeExtension("", "ext") == "");
        assert(Path::ChangeExtension("", "") == "");
    }

private:

};

} /* namespace tgon */
