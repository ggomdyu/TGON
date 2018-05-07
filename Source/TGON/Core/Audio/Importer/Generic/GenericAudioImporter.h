/**
 * @filename    GenericAudioImporter.h
 * @author      ggomdyu
 * @since       05/02/2018
 */

#pragma once
#include <vector>
#include <cstdint>

#include "Core/Debug/Log.h"

namespace tgon
{

template <typename _DerivedType, typename _AllocatorType = std::allocator<uint8_t>>
class GenericAudioImporter
{
/* @section Public constructor */
public:
    GenericAudioImporter() noexcept;
    GenericAudioImporter(const uint8_t* srcData, std::size_t srcDataBytes);

/* @section Public method */
public:
    /* @brief   Verifies the importing file is exactly WAV. */
    static bool VerifyFormat(const uint8_t* srcData, std::size_t srcDataBytes);
    bool Import(const uint8_t* srcData, std::size_t srcDataBytes);
    bool IsValid() const noexcept;
    std::vector<uint8_t, _AllocatorType>& GetAudioData() noexcept;
    const std::vector<uint8_t, _AllocatorType>& GetAudioData() const noexcept;
    int32_t GetBitsPerSample() const noexcept;
    int32_t GetChannels() const noexcept;
    int32_t GetSamplingRate() const noexcept;

/* @section Protected variable */
protected:
    std::vector<uint8_t, _AllocatorType> m_audioData;
    int32_t m_bitsPerSample;
    int32_t m_channels;
    int32_t m_samplingRate;
};

template <typename _DerivedType, typename _AllocatorType>
inline GenericAudioImporter<_DerivedType, _AllocatorType>::GenericAudioImporter() noexcept :
    m_bitsPerSample(0),
    m_channels(0),
    m_samplingRate(0)
{
}

template <typename _DerivedType, typename _AllocatorType>
inline GenericAudioImporter<_DerivedType, _AllocatorType>::GenericAudioImporter(const uint8_t* srcData, std::size_t srcDataBytes) :
    GenericAudioImporter()
{
    this->Import(srcData, srcDataBytes);
}

template <typename _DerivedType, typename _AllocatorType>
inline bool GenericAudioImporter<_DerivedType, _AllocatorType>::Import(const uint8_t* srcData, std::size_t srcDataBytes)
{
    return static_cast<_DerivedType*>(this)->Import(srcData, srcDataBytes);
}

template <typename _DerivedType, typename _AllocatorType>
inline bool GenericAudioImporter<_DerivedType, _AllocatorType>::IsValid() const noexcept
{
    return m_audioData.size() > 0;
}

template <typename _DerivedType, typename _AllocatorType>
inline bool GenericAudioImporter<_DerivedType, _AllocatorType>::VerifyFormat(const uint8_t* srcData, std::size_t srcDataBytes)
{
    return static_cast<_DerivedType*>(this)->VerifyFormat(srcData, srcDataBytes);
}

template <typename _DerivedType, typename _AllocatorType>
inline std::vector<uint8_t, _AllocatorType>& GenericAudioImporter<_DerivedType, _AllocatorType>::GetAudioData() noexcept
{
    return m_audioData;
}

template <typename _DerivedType, typename _AllocatorType>
inline const std::vector<uint8_t, _AllocatorType>& GenericAudioImporter<_DerivedType, _AllocatorType>::GetAudioData() const noexcept
{
    return m_audioData;
}

template <typename _DerivedType, typename _AllocatorType>
inline int32_t GenericAudioImporter<_DerivedType, _AllocatorType>::GetBitsPerSample() const noexcept
{
    return m_bitsPerSample;
}

template <typename _DerivedType, typename _AllocatorType>
inline int32_t GenericAudioImporter<_DerivedType, _AllocatorType>::GetChannels() const noexcept
{
    return m_channels;
}

template <typename _DerivedType, typename _AllocatorType>
inline int32_t GenericAudioImporter<_DerivedType, _AllocatorType>::GetSamplingRate() const noexcept
{
    return m_samplingRate;
}

} /* namespace tgon */