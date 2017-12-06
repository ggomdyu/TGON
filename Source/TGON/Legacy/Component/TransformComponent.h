/*
* Author : Cha Junho
* Date : 04/26/2015
* Latest author :
* Latest date :
*/


#pragma once
#include "IComponent.h"
#include "../../Core/Platform/OSAL/PlatformInclude.h"
 
#include "../../Core/Math/Vector3.h"


namespace tgon
{

class TGON_API TransformComponent : 
	public IComponent
{
public:
	TGON_GENERATE_OBJECT_INTERFACE( TransformComponent, IComponent )

public:
	TransformComponent( class GameObject* owner );
	
	virtual ~TransformComponent( );

	/*
		Commands
	*/
	virtual void Update( float tickTime ) override;

	/*
		Sets
	*/
	// Initialize as new vector.
	void SetPosition( const Vector3& );

	// Adjust current position.
	void Move( const Vector3& );

	// Initialize as new angle.
	void SetAngle( const Vector3& );

	// Adjust current angle.
	void Rotate( const Vector3& );

	// Initialize as new scale.
	void SetScale( const Vector3& );

	// Adjust current scale.
	void Scale( const Vector3& );

	/*
		Gets
	*/
	const Vector3& GetPosition( ) const;

	const Vector3& GetAngle( ) const;

	const Vector3& GetScale( ) const;

private:
	Vector3 m_pos;
	Vector3 m_angle;
	Vector3 m_scale;
};


inline void TransformComponent::SetPosition( const Vector3& pos )
{
	m_pos = pos;
}

inline void TransformComponent::Move( const Vector3& pos )
{
	m_pos += pos;
}

inline void TransformComponent::SetAngle( const Vector3& rot )
{
	m_angle = rot;
}

inline void TransformComponent::Rotate( const Vector3& rot )
{
	m_angle += rot;
}

inline void TransformComponent::SetScale( const Vector3& scale )
{
	m_scale = scale;
}

inline void TransformComponent::Scale( const Vector3& scale )
{
	m_scale += scale;
}

inline const Vector3& TransformComponent::GetPosition( ) const
{
	return m_pos;
}

inline const Vector3& TransformComponent::GetAngle( ) const
{
	return m_angle;
}

inline const Vector3& TransformComponent::GetScale( ) const
{
	return m_scale;
}


}