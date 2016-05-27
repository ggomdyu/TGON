/*
* Author : Junho-Cha
* Date : 04/02/2016
* Latest author :
* Latest date :
*/

#pragma once
#include <tgLib/Singleton.h>

#include "../Core/TObject.h"
#include "../System/ISystem.h"
#include "../Scene/IScene.h"


namespace tgon
{


class SceneSystem : public ISystem
{
public:
	TGON_OBJECT( SceneSystem, TObject )
	TGON_SINGLETON( SceneSystem )

	virtual void Update( float tickTime );

public:
	void LoadScene( IScene* newScene );

protected:
	SceneSystem( );
	virtual ~SceneSystem( );

private:
	std::unique_ptr<IScene> m_currScene;
};



}