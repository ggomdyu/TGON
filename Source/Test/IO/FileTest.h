/**
 * @file    FileTest.h
 * @author  ggomdyu
 * @since   08/02/2019
 */

#pragma once
#include <cassert>

#include "IO/Path.h"
#include "IO/File.h"
#include "Diagnostics/Log.h"

#include "../Test.h"

namespace tgon
{

class FileTest :
    public Test
{
/**@section Method */
public:
    virtual void DoTest() override
    {
        // WARNING: This test requires 1.png in desktop directory!
        auto desktopPath = Path::GetDesktopDirectory();
        auto srcImagePath = desktopPath + "/1.png";
        if (File::Exists(srcImagePath) == false)
        {
            assert(false && "This test requires 1.png in desktop directory!");
            return;
        }

        auto dtl = DateTime(2001, 10, 12, 4, 2, 10, DateTimeKind::Local);
        auto dtu = DateTime(2001, 10, 12, 4, 2, 10, DateTimeKind::Utc);

        File::SetCreationTime(srcImagePath, dtl);
        assert(File::GetCreationTime(srcImagePath).value() == dtu);
        File::SetCreationTime(srcImagePath, dtu);
        assert(File::GetCreationTime(srcImagePath).value() == dtu.AddHours(9.0));

        File::SetCreationTimeUtc(srcImagePath, dtu);
        assert(File::GetCreationTimeUtc(srcImagePath).value() == dtu);
        File::SetCreationTimeUtc(srcImagePath, dtl);
        assert(File::GetCreationTimeUtc(srcImagePath).value() == dtu.AddHours(-9.0));
        
        File::SetLastAccessTime(srcImagePath, dtl);
        assert(File::GetLastAccessTime(srcImagePath).value() == dtu);
        File::SetLastAccessTime(srcImagePath, dtu);
        assert(File::GetLastAccessTime(srcImagePath).value() == dtu.AddHours(9.0));

        File::SetLastAccessTimeUtc(srcImagePath, dtu);
        assert(File::GetLastAccessTimeUtc(srcImagePath).value() == dtu);
        File::SetLastAccessTimeUtc(srcImagePath, dtl);
        assert(File::GetLastAccessTimeUtc(srcImagePath).value() == dtu.AddHours(-9.0));

        File::SetCreationTime(srcImagePath, dtl);
        assert(File::GetCreationTime(srcImagePath).value() == dtu);
        File::SetCreationTime(srcImagePath, dtu);
        assert(File::GetCreationTime(srcImagePath).value() == dtu.AddHours(9.0));

        File::SetCreationTimeUtc(srcImagePath, dtu);
        assert(File::GetCreationTimeUtc(srcImagePath).value() == dtu);
        File::SetCreationTimeUtc(srcImagePath, dtl);
        assert(File::GetCreationTimeUtc(srcImagePath).value() == dtu.AddHours(-9.0));

        auto destImagePath = desktopPath + "/1_q43289n231nk.png";
        File::Move(srcImagePath, destImagePath);
        assert(File::Exists(destImagePath));
        assert(File::Exists(srcImagePath) == false);
        File::Move(destImagePath, srcImagePath);

        File::Copy(srcImagePath, destImagePath);
        assert(File::Exists(destImagePath));

        File::Delete(destImagePath);
        assert(File::Exists(destImagePath) == false);
    }

private:

};

} /* namespace tgon */