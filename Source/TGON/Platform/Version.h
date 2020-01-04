/**
 * @file    Version.h
 * @author  ggomdyu
 * @since   11/17/2019
 */

#pragma once
#include <optional>
#include <string>

namespace tgon
{

struct Version final
{
/**@section Constructor */
public:
    constexpr Version(int32_t major, int32_t minor, int32_t build, int32_t revision) noexcept;
    constexpr Version(int32_t major, int32_t minor, int32_t build) noexcept;
    constexpr Version(int32_t major, int32_t minor) noexcept;
    
/**@section Operator */
public:
    constexpr bool operator==(const Version& rhs) const noexcept;
    constexpr bool operator!=(const Version& rhs) const noexcept;
    constexpr bool operator<(const Version& rhs) const noexcept;
    constexpr bool operator>(const Version& rhs) const noexcept;
    constexpr bool operator<=(const Version& rhs) const noexcept;
    constexpr bool operator>=(const Version& rhs) const noexcept;

/**@section Method */
public:
    constexpr int32_t GetMajor() const noexcept;
    constexpr int32_t GetMinor() const noexcept;
    constexpr int32_t GetBuild() const noexcept;
    constexpr int32_t GetRevision() const noexcept;
    constexpr int16_t GetMajorRevision() const noexcept;
    constexpr int16_t GetMinorRevision() const noexcept;
    constexpr int32_t GetHashCode() const noexcept;
    constexpr int32_t CompareTo(const Version& rhs) const noexcept;
    std::optional<std::string> ToString() const;
    std::optional<std::string> ToString(int32_t fieldCount) const;

private:
    static void AppendPositiveNumber(int32_t num, std::string* str);

/**@section Variable */
private:
    int32_t m_major = 0;
    int32_t m_minor = 0;
    int32_t m_build = -1;
    int32_t m_revision = -1;
};

constexpr Version::Version(int32_t major, int32_t minor, int32_t build, int32_t revision) noexcept :
    m_major(major),
    m_minor(minor),
    m_build(build),
    m_revision(revision)
{
}

constexpr Version::Version(int32_t major, int32_t minor, int32_t build) noexcept :
    m_major(major),
    m_minor(minor),
    m_build(build)
{
}

constexpr Version::Version(int32_t major, int32_t minor) noexcept :
    m_major(major),
    m_minor(minor)
{
}

constexpr bool Version::operator==(const Version& rhs) const noexcept
{
    return this->CompareTo(rhs) == 0;
}

constexpr bool Version::operator!=(const Version& rhs) const noexcept
{
    return !this->operator==(rhs);
}

constexpr bool Version::operator<(const Version& rhs) const noexcept
{
    return this->CompareTo(rhs) < 0;
}

constexpr bool Version::operator<=(const Version& rhs) const noexcept
{
    return this->CompareTo(rhs) <= 0;
}

constexpr bool Version::operator>(const Version& rhs) const noexcept
{
    return rhs < *this;
}

constexpr bool Version::operator>=(const Version& rhs) const noexcept
{
    return rhs <= *this;
}

constexpr int32_t Version::GetMajor() const noexcept
{
    return m_major;
}

constexpr int32_t Version::GetMinor() const noexcept
{
    return m_minor;
}

constexpr int32_t Version::GetBuild() const noexcept
{
    return m_build;
}

constexpr int32_t Version::GetRevision() const noexcept
{
    return m_revision;
}

constexpr int16_t Version::GetMajorRevision() const noexcept
{
    return m_revision >> 16;
}

constexpr int16_t Version::GetMinorRevision() const noexcept
{
    return m_revision & 0xffff;
}

constexpr int32_t Version::GetHashCode() const noexcept
{
    int32_t accumulator = 0;
    accumulator |= (m_major & 0x0000000F) << 28;
    accumulator |= (m_minor & 0x000000FF) << 20;
    accumulator |= (m_build & 0x000000FF) << 12;
    accumulator |= (m_revision & 0x00000FFF);

    return accumulator;
}

constexpr int32_t Version::CompareTo(const Version& rhs) const noexcept
{
    if (m_major != rhs.m_major)
    {
        if (m_major > rhs.m_major)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }

    if (m_minor != rhs.m_minor)
    {
        if (m_minor > rhs.m_minor)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }

    if (m_build != rhs.m_build)
    {
        if (m_build > rhs.m_build)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }

    if (m_revision != rhs.m_revision)
    {
        if (m_revision > rhs.m_revision)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }

    return 0;
}

inline std::optional<std::string> Version::ToString() const
{
    if (m_build == -1)
    {
        return this->ToString(2);
    }
    
    if (m_revision == -1)
    {
        return this->ToString(3);
    }

    return this->ToString(4);
}

inline std::optional<std::string> Version::ToString(int32_t fieldCount) const
{
    switch (fieldCount)
    {
    case 0:
        return std::string();
    
    case 1:
        return std::to_string(m_major);

    case 2:
        {
            std::string ret;
            this->AppendPositiveNumber(m_major, &ret);
            ret.push_back('.');
            this->AppendPositiveNumber(m_minor, &ret);
            return ret;
        }

    default:
        {
            if (m_build == -1)
            {
                return {};
            }

            if (fieldCount == 3)
            {
                std::string ret;
                this->AppendPositiveNumber(m_major, &ret);
                ret.push_back('.');
                this->AppendPositiveNumber(m_minor, &ret);
                ret.push_back('.');
                this->AppendPositiveNumber(m_build, &ret);
                return ret;
            }

            if (m_revision == -1)
            {
                return {};
            }

            if (fieldCount == 4)
            {
                std::string ret;
                this->AppendPositiveNumber(m_major, &ret);
                ret.push_back('.');
                this->AppendPositiveNumber(m_minor, &ret);
                ret.push_back('.');
                this->AppendPositiveNumber(m_build, &ret);
                ret.push_back('.');
                this->AppendPositiveNumber(m_revision, &ret);
                return ret;
            }

            return {};
        }
    }
}

inline void Version::AppendPositiveNumber(int32_t num, std::string* str)
{
    int32_t index = static_cast<int32_t>(str->length());
    int32_t reminder;
    do
    {
        reminder = num % 10;
        num = num / 10;
        str->push_back('0' + static_cast<char>(reminder));
    } while (num > 0);
}

} /* namespace tgon */
