#pragma once

#include <span>
#include <unordered_set>
#include <string>

#include "StringCache.h"
#include "StringTraits.h"

using _Char = char;

namespace tg
{

class String final
{
/**@section Constructor */
public:
    String(const _Char* str);
    String(const _Char* str, int32_t length);
    String(const std::span<const _Char>& str);
    String(char c, int32_t count);

/**@section Operator */
public:
    constexpr bool operator==(const String& rhs) noexcept;
    constexpr bool operator!=(const String& rhs) noexcept;
    constexpr _Char operator[](int32_t index) const noexcept;
    _Char& operator[](int32_t index) noexcept;

/**@section Method */
public:
    //static string Join(string separator, params string[] value);
    //static string Join<T>(string separator, IEnumerable<T> values);
    //static string Join(string separator, string[] value, int32_t startIndex, int32_t count);
    //bool Equals(string value);
    //static bool Equals(string a, string b);
    //void CopyTo(int32_t sourceIndex, const std::span<char>& destination, int32_t destinationIndex, int32_t count);
    //std::unique_ptr<char[]> ToCharArray();
    //char[] ToCharArray(int32_t startIndex, int32_t length);
    //static bool IsNullOrEmpty(const char* value);
    //static bool IsNullOrWhiteSpace(const char* value);
    [[nodiscard]] int32_t GetHashCode() const noexcept;
    [[nodiscard]] int32_t Length() const noexcept;
    //std::vector<String> Split(char[] separator);
    //std::vector<String> Split(char[] separator, int32_t count);
    //std::vector<String> Split(char[] separator, StringSplitOptions options);
    //std::vector<String> Split(char[] separator, int32_t count, StringSplitOptions options);
    //std::vector<String> Split(string[] separator, StringSplitOptions options);
    //std::vector<String> Split(string[] separator, int32_t count, StringSplitOptions options);
    //std::string_view Substring(int32_t startIndex);
    //std::string_view Substring(int32_t startIndex, int32_t length);
    //string Trim(params char[] trimChars);
    //string TrimStart(params char[] trimChars);
    //string TrimEnd(params char[] trimChars);
    //bool IsNormalized();
    //bool IsNormalized(NormalizationForm normalizationForm);
    //string Normalize();
    //string Normalize(NormalizationForm normalizationForm);
    //static int Compare(string strA, string strB);
    //static int Compare(string strA, string strB, bool ignoreCase);
    //static int Compare(string strA, string strB, StringComparison comparisonType);
    //static int Compare(string strA, string strB, int32_t length);
    //static int Compare(string strA, string strB, int32_t length, bool ignoreCase);
    //[[nodiscard]] int32_t CompareTo(const String& str) noexcept;
    //static int CompareOrdinal(string strA, string strB);
    //static int CompareOrdinal(string strA, string strB, bool ignoreCase);
    //bool Contains(string value);
    //bool EndsWith(string value);
    //bool EndsWith(string value, bool ignoreCase);
    //int32_t IndexOf(char c);
    //int32_t IndexOf(char c, int32_t startIndex) const;
    //int32_t IndexOf(char c, int32_t startIndex, int32_t count) const;
    //int32_t IndexOfAny(const std::span<const char>& anyOf) const;
    //int32_t IndexOfAny(const std::span<const char>& anyOf, int32_t startIndex);
    //int IndexOfAny(char[] anyOf, int startIndex, int count);
    //int IndexOf(string value);
    //int IndexOf(string value, int startIndex);
    //int IndexOf(string value, int startIndex, int count);
    //int LastIndexOf(char value);
    //int LastIndexOf(char value, int startIndex);
    //extern int LastIndexOf(char value, int startIndex, int count);
    //int LastIndexOfAny(char[] anyOf);
    //int LastIndexOfAny(char[] anyOf, int startIndex);
    //extern int LastIndexOfAny(char[] anyOf, int startIndex, int count);
    //int LastIndexOf(string value);
    //int LastIndexOf(string value, int startIndex);
    //int LastIndexOf(string value, int startIndex, int count);
    //string PadLeft(int totalWidth);
    //string PadLeft(int totalWidth, char paddingChar);
    //string PadRight(int totalWidth);
    //string PadRight(int totalWidth, char paddingChar);
    //bool StartsWith(string value);
    //bool StartsWith(string value, bool ignoreCase);
    //string ToLower();
    //string ToLowerInvariant();
    //string ToUpper();
    //string ToUpperInvariant();
    //override string ToString();
    //string Trim();
    //string Insert(int startIndex, string value);
    //string Replace(char oldChar, char newChar);
    //string Replace(string oldValue, string newValue);
    //string Remove(int startIndex, int count);
    //template <typename _Types>
    //static string Format(string format, const _Types&.. args);
    //template <typename _Types>
    //static string Concat(const _Types&..args);
    //static string Concat(IEnumerable<string> values);
    //static string Intern(string str);
    //static string IsInterned(string str);
    //TypeCode GetTypeCode();
    //bool IConvertible.ToBoolean(IFormatProvider provider);
    //
    //
private:

private:
    inline static StringCache<_Char> m_strCache;
    std::string& m_str;
};

inline String::String(const _Char* str) :
    String(str, BasicStringTraits<_Char>::Length(str))
{
}

inline String::String(const _Char* str, int32_t length) :
    m_str(m_strCache.GetValue({str, length}))
{
}

inline String::String(const std::span<const _Char>& str)
{
}

inline String::String(char c, int32_t count)
{
}

inline _Char String::operator[](int32_t index) const noexcept
{
    return const_cast<String*>(this)->operator[](index);
}

inline _Char& String::operator[](int32_t index) noexcept
{
    return m_str[index];
}

inline int32_t String::GetHashCode() const noexcept
{
    return reinterpret_cast<int32_t>(&m_str);
}

inline int32_t String::Length() const noexcept
{
    return m_strBuffer.size() - 1;
}

}
