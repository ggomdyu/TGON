/**
 * @file    VorbisAudioImporter.h
 * @author  ggomdyu
 * @since   04/20/2018
 */
 
#pragma once
#include "AudioImporter.h"

namespace tgon
{

class VorbisAudioImporter :
    public AudioImporter
{
/**@section Method */
public:
    static bool IsExactFormat(const gsl::span<const std::byte>& fileData);
    bool Initialize(const gsl::span<const std::byte>& fileData) override;
};

} /* namespace tgon */
