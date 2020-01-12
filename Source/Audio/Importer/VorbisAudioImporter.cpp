#include "PrecompiledHeader.h"

#include <stb_vorbis.c>

#include "VorbisAudioImporter.h"

namespace tgon
{

bool VorbisAudioImporter::Initialize(const gsl::span<const std::byte>& fileData)
{
    if (IsExactFormat(fileData) == false)
    {
        return false;
    }

    // vorbis's each sample is a 16-bit number.
    m_bitsPerSample = 16;

    short* audioData = nullptr;
    auto audioDataBytes = stb_vorbis_decode_memory(reinterpret_cast<const unsigned char*>(fileData.data()), static_cast<int>(fileData.size()), &m_channels, &m_samplingRate, &audioData) * 4;
    m_audioData.reset(reinterpret_cast<std::byte*>(audioData));
    m_audioDataBytes = audioDataBytes;

    return true;
}

bool VorbisAudioImporter::IsExactFormat(const gsl::span<const std::byte>& fileData)
{
    if (fileData.size() < 16)
    {
        return false;
    }

    return true;
}

} /* namespace tgon */
