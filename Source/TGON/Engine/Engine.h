/**
 * @filename    TEngine.h
 * @author      ggomdyu
 * @since       07/23/2016
 */

#pragma once
#include "EngineContextObject.h"

namespace tgon {
//namespace engine {

class TGON_API Engine :
	public ModuleContext
{
public:
	TGON_MAKE_OBJECT_INTERFACE(Engine)

public:
    Engine();
    virtual ~Engine() = default;

public:
    int32_t Execute(int argc, char** argv);

private:
    void AddEssentialModules();
    void UpdateModules();

private:
	std::shared_ptr<class GameApplication> m_gameApplication;
    std::vector<IModule*> m_modulesForFastIter;
};

} /* namespace tgon */
