#include "PrecompiledHeader.h"
#include "WWW.h"

#include <windows.h>

namespace tgon
{

WWW::WWW(const char* url) :
    m_url(url)
{
}

WWW::WWW(const std::string& url) :
    m_url(url)
{
}

const typename WWW::Bytes::value_type* WWW::GetBytes() const
{
    return m_downloadedBytes.data();
}

typename WWW::Bytes::size_type WWW::GetDownloadedSize() const
{
    return m_downloadedBytes.size();
}

const std::string& WWW::GetURL() const
{
    return m_url;
}

const WWW::Bytes WWW::DownloadFromURL(const char* url) const
{
    return {};
}

} /* namespace tgon */