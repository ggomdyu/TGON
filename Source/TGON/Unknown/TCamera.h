#pragma once
#include "../Math/TVector3.h"
#include "../Math/TMatrix4x4.h"
#include "TObject.h"
#include "TSingleton.h"


namespace tgon
{


class TCamera final : public TObject
{
public:
	TGON_OBJECT( TCamera, TObject )
	TGON_SINGLETON( TCamera )

	static const TVector3 Eye;
	static const TVector3 LookAt;
	static const TVector3 Up;

public:
	const TMatrix4x4& GetView( ) const;
	const TMatrix4x4& GetPerspective( ) const;
	const TMatrix4x4& GetOrtho( ) const; 
	const TMatrix4x4& GetViewport( ) const;

private:
	TCamera( );
	~TCamera( );

private:
	TVector3 m_eye;
	TVector3 m_up;
	TVector3 m_LookAt;

	TMatrix4x4 m_matPerspective;
	TMatrix4x4 m_matOrtho;
	TMatrix4x4 m_matView;
	TMatrix4x4 m_matViewport;
};


const TMatrix4x4& tgon::TCamera::GetPerspective( ) const
{
	return m_matPerspective;
}

inline const TMatrix4x4& TCamera::GetOrtho( ) const
{
	return m_matOrtho;
}

const TMatrix4x4& tgon::TCamera::GetView( ) const
{
	return m_matView;
}

inline const TMatrix4x4& tgon::TCamera::GetViewport( ) const
{
	return m_matViewport;
}


}