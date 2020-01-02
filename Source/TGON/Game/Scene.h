/**
 * @file    Scene.h
 * @author  ggomdyu
 * @since   08/19/2016
 */

#pragma once
#include <vector>
#include <unordered_map>

#include "GameObject.h"
#include "Text/StringHash.h"

namespace tgon
{

class Scene :
    public Object
{
public:
    TGON_DECLARE_RTTI(Scene)

/**@section Method */
public:
    virtual void Initialize() {}
    virtual void Destroy() {}
    virtual void Update();
    void AddObject(const std::shared_ptr<GameObject>& object);
    void AddObject(std::shared_ptr<GameObject>&& object);
    bool RemoveObject(const StringViewHash& objectName);
    std::shared_ptr<GameObject> FindObject(const StringViewHash& objectName);
    std::shared_ptr<const GameObject> FindObject(const StringViewHash& objectName) const;

/**@section Variable */
private:
    std::vector<std::shared_ptr<GameObject>> m_objects;
    std::unordered_map<StringHash, std::shared_ptr<GameObject>> m_objectDict;
};

} /* namespace tgon */
