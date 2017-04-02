#include "PrecompiledHeader.h"
#include "Hash.h"

//namespace tgon
//{
//
//bool Math::CheckHashCollision(std::size_t hash, const std::string& str)
//{
//    static std::map<std::size_t, std::string> hashCollisionChecker;
//
//    auto iter = hashCollisionChecker.find(hash);
//    if (iter != hashCollisionChecker.end())
//    {
//        if (std::strcmp(iter->second.c_str(), str.c_str()))
//        {
//            return true;
//        }
//    }
//    else
//    {
//        hashCollisionChecker.insert({ hash, str });
//    }
//
//    return false;
//}
//
//}