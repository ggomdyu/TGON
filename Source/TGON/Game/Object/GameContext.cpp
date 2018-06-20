#include "PrecompiledHeader.h"

#include "GameContext.h"

namespace tgon
{

GameContext* GameContext::GetInstance()
{
    static GameContext instance;
    return &instance;
}

} /*namespace tgon*/
