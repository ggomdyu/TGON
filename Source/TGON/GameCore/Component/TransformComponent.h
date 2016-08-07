/*
* Author : Cha Junho
* Date : 04/26/2015
* Latest author :
* Latest date :
*/


#pragma once
#include "IComponent.h"
#include "../../Platform/Config/Build.h"
 
#include "../../Core/Math/TVector3.h"


namespace tgon
{

class TGON_API TransformComponent : 
	public IComponent
{
public:
	TGON_GENERATE_OBJECT_INTERFACE( TransformComponent, IComponent )

public:
	TransformComponent( class TGameObject* owner );
	
	virtual ~TransformComponent( );

	/*
		Commands
	*/
	virtual void Update( float tickTime ) override;

	/*
		Sets
	*/
	// Initialize as new vector.
	void SetPosition( const TVector3& );

	// Adjust current position.
	void Move( const TVector3& );

	// Initialize as new angle.
	void SetAngle( const TVector3& );

	// Adjust current angle.
	void Rotate( const TVector3& );

	// Initialize as new scale.
	void SetScale( const TVector3& );

	// Adjust current scale.
	void Scale( const TVector3& );

	/*
		Gets
	*/
	const TVector3& GetPosition( ) const;

	const TVector3& GetAngle( ) const;

	const TVector3& GetScale( ) const;

private:
	TVector3 m_pos;
	TVector3 m_angle;
	TVector3 m_scale;
};


inline void TransformComponent::SetPosition( const TVector3& pos )
{
	m_pos = pos;
}

inline void TransformComponent::Move( const TVector3& pos )
{
	m_pos += pos;
}

inline void TransformComponent::SetAngle( const TVector3& rot )
{
	m_angle = rot;
}

inline void TransformComponent::Rotate( const TVector3& rot )
{
	m_angle += rot;
}

inline void TransformComponent::SetScale( const TVector3& scale )
{
	m_scale = scale;
}

inline void TransformComponent::Scale( const TVector3& scale )
{
	m_scale += scale;
}

inline const TVector3& TransformComponent::GetPosition( ) const
{
	return m_pos;
}

inline const TVector3& TransformComponent::GetAngle( ) const
{
	return m_angle;
}

inline const TVector3& TransformComponent::GetScale( ) const
{
	return m_scale;
}


}