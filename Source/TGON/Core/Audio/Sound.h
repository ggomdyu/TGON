/**
 * @filename    WAVImporter.h
 * @author      ggomdyu
 * @since       04/20/2018
 * @see         https://sites.google.com/site/musicgapi/technical-documents/wav-file-format#list
 *              http://www-mmsp.ece.mcgill.ca/Documents/AudioFormats/WAVE/WAVE.html
 */

#pragma once
#include <vector>
#include <cstdint>

namespace tgon
{

class Sound
{
public:
    /**
     * @brief                   Reads a sound data from the given path specified by filePath.
     * @param [in] filePath     The file path of image
     */
    explicit Sound(const std::string& filePath);

    /**
     * @brief                   Reads a sound file data from memory.
     * @param [in] filePath     The file path of image file
     * @param [in] srcData      The pointer to image data
     * @param [in] srcDataBytes The bytes of image data
     * @param [in] imageFormat  The format of image
     */
    Sound(const std::string& filePath, const uint8_t* srcData, std::size_t srcDataBytes);
    
    /**
     * @brief                   Reads a sound file data from memory.
     * @param [in] filePath     The file path of image source
     * @param [in] srcData      The pointer to image data
     * @param [in] srcDataBytes The bytes of image data
     */
    Sound(const std::string& filePath, const uint8_t* srcData, std::size_t srcDataBytes);

public:
    void Play(float volume, bool isLooping);
    void Stop();
    void Pause();
    void Resume();

    void SetVolume(float volume);
    float GetVolume();
    float GetProgress() const;

private:
};

} /* namespace tgon */