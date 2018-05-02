/**
 * @filename    OggVorbisAudioImporter.h
 * @author      ggomdyu
 * @since       04/20/2018
 */

#pragma once
#include <vector>
#include <cstdint>

#include <vorbis/vorbisfile.h>
#include <ogg/ogg.h>

#include "Core/Debug/Log.h"

namespace tgon
{
namespace detail
{

struct OggVorbisFileStream final
{
/* @section Public constructor */
public:
    OggVorbisFileStream(const uint8_t* srcData, size_t srcDataBytes) noexcept;

/* @section Public method */
public:
    static size_t Read(void* buffer, size_t elementSize, size_t elementCount, void* stream);
    static int Seek(void* stream, ogg_int64_t offset, int origin);
    static int Close(void* stream);
    static long Tell(void* stream);

/* @section Public variable */    
public:
    const uint8_t* srcData;
    const uint8_t* srcDataIter;
    size_t srcDataBytes;
};

} /* namespace detail */

template <typename _AllocatorType = std::allocator<uint8_t>>
class OggVorbisAudioImporter
{

/* @section Public constructor */
public:
    OggVorbisAudioImporter() noexcept;
    OggVorbisAudioImporter(const uint8_t* srcData, std::size_t srcDataBytes);

/* @section Public method */
public:
    /* @brief   Verifies the importing file is exactly WAV. */
    static bool VerifyFormat(const uint8_t* srcData, std::size_t srcDataBytes);
    bool Import(const uint8_t* srcData, std::size_t srcDataBytes);
    bool IsValid() const noexcept;
    std::vector<uint8_t, _AllocatorType>& GetSoundData() noexcept;
    const std::vector<uint8_t, _AllocatorType>& GetSoundData() const noexcept;
    int32_t GetBitsPerSample() const noexcept;
    int32_t GetChannels() const noexcept;
    int32_t GetSamplingRate() const noexcept;

/* @section Private method */
private:
    ov_callbacks MakeCustomIOCallback() const noexcept;
    unsigned long DecodeOggVorbis(OggVorbis_File* oggVorbisFile, uint8_t* destDecodeBuffer, unsigned long bufferSize, unsigned long channels);

/* @section Private variable */
private:
    std::vector<uint8_t, _AllocatorType> m_soundData;
    int32_t m_bitsPerSample;
    int32_t m_channels;
    int32_t m_samplingRate;
};

inline detail::OggVorbisFileStream::OggVorbisFileStream(const uint8_t* srcData, size_t srcDataBytes) noexcept :
    srcData(srcData),
    srcDataIter(srcData),
    srcDataBytes(srcDataBytes)
{
}

inline size_t detail::OggVorbisFileStream::Read(void* buffer, size_t elementSize, size_t elementCount, void* stream)
{
    OggVorbisFileStream* castedStream = reinterpret_cast<OggVorbisFileStream*>(stream);
    
    size_t bytes = elementSize * elementCount;
    if (castedStream->srcDataIter + bytes > castedStream->srcData + castedStream->srcDataBytes)
    {
        bytes = castedStream->srcData + castedStream->srcDataBytes - castedStream->srcDataIter;
    }

    memcpy(buffer, castedStream->srcDataIter, bytes);
    castedStream->srcDataIter += bytes;

    return bytes;
}

inline int detail::OggVorbisFileStream::Seek(void* stream, ogg_int64_t offset, int origin)
{
    OggVorbisFileStream* castedStream = reinterpret_cast<OggVorbisFileStream*>(stream);

    if (origin == SEEK_CUR)
    {
        castedStream->srcDataIter += offset;
    }
    else if (origin == SEEK_END)
    {
        castedStream->srcDataIter = castedStream->srcData + castedStream->srcDataBytes - offset;
    }
    else if (origin == SEEK_SET)
    {
        castedStream->srcDataIter = castedStream->srcData + offset;
    }
    else
    {
        return -1;
    }

    if (castedStream->srcDataIter < castedStream->srcData)
    {
        castedStream->srcDataIter = castedStream->srcData;
        return -1;
    }

    if (castedStream->srcDataIter > castedStream->srcData + castedStream->srcDataBytes)
    {
        castedStream->srcDataIter = castedStream->srcData + castedStream->srcDataBytes;
        return -1;
    }

    return 0;
}

inline int detail::OggVorbisFileStream::Close(void* stream)
{
    return 0;
}

inline long detail::OggVorbisFileStream::Tell(void* stream)
{
    const OggVorbisFileStream* castedStream = reinterpret_cast<OggVorbisFileStream*>(stream);
    return castedStream->srcDataIter - castedStream->srcData;
}

template <typename _AllocatorType>
inline OggVorbisAudioImporter<_AllocatorType>::OggVorbisAudioImporter() noexcept :
    m_bitsPerSample(0),
    m_channels(0),
    m_samplingRate(0)
{
}

template <typename _AllocatorType>
inline OggVorbisAudioImporter<_AllocatorType>::OggVorbisAudioImporter(const uint8_t* srcData, std::size_t srcDataBytes) :
    OggVorbisAudioImporter()
{
    this->Import(srcData, srcDataBytes);
}

template <typename _AllocatorType>
inline bool OggVorbisAudioImporter<_AllocatorType>::Import(const uint8_t* srcData, std::size_t srcDataBytes)
{
    if (VerifyFormat(srcData, srcDataBytes) == false)
    {
        return false;
    }

    detail::OggVorbisFileStream fileStream(srcData, srcDataBytes);
    ov_callbacks ovCallbacks = this->MakeCustomIOCallback();

    OggVorbis_File oggVorbisFile;
    auto errorCode = ov_open_callbacks(reinterpret_cast<void*>(&fileStream), &oggVorbisFile, nullptr, -1, ovCallbacks);
    if (errorCode != 0)
    {
        Log(LogLevel::Warning, "Failed to invoke ov_open_callbacks. (Code: %d)", errorCode);
        return false;
    }

    const vorbis_info* vorbisInfo = ov_info(&oggVorbisFile, -1);
    if (vorbisInfo != nullptr)
    {
        m_samplingRate = vorbisInfo->rate;
        m_channels = vorbisInfo->channels;
        m_bitsPerSample = 16; // ogg vorbis is always 16 bit.

        int32_t bufferSize = ov_pcm_total(&oggVorbisFile, -1) * 2 * m_channels;
        m_soundData.resize(bufferSize);
        DecodeOggVorbis(&oggVorbisFile, &m_soundData[0], bufferSize, vorbisInfo->channels);
    }

    return true;
}

template <typename _AllocatorType>
inline bool OggVorbisAudioImporter<_AllocatorType>::IsValid() const noexcept
{
    return m_soundData.size() > 0;
}

template <typename _AllocatorType>
inline bool OggVorbisAudioImporter<_AllocatorType>::VerifyFormat(const uint8_t* srcData, std::size_t srcDataBytes)
{
    if (srcDataBytes < 16)
    {
        return false;
    }

    return true;
}

template <typename _AllocatorType>
inline std::vector<uint8_t, _AllocatorType>& OggVorbisAudioImporter<_AllocatorType>::GetSoundData() noexcept
{
    return m_soundData;
}

template <typename _AllocatorType>
inline const std::vector<uint8_t, _AllocatorType>& OggVorbisAudioImporter<_AllocatorType>::GetSoundData() const noexcept
{
    return m_soundData;
}

template <typename _AllocatorType>
inline int32_t OggVorbisAudioImporter<_AllocatorType>::GetBitsPerSample() const noexcept
{
    return m_bitsPerSample;
}

template <typename _AllocatorType>
inline int32_t OggVorbisAudioImporter<_AllocatorType>::GetChannels() const noexcept
{
    return m_channels;
}

template <typename _AllocatorType>
inline int32_t OggVorbisAudioImporter<_AllocatorType>::GetSamplingRate() const noexcept
{
    return m_samplingRate;
}

template <typename _AllocatorType>
inline ov_callbacks OggVorbisAudioImporter<_AllocatorType>::MakeCustomIOCallback() const noexcept
{
    ov_callbacks ovCallbacks;

    ovCallbacks.read_func = detail::OggVorbisFileStream::Read;
    ovCallbacks.seek_func = detail::OggVorbisFileStream::Seek;
    ovCallbacks.close_func = detail::OggVorbisFileStream::Close;
    ovCallbacks.tell_func = detail::OggVorbisFileStream::Tell;

    return ovCallbacks;
}

template <typename _AllocatorType>
inline unsigned long OggVorbisAudioImporter<_AllocatorType>::DecodeOggVorbis(OggVorbis_File* oggVorbisFile, uint8_t* destDecodeBuffer, unsigned long bufferSize, unsigned long channels)
{
	int current_section;

	unsigned long bytesDone = 0;
	while (true)
	{
        long decodeSize = ov_read(oggVorbisFile, reinterpret_cast<char*>(destDecodeBuffer + bytesDone), bufferSize - bytesDone, 0, 2, 1, &current_section);
		if (decodeSize > 0)
		{
			bytesDone += decodeSize;
            if (bytesDone >= bufferSize)
            {
				break;
            }
		}
		else
		{
			break;
		}
	}

	// Mono, Stereo and 4-Channel files decode into the same channel order as WAVEFORMATEXTENSIBLE,
	// however 6-Channels files need to be re-ordered
	if (channels == 6)
	{		
        uint16_t* samples = (uint16_t*)destDecodeBuffer;
		for (unsigned long ulSamples = 0; ulSamples < (bufferSize >> 1); ulSamples += 6)
		{
			// WAVEFORMATEXTENSIBLE Order : FL, FR, FC, LFE, RL, RR
			// OggVorbis Order            : FL, FC, FR,  RL, RR, LFE
			std::swap(samples[ulSamples+1], samples[ulSamples+2]);
			std::swap(samples[ulSamples+3], samples[ulSamples+5]);
			std::swap(samples[ulSamples+4], samples[ulSamples+5]);
		}
	}

	return bytesDone;
}

} /* namespace tgon */