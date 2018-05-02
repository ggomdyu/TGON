#include "PrecompiledHeader.pch"

#include "Audio.h"
#include "AudioUtility.h"
#include "Importer/Wav/WavAudioImporter.h"
#include "Importer/OggVorbis/OggVorbisAudioImporter.h"

namespace tgon
{

Audio3D::Audio3D(const std::string& filePath) :
    Audio3D([&]() -> Audio3D
    {
        FILE* file = fopen(filePath.c_str(), "rb");
        if (file == nullptr)
        {
            return {};
        }

        // Read the image data from file.
        std::vector<uint8_t> audioData;
        {
            fseek(file, 0, SEEK_END);
            long fileSize = ftell(file);
            fseek(file, 0, SEEK_SET);

            audioData.resize(fileSize + 1);
            fread(audioData.data(), 1, fileSize, file);
        };
        fclose(file);

        std::size_t extensionOffset = filePath.rfind('.') + 1;
        return Audio3D(filePath, audioData.data(), audioData.size(), ConvertStringToAudioFormat(&filePath[0] + extensionOffset, filePath.size() - extensionOffset));
    } ())
{
}

Audio3D::Audio3D(const std::string& filePath, const uint8_t* srcData, std::size_t srcDataBytes, AudioFormat audioFormat) :
    Audio3D()
{
    switch (audioFormat)
    {
    case AudioFormat::Wav:
        {
            WavAudioImporter<> importer(srcData, srcDataBytes);
            {
                m_soundData = std::move(importer.GetSoundData());
                m_bitsPerSample = importer.GetBitsPerSample();
                m_channels = importer.GetChannels();
                m_samplingRate = importer.GetSamplingRate();
            }
        }
        break;

    case AudioFormat::OggVorbis:
        {
            OggVorbisAudioImporter<> importer(srcData, srcDataBytes);
            {
                m_soundData = std::move(importer.GetSoundData());
                m_bitsPerSample = importer.GetBitsPerSample();
                m_channels = importer.GetChannels();
                m_samplingRate = importer.GetSamplingRate();
            }
        }
        break;

    default:
        break;
    }
}

Audio3D::Audio3D(const std::string& filePath, const uint8_t* srcData, std::size_t srcDataBytes)
{
}

Audio3D::Audio3D(Audio3D&& rhs)
{
}

Audio3D::Audio3D()
{
}

} /* namespace tgon */