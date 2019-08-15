/**
 * @file    BaseAudioImporter.h
 * @author  ggomdyu
 * @since   05/02/2018
 */

#pragma once
#include <cstdint>
#include <memory>
#include <boost/noncopyable.hpp>

namespace tgon
{

template <typename _DerivedType>
class BaseAudioImporter :
    private boost::noncopyable
{
/**@section Constructor */
public:
    BaseAudioImporter() noexcept;
    BaseAudioImporter(const uint8_t* fileData, std::size_t fileDataBytes);

/**@section Method */
public:
    static bool VerifyFormat(const uint8_t* fileData, std::size_t fileDataBytes);
    bool Import(const uint8_t* fileData, std::size_t fileDataBytes);
    bool IsValid() const noexcept;
    std::unique_ptr<uint8_t[]>& GetAudioData() noexcept;
    const std::unique_ptr<uint8_t[]>& GetAudioData() const noexcept;
    size_t GetAudioDataBytes() const noexcept;
    int32_t GetBitsPerSample() const noexcept;
    int32_t GetChannels() const noexcept;
    int32_t GetSamplingRate() const noexcept;

/**@section Variable */
protected:
    std::unique_ptr<uint8_t[]> m_audioData;
    size_t m_audioDataBytes;
    int32_t m_bitsPerSample;
    int32_t m_channels;
    int32_t m_samplingRate;
};

template <typename _DerivedType>
inline BaseAudioImporter<_DerivedType>::BaseAudioImporter() noexcept :
    m_audioDataBytes(0),
    m_bitsPerSample(0),
    m_channels(0),
    m_samplingRate(0)
{
}

template <typename _DerivedType>
inline BaseAudioImporter<_DerivedType>::BaseAudioImporter(const uint8_t* fileData, std::size_t fileDataBytes) :
    BaseAudioImporter()
{
    this->Import(fileData, fileDataBytes);
}

template <typename _DerivedType>
inline bool BaseAudioImporter<_DerivedType>::Import(const uint8_t* fileData, std::size_t fileDataBytes)
{
    return static_cast<_DerivedType*>(this)->Import(fileData, fileDataBytes);
}

template <typename _DerivedType>
inline bool BaseAudioImporter<_DerivedType>::IsValid() const noexcept
{
    return m_audioData != nullptr;
}

template <typename _DerivedType>
inline bool BaseAudioImporter<_DerivedType>::VerifyFormat(const uint8_t* fileData, std::size_t fileDataBytes)
{
    return _DerivedType::VerifyFormat(fileData, fileDataBytes);
}

template <typename _DerivedType>
inline std::unique_ptr<uint8_t[]>& BaseAudioImporter<_DerivedType>::GetAudioData() noexcept
{
    return m_audioData;
}

template <typename _DerivedType>
inline const std::unique_ptr<uint8_t[]>& BaseAudioImporter<_DerivedType>::GetAudioData() const noexcept
{
    return m_audioData;
}

template<typename _DerivedType>
inline size_t BaseAudioImporter<_DerivedType>::GetAudioDataBytes() const noexcept
{
    return m_audioDataBytes;
}

template <typename _DerivedType>
inline int32_t BaseAudioImporter<_DerivedType>::GetBitsPerSample() const noexcept
{
    return m_bitsPerSample;
}

template <typename _DerivedType>
inline int32_t BaseAudioImporter<_DerivedType>::GetChannels() const noexcept
{
    return m_channels;
}

template <typename _DerivedType>
inline int32_t BaseAudioImporter<_DerivedType>::GetSamplingRate() const noexcept
{
    return m_samplingRate;
}

}
