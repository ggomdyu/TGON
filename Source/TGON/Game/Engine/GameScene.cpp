#include "PrecompiledHeader.h"

#include "GameScene.h"

namespace tgon
{

void GameScene::AddObject(const std::shared_ptr<GameObject>& object)
{
    auto predicate = [&](const std::shared_ptr<GameObject>& lhs, size_t rhs)
    {
        return lhs->GetRTTI()->GetHashCode() < rhs;
    };

    auto iter = std::lower_bound(m_objects.begin(), m_objects.end(), object->GetName().GetHashCode(), predicate);

    m_objects.insert(iter, object);
}

GameObject* GameScene::GetObject(const HashStringView& objectName)
{
    auto predicate = [&](const std::shared_ptr<GameObject>& lhs, size_t rhs)
    {
        return lhs->GetRTTI()->GetHashCode() < rhs;
    };

    auto iter = std::lower_bound(m_objects.begin(), m_objects.end(), objectName.GetHashCode(), predicate);
    if (iter != m_objects.end())
    {
        return (*iter).get();
    }
    else
    {
        return nullptr;
    }
}

const GameObject* GameScene::GetObject(const HashStringView& objectName) const
{
    return const_cast<GameScene*>(this)->GetObject(objectName);
}
    
bool GameScene::RemoveObject(const HashStringView& objectName)
{
    auto predicate = [&](const std::shared_ptr<GameObject>& lhs, size_t rhs)
    {
        return lhs->GetRTTI()->GetHashCode() < rhs;
    };
    
    auto iter = std::lower_bound(m_objects.begin(), m_objects.end(), objectName.GetHashCode(), predicate);
    if (iter != m_objects.end())
    {
        m_objects.erase(iter);
        return true;
    }
    else
    {
        return false;
    }
}

void GameScene::Update()
{
    for (auto& object : m_objects)
    {
        object->Update();
    }
}

} /* namespace tgon */
