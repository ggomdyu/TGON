#include "PrecompiledHeader.h"
#include "TCamera.h"

#include ".././Core/Math/Mathf.h"


namespace tgon
{


const Vector3 TCamera::Eye( 0.f, 0.f, 0.f );

const Vector3 TCamera::LookAt( 0.f, 0.f, -5.f );

const Vector3 TCamera::Up( 0.f, 1.f, 0.f );


TCamera::TCamera( ) :
	m_fov( Math::PI * 0.25f ),
	m_nearZ( 0.3f ),
	m_farZ( 1000.f ),
	m_eye( TCamera::Eye ),
	m_lookAt( TCamera::LookAt ),
	m_up( TCamera::Up ),
	m_matView( Matrix4x4::View( m_eye, m_lookAt, m_up )),
	m_matPerspective( Matrix4x4::PerspectiveFovLH( m_fov, 1.f, m_nearZ, m_farZ ))
{
	
}

TCamera::~TCamera( )
{
}


} /* namespace tgon */
