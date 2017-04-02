/**
 * filename Hash.h
 * author   ggomdyu
 * since    03/04/2017
 */

#pragma once
#include "../Platform/TConfig.h"

#include <cassert>
#include <cmath>
#include <string>
#include <map>

namespace std
{

//template<> struct hash<std::string>
//{
//    typedef S argument_type;
//    typedef std::size_t result_type;
//    result_type operator()(argument_type const& s) const
//    {
//        result_type const h1(std::hash<std::string>{}(s.first_name));
//        result_type const h2(std::hash<std::string>{}(s.last_name));
//        return h1 ^ (h2 << 1); // or use boost::hash_combine (see Discussion)
//    }
//};

}
namespace tgon
{

class TGON_API Hash
{
/**
 * @section Public command methods
 */ 
public:
	/* @return	The value that hashed by x65599 algorithm */
	template <std::size_t N>
	static std::size_t StringToHash(const char(&str)[N]);
	
    /* @return	The value that hashed by x65599 algorithm */
    static std::size_t StringToHash(const char* str, std::size_t length);

/**
 * @section Private command methods
 */
private:
	static std::size_t x65599Hash(const char* str, std::size_t length);
    
    template <typename HashAlgorithmTag>
    static bool CheckHashCollision(std::size_t hash, const std::string& key);

/** 
 * @section Ctor/Dtor
 */ 
public:
    Hash() = delete;
    ~Hash() = delete;
};

template<std::size_t N>
inline std::size_t Hash::StringToHash(const char(&str)[N])
{
    std::hash<std::string> hasher;
	return x65599Hash(str, N);
}

inline std::size_t Hash::StringToHash(const char* str, std::size_t length)
{
	return x65599Hash(str, length);
}

inline std::size_t Hash::x65599Hash(const char* str, std::size_t length)
{
    std::size_t hash = 0;
    for (std::size_t i = 0; i < length; ++i)
    {
        hash = 65599 * hash + str[i];
    }

    hash = hash ^ (hash >> 16);

#if defined(_DEBUG) || defined(DEBUG)
    struct hash_x65599 {};

    if (Hash::CheckHashCollision<hash_x65599>(hash, str))
    {
        // TODO: How about USE logger?
        assert(false && "DANGEROUS WARNING! :: Hash collision occured!!!");
    }
#endif

    return hash;
}

template <typename HashAlgorithmTag>
inline bool Hash::CheckHashCollision(std::size_t hash, const std::string& str)
{
    static std::map<std::size_t, std::string> hashCollisionChecker;

    auto iter = hashCollisionChecker.find(hash);
    if (iter != hashCollisionChecker.end())
    {
        if (std::strcmp(iter->second.c_str(), str.c_str()))
        {
            return true;
        }
    }
    else
    {
        hashCollisionChecker.insert({ hash, str });
    }

    return false;
}

} /* namespace tgon */