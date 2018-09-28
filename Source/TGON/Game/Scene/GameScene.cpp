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

std::shared_ptr<GameObject> GameScene::FindObject(const StringViewHash& objectName)
{
    auto predicate = [&](const std::shared_ptr<GameObject>& lhs, size_t rhs)
    {
        return lhs->GetRTTI()->GetHashCode() < rhs;
    };

    auto iter = std::lower_bound(m_objects.begin(), m_objects.end(), objectName.GetHashCode(), predicate);
    if (iter != m_objects.end())
    {
        return *iter;
    }
    else
    {
        return nullptr;
    }
}

const std::shared_ptr<GameObject> GameScene::FindObject(const StringViewHash& objectName) const
{
    return const_cast<GameScene*>(this)->FindObject(objectName);
}
    
bool GameScene::RemoveObject(const StringViewHash& objectName)
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
