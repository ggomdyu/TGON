/**
 * @file    WavAudioDecoder.h
 * @author  ggomdyu
 * @since   04/20/2018
 */

#pragma once
#include <gsl/span>

#include "AudioDecoder.h"

namespace tgon
{

class WavAudioDecoder final :
    public AudioDecoder
{
public:
    TGON_DECLARE_RTTI(WavAudioDecoder)
    
/**@section Constructor */
public:
    static std::optional<WavAudioDecoder> Create(const gsl::span<const std::byte>& fileData);
    
/**@section Method */
public:
    static bool IsWav(const gsl::span<const std::byte>& fileData);
};

} /* namespace tgon */
