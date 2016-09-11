/*
* Author : Junho-Cha
* Date : 07/05/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../../Core/Object/Object.h"
#include "../../Core/Math/Vector3.h"
#include "../../Core/Math/Matrix4x4.h"


namespace tgon
{


class TGON_API TCamera final :
	public Object
{
public:
	TGON_GENERATE_OBJECT_INTERFACE( TCamera, std::nullptr_t )

	TCamera( );
	
	virtual ~TCamera( );

public:
	static const Vector3 Eye;

	static const Vector3 LookAt;

	static const Vector3 Up;


	/*
		Sets
	*/
	void SetEye( const Vector3& );
	
	void SetLookAt( const Vector3& );
	
	void SetUp( const Vector3& );

	void SetFieldOfView( float fov );

	// Set the near clipping plane's Z position
	void SetNearClippingZ( float nearZ );

	// Set the far clipping plane's Z position
	void SetFarClippingZ( float farZ );


	/*
		Gets
	*/
	//
	const Matrix4x4& GetView( ) const;

	// Return 3D projection matrix.
	const Matrix4x4& GetPerspective( ) const;

	// Return 2D projection matrix.
	const Matrix4x4& GetOrthographic( ) const; 

	//
	const Matrix4x4& GetViewport( ) const;


private:
	Vector3 m_eye;

	Vector3 m_up;

	Vector3 m_lookAt;

	Matrix4x4 m_matPerspective;

	Matrix4x4 m_matOrtho;

	Matrix4x4 m_matView;

	Matrix4x4 m_matViewport;

	float m_fov;

	float m_nearZ;

	float m_farZ;
};


inline const Matrix4x4& TCamera::GetPerspective( ) const
{
	return m_matPerspective;
}

inline const Matrix4x4& TCamera::GetOrthographic( ) const
{
	return m_matOrtho;
}

inline const Matrix4x4& TCamera::GetView( ) const
{
	return m_matView;
}

inline const Matrix4x4& TCamera::GetViewport( ) const
{
	return m_matViewport;
}

inline void TCamera::SetEye( const Vector3& eye )
{
	m_eye = eye;
}

inline void TCamera::SetLookAt( const Vector3& lookAt )
{
	m_lookAt = lookAt;
}

inline void TCamera::SetUp( const Vector3& up )
{
	m_up = up;
}

inline void TCamera::SetFieldOfView( float fov )
{
	m_fov = fov;
}

inline void TCamera::SetNearClippingZ( float nearZ )
{
	m_nearZ = nearZ;
}

inline void TCamera::SetFarClippingZ( float farZ )
{
	m_farZ = farZ;
}


} /*namespace tgon*/