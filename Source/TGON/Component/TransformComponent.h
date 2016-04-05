#pragma once
#include "IComponent.h"

namespace tgon
{


class TransformComponent : public IComponent
{
	struct transform { float x, y, z; };
	typedef transform Position;
	typedef transform Angle;
	typedef transform Scale;

public:
	TransformComponent( );
	virtual ~TransformComponent( );

	void SetPosition( const Position& position ) { m_position = position; }
	void SetAngle( const Angle& angle ) { m_angle = angle; }
	void SetScale( const Scale& scale ) { m_scale = scale; }

	const Position& GetPosition() const { return m_position; }
	const Angle& GetAngle( ) const { return m_angle; }
	const Scale& GetScale( ) const { return m_scale; }

private:
	Position m_position;
	Angle m_angle;
	Scale m_scale;
};


}