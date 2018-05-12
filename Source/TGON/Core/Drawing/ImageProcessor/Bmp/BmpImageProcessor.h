/**
 * @filename    BmpImageProcessor.h
 * @author      ggomdyu
 * @since       04/22/2018
 */

#pragma once
#include "../Generic/GenericImageProcessor.h"

namespace tgon
{

template <typename _AllocatorType = std::allocator<uint8_t>>
class BmpImageProcessor :
    public GenericImageProcessor<BmpImageProcessor<_AllocatorType>, _AllocatorType>
{
/* @section Public constructor */
public:
    using GenericImageProcessor::GenericImageProcessor;

/* @section Public method */
public:
    static bool VerifyFormat(const uint8_t* srcData, uint32_t srcDataBytes);
    bool Import(const uint8_t* srcData, uint32_t srcDataBytes);
};

template <typename _AllocatorType>
inline bool BmpImageProcessor<_AllocatorType>::Import(const uint8_t* srcData, uint32_t srcDataBytes)
{
    return false;
}

template <typename _AllocatorType>
inline bool BmpImageProcessor<_AllocatorType>::VerifyFormat(const uint8_t* srcData, uint32_t srcDataBytes)
{
    if (srcDataBytes < 2)
    {
        return false;
    }

    const char* header = reinterpret_cast<const char*>(&srcData[0]);
    return (header[0] == 'B' && header[1] == 'M');
}

} /* namespace tgon */  

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
//} /* namespace */