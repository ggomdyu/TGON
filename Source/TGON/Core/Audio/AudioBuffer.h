/**
 * @file    AudioBuffer.h
 * @author  ggomdyu
 * @since   04/30/2018
 * @see     https://www.openal.org/documentation/OpenAL_Programmers_Guide.pdf
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <vector>
#include <cstdint>
#include <memory>
#include <string>

#include "Core/Platform/Config.h"
#if TGON_PLATFORM_MACOS
#   import <OpenAL/al.h>
#else
#   include <al.h>
#endif

#include "AudioBufferType.h"

namespace tgon
{

class AudioBuffer final :
    private boost::noncopyable
{
/**@section Constructor */
public:
    AudioBuffer();

    /**
     * @brief   Reads a audio data from the path specified by filePath.
     * @param [in] filePath     A path to the audio file
     */
    explicit AudioBuffer(const std::string& filePath);

    /**
     * @brief   Reads a audio file data from memory.
     * @param [in] filePath     A file path of the audio source
     * @param [in] srcData      A pointer to audio data
     * @param [in] srcDataBytes The bytes of the audio data
     */
    AudioBuffer(const std::string& filePath, const uint8_t* srcData, std::size_t srcDataBytes);

    AudioBuffer(AudioBuffer&& rhs) = default;

/**@section Operator */
public:
    AudioBuffer& operator=(AudioBuffer&& rhs) = default;

/**@section Destructor */
public:
    ~AudioBuffer();

/**@section Method */
public:
    /**
     * @brief   Reads a sound data from the path specified by filePath.
     * @param [in] filePath     The file path of the audio file
     */
    bool Initialize(const std::string& filePath);

    /**
     * @brief   Reads a audio file data from memory.
     * @param [in] filePath     The file path of the audio file
     * @param [in] srcData      The pointer to the audio data
     * @param [in] srcDataBytes The bytes of the audio data
     * @param [in] audioFormat  The format of the audio
     */
    bool Initialize(const std::string& filePath, const uint8_t* srcData, std::size_t srcDataBytes, AudioFormat audioFormat);
    
    /**
     * @brief   Reads a audio file data from memory.
     * @param [in] filePath     The file path of the audio source
     * @param [in] srcData      The pointer to the audio data
     * @param [in] srcDataBytes The bytes of the audio data
     */
    bool Initialize(const std::string& filePath, const uint8_t* srcData, std::size_t srcDataBytes);

    bool IsValid() const noexcept;

    /**@brief   Gets the raw data of the sound. */
    const std::vector<uint8_t>& GetSoundData() const noexcept;

    /**@brief   Gets bits per sample. */
    int32_t GetBitsPerSample() const noexcept;

    /**@brief   Gets the count of sound channel. */
    int32_t GetChannels() const noexcept;

    /**@brief   Gets the sampling rate of the sound. */
    int32_t GetSamplingRate() const noexcept;

    ALenum GetALFormat() const noexcept;

    /**@brief   Gets the id of ALBuffer that stores sound data. */
    ALuint GetALBufferId() const noexcept;
    
    /**@brief   Gets the file path saved at loading time. */
    const std::string& GetFilePath() const noexcept;

private:
    bool ParseData(const uint8_t* srcData, std::size_t srcDataBytes, AudioFormat audioFormat);

    bool InitializeALBuffer(const std::vector<uint8_t>& audioData, ALenum alFormat, int32_t samplingRate);

/**@section Variable */
private:
    std::string m_filePath;
    std::vector<uint8_t> m_audioData;
    int32_t m_bitsPerSample;
    int32_t m_channels;
    int32_t m_samplingRate;
    ALenum m_alFormat;
    ALuint m_alBufferId;
};

} /* namespace tgon */
