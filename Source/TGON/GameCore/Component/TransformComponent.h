/*
* Author : Junho-Cha
* Date : 04/26/2015
* Latest author :
* Latest date :
*/


#pragma once
#include "IComponent.h"
#include "../../Core/Math/TVector3.h"


namespace tgon
{

class TransformComponent : 
	public IComponent
{
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
	void SetPosition( const TVector3& );

	void Move( const TVector3& );

	void SetAngle( const TVector3& );

	void Rotate( const TVector3& );

	void SetScale( const TVector3& );

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


}


inline void tgon::TransformComponent::SetPosition( const TVector3& pos )
{
	m_pos = pos;
}

inline void tgon::TransformComponent::Move( const TVector3& pos )
{
	m_pos += pos;
}

inline void tgon::TransformComponent::SetAngle( const TVector3& rot )
{
	m_angle = rot;
}

inline void tgon::TransformComponent::Rotate( const TVector3& rot )
{
	m_angle += rot;
}

inline void tgon::TransformComponent::SetScale( const TVector3& scale )
{
	m_scale = scale;
}

inline void tgon::TransformComponent::Scale( const TVector3& scale )
{
	m_scale += scale;
}

inline const tgon::TVector3& tgon::TransformComponent::GetPosition( ) const
{
	return m_pos;
}

inline const tgon::TVector3& tgon::TransformComponent::GetAngle( ) const
{
	return m_angle;
}

inline const tgon::TVector3& tgon::TransformComponent::GetScale( ) const
{
	return m_scale;
}