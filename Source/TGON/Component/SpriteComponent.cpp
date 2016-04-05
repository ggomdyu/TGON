#include "stdafx.h"
#include "SpriteComponent.h"
//
//#include "GraphicsManager.h"
//#include "TransformComponent.h"
//
//tgon::SpriteComponent::SpriteComponent( const wchar_t* texturePath ) :
//	m_texture( GraphicsManager::GetInstance( )->GetGraphicsDevice( ),
//			   texturePath )
//{
//}
//
//
//tgon::SpriteComponent::~SpriteComponent( )
//{
//}
//
//
//void tgon::SpriteComponent::Render( )
//{
//	auto* transformComponent = this->GetOwner( )->GetComponent<TransformComponent>( );
//	D3DXMATRIXA16 matWorld;
//
//	auto& w = transformComponent->GetAngle( ).z;
//
//	D3DXVECTOR2 vecScale( transformComponent->GetScale( ).x, transformComponent->GetScale( ).y );
//	D3DXVECTOR2 vecTranslation( transformComponent->GetPosition( ).x, transformComponent->GetPosition( ).y );
//
//	D3DXMatrixTransformation2D(
//			&matWorld,
//			nullptr,
//			1.0f,
//			&vecScale,
//			nullptr,
//			transformComponent->GetAngle( ).z,
//			&vecTranslation
//		);
//	
//	
//}