#pragma once

class Texture2D
{
public:
    explicit Texture2D(const char* imageFilePath);

private:
    uint8_t* m_textureBits;
};
