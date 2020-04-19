#pragma once

#include <gsl/span>
#include <optional>

#include "AudioDecoder.h"

namespace tg
{

class WavAudioDecoder final :
    public AudioDecoder
{
public:
    TGON_DECLARE_RTTI(WavAudioDecoder)
    
/**@section Constructor */
public:
    using AudioDecoder::AudioDecoder;

/**@section Method */
public:
    static std::optional<WavAudioDecoder> Create(const gsl::span<const std::byte>& fileData);
    static bool IsWav(const gsl::span<const std::byte>& fileData);
};

}
