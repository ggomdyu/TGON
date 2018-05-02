/**
 * @filename    Audio.h
 * @author      ggomdyu
 * @since       04/30/2018
 */

#pragma once
#include <vector>
#include <cstdint>

#include "AudioType.h"

namespace tgon
{

class Audio3D
{
public:
    /**
     * @brief                   Reads a sound data from the path specified by filePath.
     * @param [in] filePath     The file path of image
     */
    explicit Audio3D(const std::string& filePath);

    /**
     * @brief                   Reads a sound file data from memory.
     * @param [in] filePath     The file path of image file
     * @param [in] srcData      The pointer to image data
     * @param [in] srcDataBytes The bytes of image data
     * @param [in] imageFormat  The format of image
     */
    Audio3D(const std::string& filePath, const uint8_t* srcData, std::size_t srcDataBytes, AudioFormat audioFormat);
    
    /**
     * @brief                   Reads a sound file data from memory.
     * @param [in] filePath     The file path of image source
     * @param [in] srcData      The pointer to image data
     * @param [in] srcDataBytes The bytes of image data
     */
    Audio3D(const std::string& filePath, const uint8_t* srcData, std::size_t srcDataBytes);

    Audio3D(const Audio3D& rhs) = default;
    Audio3D(Audio3D&& rhs);

/* @section Private constructor */
private:
    Audio3D();

public:
    void Play(float volume, bool isLooping);
    void Stop();
    void Pause();
    void Resume();

    void SetVolume(float volume);
    float GetVolume();
    float GetProgress() const;

private:
    std::vector<uint8_t> m_soundData;
    int32_t m_bitsPerSample;
    int32_t m_channels;
    int32_t m_samplingRate;
};

} /* namespace tgon */