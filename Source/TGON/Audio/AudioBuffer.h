/**
 * @file    AudioBuffer.h
 * @author  ggomdyu
 * @since   04/30/2018
 * @see     https://www.openal.org/documentation/OpenAL_Programmers_Guide.pdf
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <cstdint>
#include <memory>
#include <string>

#include "Platform/Config.h"
#if TGON_PLATFORM_MACOS
#   import <OpenAL/al.h>
#else
#   include <al.h>
#endif

#include "AudioBufferType.h"

namespace tgon
{

class TGON_API AudioBuffer
{
/**@section Constructor */
public:
    AudioBuffer();

    /**
     * @brief   Reads the audio data from the directory specified by filePath.
     * @param [in] filePath     The file path of the audio file
     */
    explicit AudioBuffer(const std::string& filePath);

    /**
     * @brief   Reads the audio data from the file memory.
     * @param [in] fileData         The pointer to audio data
     * @param [in] fileDataBytes    The bytes of the audio data
     */
    AudioBuffer(const uint8_t* fileData, std::size_t fileDataBytes);

    AudioBuffer(const AudioBuffer& rhs) = delete;
    AudioBuffer(AudioBuffer&& rhs) = default;

/**@section Operator */
public:
    AudioBuffer& operator=(const AudioBuffer& rhs) = delete;
    AudioBuffer& operator=(AudioBuffer&& rhs) = default;

/**@section Destructor */
public:
    ~AudioBuffer();

/**@section Method */
public:
    /**
     * @brief   Reads sound data from the path specified by filePath.
     * @param [in] filePath     The file path of the audio file
     */
    bool SetAudioData(const std::string& filePath);

    /**
     * @brief   Reads audio file data from memory.
     * @param [in] fileData         The pointer to the audio data
     * @param [in] fileDataBytes    The bytes of the audio data
     * @param [in] audioFormat      The format of the audio
     */
    bool SetAudioData(const uint8_t* fileData, std::size_t fileDataBytes, AudioFormat audioFormat);
    
    /**
     * @brief   Reads audio file data from memory.
     * @param [in] fileData         The pointer to the audio data
     * @param [in] fileDataBytes    The bytes of the audio data
     */
    bool SetAudioData(const uint8_t* fileData, std::size_t fileDataBytes);

    bool IsValid() const noexcept;
    const uint8_t* GetAudioData() const noexcept;
    size_t GetAudioDataBytes() const noexcept;
    int32_t GetBitsPerSample() const noexcept;
    int32_t GetChannels() const noexcept;
    int32_t GetSamplingRate() const noexcept;
    ALenum GetALFormat() const noexcept;

    /**@brief   Gets the id of ALBuffer that stores sound data. */
    ALuint GetALBufferId() const noexcept;
    
    /**@brief   Gets the file path saved at loading time. */
    const std::string& GetFilePath() const noexcept;

private:
    bool Decode(const uint8_t* fileData, std::size_t fileDataBytes, AudioFormat audioFormat);

/**@section Variable */
private:
    std::string m_filePath;
    std::unique_ptr<uint8_t[]> m_audioData;
    ALuint m_alBufferId;
    size_t m_audioDataBytes;
    int32_t m_bitsPerSample;
    int32_t m_channels;
    int32_t m_samplingRate;
    ALenum m_alFormat;
};

}
