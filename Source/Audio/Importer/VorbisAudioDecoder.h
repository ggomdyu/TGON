#pragma once

#include <gsl/span>
#include <optional>

#include "AudioDecoder.h"

namespace tg
{

class VorbisAudioDecoder final :
    public AudioDecoder
{
public:
    TGON_DECLARE_RTTI(VorbisAudioDecoder)

/**@section Constructor */
public:
    using AudioDecoder::AudioDecoder;

/**@section Method */
public:
    static std::optional<VorbisAudioDecoder> Create(const gsl::span<const std::byte>& fileData);
    static bool IsVorbis(const gsl::span<const std::byte>& fileData);
};

}
