/*
* Author : Junho-Cha
* Date : 07/05/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../../Platform/Config/Build.h"

#include "../../Core/Reflection/TObject.h"
#include "../../Core/Math/TVector3.h"
#include "../../Core/Math/TMatrix4x4.h"


namespace tgon
{


class TGON_API TCamera final :
	public TObject
{
public:
	TGON_OBJECT( TCamera, TObject )

	TCamera( );
	
	virtual ~TCamera( );

public:
	static const TVector3 Eye;

	static const TVector3 LookAt;

	static const TVector3 Up;


	/*
		Sets
	*/
	void SetEye( const TVector3& );
	
	void SetLookAt( const TVector3& );
	
	void SetUp( const TVector3& );

	void SetFieldOfView( float fov );

	// Set the near clipping plane's Z position
	void SetNearClippingZ( float nearZ );

	// Set the far clipping plane's Z position
	void SetFarClippingZ( float farZ );


	/*
		Gets
	*/
	//
	const TMatrix4x4& GetView( ) const;

	// Return 3D projection matrix.
	const TMatrix4x4& GetPerspective( ) const;

	// Return 2D projection matrix.
	const TMatrix4x4& GetOrthographic( ) const; 

	//
	const TMatrix4x4& GetViewport( ) const;

private:
	TVector3 m_eye;

	TVector3 m_up;

	TVector3 m_lookAt;

	TMatrix4x4 m_matPerspective;

	TMatrix4x4 m_matOrtho;

	TMatrix4x4 m_matView;

	TMatrix4x4 m_matViewport;

	float m_fov;

	// Near clipping plane's Z position
	float m_nearZ;

	// Far clipping plane's Z position
	float m_farZ;
};


inline const TMatrix4x4& tgon::TCamera::GetPerspective( ) const
{
	return m_matPerspective;
}

inline const TMatrix4x4& TCamera::GetOrthographic( ) const
{
	return m_matOrtho;
}

inline const TMatrix4x4& tgon::TCamera::GetView( ) const
{
	return m_matView;
}

inline const TMatrix4x4& tgon::TCamera::GetViewport( ) const
{
	return m_matViewport;
}

inline void TCamera::SetEye( const TVector3& eye )
{
	m_eye = eye;
}

inline void TCamera::SetLookAt( const TVector3& lookAt )
{
	m_lookAt = lookAt;
}

inline void TCamera::SetUp( const TVector3& up )
{
	m_up = up;
}

inline void tgon::TCamera::SetFieldOfView( float fov )
{
	m_fov = fov;
}

inline void TCamera::SetNearClippingZ( float nearZ )
{
	m_nearZ = nearZ;
}

inline void tgon::TCamera::SetFarClippingZ( float farZ )
{
	m_farZ = farZ;
}


}