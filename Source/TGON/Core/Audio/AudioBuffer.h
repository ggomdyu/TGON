/**
 * @filename    Audio.h
 * @author      ggomdyu
 * @since       04/30/2018
 * @see         https://www.openal.org/documentation/OpenAL_Programmers_Guide.pdf
 */

#pragma once
#include <vector>
#include <cstdint>
#include <memory>
#if TGON_PLATFORM_MACOS
#   import <OpenAL/al.h>
#else
#   include <al.h>
#endif

#include "AudioBufferType.h"

namespace tgon
{

class AudioBuffer final
{
/* @section Public constructor */
public:
    AudioBuffer();

    /**
     * @brief                   Reads a audio data from the path specified by filePath.
     * @param [in] filePath     The file path of audio
     */
    explicit AudioBuffer(const std::string& filePath);

    /**
     * @brief                   Reads a audio file data from memory.
     * @param [in] filePath     The file path of audio file
     * @param [in] srcData      The pointer to audio data
     * @param [in] srcDataBytes The bytes of audio data
     * @param [in] audioFormat  The format of audio
     */
    AudioBuffer(const std::string& filePath, const uint8_t* srcData, std::size_t srcDataBytes, AudioFormat audioFormat);
    
    /**
     * @brief                   Reads a audio file data from memory.
     * @param [in] filePath     The file path of audio source
     * @param [in] srcData      The pointer to audio data
     * @param [in] srcDataBytes The bytes of audio data
     */
    AudioBuffer(const std::string& filePath, const uint8_t* srcData, std::size_t srcDataBytes);

    AudioBuffer(const AudioBuffer& rhs) = delete;
    AudioBuffer(AudioBuffer&& rhs) = default;

/* @section Public operator */
public:
    AudioBuffer& operator=(const AudioBuffer& rhs) = delete;
    AudioBuffer& operator=(AudioBuffer&& rhs) = default;

/* @section Public destructor */
public:
    ~AudioBuffer();

/* @section Public method */
public:
    /**
     * @brief                   Reads a sound data from the path specified by filePath.
     * @param [in] filePath     The file path of audio
     */
    bool Initialize(const std::string& filePath);

    /**
     * @brief                   Reads a audio file data from memory.
     * @param [in] filePath     The file path of audio file
     * @param [in] srcData      The pointer to audio data
     * @param [in] srcDataBytes The bytes of audio data
     * @param [in] audioFormat  The format of audio
     */
    bool Initialize(const std::string& filePath, const uint8_t* srcData, std::size_t srcDataBytes, AudioFormat audioFormat);
    
    /**
     * @brief                   Reads a audio file data from memory.
     * @param [in] filePath     The file path of audio source
     * @param [in] srcData      The pointer to audio data
     * @param [in] srcDataBytes The bytes of audio data
     */
    bool Initialize(const std::string& filePath, const uint8_t* srcData, std::size_t srcDataBytes);

    bool IsValid() const noexcept;

    /* @brief   Gets the raw data of sound. */
    const std::vector<uint8_t>& GetSoundData() const noexcept;

    /* @brief   Gets bits per sample. */
    int32_t GetBitsPerSample() const noexcept;

    /* @brief   Gets count of sound channel. */
    int32_t GetChannels() const noexcept;

    /* @brief   Gets sampling rate of sound. */
    int32_t GetSamplingRate() const noexcept;

    ALenum GetALFormat() const noexcept;

    /* @brief   Gets the id of ALBuffer that stores sound data. */
    ALuint GetALBufferId() const noexcept;
    
    /* @brief   Gets the file path saved at loading time. */
    const std::string& GetFilePath() const noexcept;

/* @section Private method */
private:
    bool ParseData(const uint8_t* srcData, std::size_t srcDataBytes, AudioFormat audioFormat);
    bool InitializeALBuffer(const std::vector<uint8_t>& audioData, ALenum alFormat, int32_t samplingRate);

/* @section Private variable */
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
