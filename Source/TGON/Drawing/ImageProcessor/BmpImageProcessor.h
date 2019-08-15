/**
 * @file    BmpImageProcessor.h
 * @author  ggomdyu
 * @since   04/22/2018
 */

#pragma once
#include "BaseImageProcessor.h"

namespace tgon
{

class BmpImageProcessor :
    public BaseImageProcessor<BmpImageProcessor>
{
/* @section Constructor */
public:
    using BaseImageProcessor<BmpImageProcessor>::BaseImageProcessor;

/* @section Method */
public:
    /* @brief   Verifies the file format is exact. */
    static bool VerifyFormat(const uint8_t* fileData, size_t fileDataBytes);

    /* @brief   Decodes the file to the image. */
    bool Import(const uint8_t* fileData, size_t fileDataBytes);
};

inline bool BmpImageProcessor::Import(const uint8_t* fileData, std::size_t fileDataBytes)
{
    return false;
}

inline bool BmpImageProcessor::VerifyFormat(const uint8_t* fileData, std::size_t fileDataBytes)
{
    if (fileDataBytes < 2)
    {
        return false;
    }

    const char* header = reinterpret_cast<const char*>(&fileData[0]);
    return (header[0] == 'B' && header[1] == 'M');
}
    
}  

//namespace
//{
//
//// Currently support windows format, not os2
//template <typename _AllocatorType>
//bool ResolveBMP(const uint8_t* srcData, std::size_t srcDataLen, std::vector<uint8_t, _AllocatorType>* destData, int32_t* width, int32_t* height, int32_t* channels, int32_t* colorDepth, PixelFormat* pixelFormat)
//{
//    if (srcData[0] != 'B' || srcData[1] != 'M')
//    {
//        return false;
//    }
//
//    *width = *(int*)&(srcData[0x12]);
//    *height = *(int*)&(srcData[0x16]);
//
//    int imageSize = *(int*)&(srcData[0x22]);
//    destData->resize(imageSize);
//
//    int dataStartPos = *(int*)&(srcData[0x0A]);
//    if (dataStartPos == 0)
//    {
//        dataStartPos = 54;
//    }
//
//    memcpy(destData->data(), srcData + dataStartPos, imageSize);
//
//    return true;
//}
//
//}
