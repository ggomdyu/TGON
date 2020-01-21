#include "PrecompiledHeader.h"

#include <stb_vorbis.c>

#include "VorbisAudioDecoder.h"

namespace tgon
{

std::optional<VorbisAudioDecoder> VorbisAudioDecoder::Create(const gsl::span<const std::byte>& fileData)
{
    if (IsVorbis(fileData) == false)
    {
        return {};
    }
return {};
//    // vorbis's each sample is 16-bit.
//    int32_t bitsPerSample = 16;
//
//    short* audioData = nullptr;
//    int bitsPerSample = 0;
//    int channels = 0;
//    int samplingRate = 0;
//    auto audioDataBytes = stb_vorbis_decode_memory(reinterpret_cast<const unsigned char*>(fileData.data()), static_cast<int>(fileData.size()), &channels, &samplingRate, &audioData) * 4;
//    m_audioData.reset(reinterpret_cast<std::byte*>(audioData));
//    m_audioDataBytes = audioDataBytes;
//
//    return VorbisVorbisAudioDecoder();
}

bool VorbisAudioDecoder::IsVorbis(const gsl::span<const std::byte>& fileData)
{
    if (fileData.size() < 35)
    {
        return false;
    }
    
    return !strncmp(reinterpret_cast<const char*>(&fileData[0]), "OggS", 4) && !strncmp(reinterpret_cast<const char*>(&fileData[29]), "vorbis", 6);
}

} /* namespace tgon */
