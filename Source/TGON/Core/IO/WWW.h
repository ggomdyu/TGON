/**
 * @filename    WWW.h
 * @author      ggomdyu
 * @since       04/09/2017
 */

#pragma once
#include <string>
#include <cstdint>
#include <vector>

namespace tgon
{

class WWW
{
private:
    using Bytes = std::vector<uint8_t>;

/**
 * @section Ctor/Dtor
 */
public:
    explicit WWW(const char* url);
    explicit WWW(const std::string& url);

/**
 * @section Get methods
 */
public:
    const typename Bytes::value_type* GetBytes() const;
    typename Bytes::size_type GetDownloadedSize() const;
    const std::string& GetURL() const;

private:
    const Bytes DownloadFromURL(const char* url) const;

private:
    std::string m_url;
    Bytes m_downloadedBytes;
};

} /* namespace tgon */