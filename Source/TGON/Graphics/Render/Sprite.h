///**
// * @file    Sprite.h
// * @author  ggomdyu
// * @since   06/06/2018
// */
//
//#pragma once
//#include "Core/Math/Matrix4x4.h"
//#include "Core/Math/Color.h"
//
//#include "Mesh.h"
//#include "MeshRenderer.h"
//#include "Material.h"
//
//namespace tgon
//{
//
//class Texture;
//class Mesh;
//    
//class Sprite
//{
///* @section Public constructor */
//public:
//    Sprite();
//    
//    /* @brief   Initializes the sprite with specified file path. */
//    explicit Sprite(const std::string& filePath);
//    
//    /* @brief   Initializes the sprite with specified file path and blend color. */
//    Sprite(const std::string& filePath, const Color4f& blendColor);
//    
//    /* @brief   Initializes the sprite with texture and material. */
//    Sprite(const std::shared_ptr<Texture>& texture, const std::shared_ptr< Material>& material);
//    
//    /* @brief   Initializes the sprite with texture and material. */
//    Sprite(const std::shared_ptr<Texture>& texture, const std::shared_ptr<Material>& material, const Color4f& blendColor);
//
///* @section Public method */
//public:
//    void Draw(Graphics& graphics);
//    
//    /* @brief   Sets the blend color. */
//    void SetBlendColor(const Color4f& blendColor);
//    
//    /* @brief   Sets the texture. */
//    void SetTexture(const std::shared_ptr<Texture>& texture);
//    
//    /* @brief   Sets the world-view-projection matrix. */
//    void SetWVP(const Matrix4x4& matWVP) noexcept;
//
//    /* @brief   Gets the world-view-projection matrix. */
//    const Matrix4x4& GetWVP() const noexcept;
//    
//    /* @brief   Gets the blend color. */
//    const Color4f& GetBlendColor() const noexcept;
//    
//    /* @brief   Gets the texture. */
//    const std::shared_ptr<Texture>& GetTexture() const noexcept;
//    
//    /* @brief   Gets the material. */
//    const std::shared_ptr<Material>& GetMaterial() const noexcept;
//    
//    /* @brief   Gets the mesh. */
//    const std::shared_ptr<Mesh>& GetMesh() const noexcept;
//
///* @section Private variable */
//private:
//    std::shared_ptr<Texture> m_texture;
//};
//    
//} /* namespace tgon */
