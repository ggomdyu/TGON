/**
 * @file    MeshRendererComponent.h
 * @author  ggomdyu
 * @since   08/11/2018
 */

#pragma once
#include "Graphics/Render/Material.h"
#include "Graphics/Render/Mesh.h"
#include "Graphics/Engine/GraphicsModule.h"

#include "Component.h"

namespace tgon
{

class TGON_API CameraComponent :
	public Component
{
public:
    TGON_RUNTIME_OBJECT(CameraComponent);

/* @section Public constructor */
public:
    CameraComponent();
    
/* @section Public destructor */
public:
    virtual ~CameraComponent() override = default;

/* @section Public method */
public:
	virtual void Update() override;
    
/* @section Private variable */
private:
};

} /* namespace tgon */
