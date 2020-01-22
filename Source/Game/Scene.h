/**
 * @file    Scene.h
 * @author  ggomdyu
 * @since   08/19/2016
 */

#pragma once
#include <vector>
#include <unordered_map>

#include "Text/StringHash.h"

#include "GameObject.h"

namespace tgon
{

class Scene :
    public RuntimeObject
{
public:
    TGON_DECLARE_RTTI(Scene)

/**@section Type */
private:
    using GameObjectVector = std::vector<std::shared_ptr<GameObject>>;
    using GameObjectMap = std::unordered_map<StringHash, std::shared_ptr<GameObject>>;

/**@section Method */
public:
    virtual void Initialize() {}
    virtual void Update();
    void AddObject(const std::shared_ptr<GameObject>& object);
    void AddObject(std::shared_ptr<GameObject>&& object);
    bool RemoveObject(const StringViewHash& objectName);
    void RemoveAllObject();
    std::shared_ptr<GameObject> FindObject(const StringViewHash& objectName);
    std::shared_ptr<const GameObject> FindObject(const StringViewHash& objectName) const;

/**@section Variable */
private:
    GameObjectVector m_objectVector;
    GameObjectMap m_objectMap;
};

} /* namespace tgon */
