/**
 * @filename    OGGImporter.h
 * @author      ggomdyu
 * @since       04/20/2018
 * @see         https://sites.google.com/site/musicgapi/technical-documents/wav-file-format#list
 *              http://www-mmsp.ece.mcgill.ca/Documents/AudioFormats/WAVE/WAVE.html
 */

#pragma once
#include <vector>
#include <cstdint>

#include <vorbis/vorbisfile.h>
#include <ogg/ogg.h>

#include "Core/Debug/Log.h"

namespace tgon
{

class OggVorbisImporter
{
    struct CustomFileStream final
    {
    /* @section Public constructor */
    public:
        CustomFileStream(const uint8_t* srcData, size_t srcDataBytes) noexcept;

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

/* @section Public constructor */
public:
    OggVorbisImporter() noexcept;
    OggVorbisImporter(const uint8_t* srcData, std::size_t srcDataBytes);

/* @section Public method */
public:
    /* @brief   Verifies the importing file is exactly WAV. */
    static bool VerifyFormat(const uint8_t* srcData, std::size_t srcDataBytes);
    bool Import(const uint8_t* srcData, std::size_t srcDataBytes);
    bool IsValid() const noexcept;
    std::vector<uint8_t>& GetSoundData() noexcept;
    const std::vector<uint8_t>& GetSoundData() const noexcept;
    int32_t GetBitsPerSample() const noexcept;
    int32_t GetChannels() const noexcept;
    int32_t GetSamplingRate() const noexcept;

/* @section Private method */
private:
    ov_callbacks MakeCustomIOCallback() const noexcept;
    unsigned long DecodeOggVorbis(OggVorbis_File* oggVorbisFile, uint8_t* destDecodeBuffer, unsigned long bufferSize, unsigned long channels);

/* @section Private variable */
private:
    std::vector<uint8_t> m_soundData;
    int32_t m_bitsPerSample;
    int32_t m_channels;
    int32_t m_samplingRate;
};

OggVorbisImporter::CustomFileStream::CustomFileStream(const uint8_t* srcData, size_t srcDataBytes) noexcept :
    srcData(srcData),
    srcDataIter(srcData),
    srcDataBytes(srcDataBytes)
{
}

inline size_t OggVorbisImporter::CustomFileStream::Read(void* buffer, size_t elementSize, size_t elementCount, void* stream)
{
    CustomFileStream* castedStream = reinterpret_cast<CustomFileStream*>(stream);
    
    size_t bytes = elementSize * elementCount;
    if (castedStream->srcDataIter + bytes > castedStream->srcData + castedStream->srcDataBytes)
    {
        bytes = castedStream->srcData + castedStream->srcDataBytes - castedStream->srcDataIter;
    }

    memcpy(buffer, castedStream->srcDataIter, bytes);
    castedStream->srcDataIter += bytes;

    return bytes;
}

inline int OggVorbisImporter::CustomFileStream::Seek(void* stream, ogg_int64_t offset, int origin)
{
    CustomFileStream* castedStream = reinterpret_cast<CustomFileStream*>(stream);

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

inline int OggVorbisImporter::CustomFileStream::Close(void* stream)
{
    return 0;
}

inline long OggVorbisImporter::CustomFileStream::Tell(void* stream)
{
    const CustomFileStream* castedStream = reinterpret_cast<CustomFileStream*>(stream);
    return castedStream->srcDataIter - castedStream->srcData;
}

inline OggVorbisImporter::OggVorbisImporter() noexcept :
    m_bitsPerSample(0),
    m_channels(0),
    m_samplingRate(0)
{
}

inline OggVorbisImporter::OggVorbisImporter(const uint8_t* srcData, std::size_t srcDataBytes) :
    OggVorbisImporter()
{
    this->Import(srcData, srcDataBytes);
}

inline bool OggVorbisImporter::Import(const uint8_t* srcData, std::size_t srcDataBytes)
{
    if (VerifyFormat(srcData, srcDataBytes) == false)
    {
        return false;
    }

    CustomFileStream fileStream(srcData, srcDataBytes);
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

inline bool OggVorbisImporter::IsValid() const noexcept
{
    return m_soundData.size() > 0;
}

inline bool OggVorbisImporter::VerifyFormat(const uint8_t* srcData, std::size_t srcDataBytes)
{
    if (srcDataBytes < 16)
    {
        return false;
    }

    return true;
}

inline std::vector<uint8_t>& OggVorbisImporter::GetSoundData() noexcept
{
    return m_soundData;
}

inline const std::vector<uint8_t>& OggVorbisImporter::GetSoundData() const noexcept
{
    return m_soundData;
}

inline int32_t OggVorbisImporter::GetBitsPerSample() const noexcept
{
    return m_bitsPerSample;
}

inline int32_t OggVorbisImporter::GetChannels() const noexcept
{
    return m_channels;
}

inline int32_t OggVorbisImporter::GetSamplingRate() const noexcept
{
    return m_samplingRate;
}

inline ov_callbacks OggVorbisImporter::MakeCustomIOCallback() const noexcept
{
    ov_callbacks ovCallbacks;

    ovCallbacks.read_func = CustomFileStream::Read;
    ovCallbacks.seek_func = CustomFileStream::Seek;
    ovCallbacks.close_func = CustomFileStream::Close;
    ovCallbacks.tell_func = CustomFileStream::Tell;

    return ovCallbacks;
}

inline unsigned long OggVorbisImporter::DecodeOggVorbis(OggVorbis_File* oggVorbisFile, uint8_t* destDecodeBuffer, unsigned long bufferSize, unsigned long channels)
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