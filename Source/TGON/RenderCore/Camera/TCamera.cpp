#include "PrecompiledHeader.h"
#include "TCamera.h"

#include ".././Core/Math/TMath.h"

const tgon::TVector3 tgon::TCamera::Eye( 0.f, 0.f, 0.f );

const tgon::TVector3 tgon::TCamera::LookAt( 0.f, 0.f, -5.f );

const tgon::TVector3 tgon::TCamera::Up( 0.f, 1.f, 0.f );


tgon::TCamera::TCamera( ) :
	m_fov( TMath::PI * 0.25f ),
	m_nearZ( 0.3f ),
	m_farZ( 1000.f ),
	m_eye( TCamera::Eye ),
	m_lookAt( TCamera::LookAt ),
	m_up( TCamera::Up ),
	m_matView( TMatrix4x4::View( m_eye, m_lookAt, m_up )),
	m_matPerspective( TMatrix4x4::PerspectiveFovLH( m_fov, 1.f, m_nearZ, m_farZ ))
{
	
}

tgon::TCamera::~TCamera( )
{
}
