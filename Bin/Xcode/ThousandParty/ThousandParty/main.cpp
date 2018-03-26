#include "PrecompiledHeader.pch"

#define TGON_USING_OPENGL 1
#include "Game/Engine/GameApplication.h"

#include "Core/Random/Random.h"
#include "Core/Object/Object.h"
#include "Core/Object/IRuntimeObjectUtility.h"
#include "Core/Platform/Window.h"
#include "Core/Platform/Generic/GenericWindowType.h"
#include "Core/File/Path.h"
#include "Core/Platform/Time.h"
#include "Core/Random/Random.h"
#include "Core/Drawing/Bitmap.h"
#include "Core/Debug/Log.h"
#include "Core/Platform/Screen.h"
#include "Core/Platform/Locale.h"
#include "Core/Platform/ScreenType.h"
#include "Core/String/FixedString.h"
#include "Core/String/FixedStringUtility.h"
#include "Core/String/StringView.h"
#include "Core/File/Path.h"
#include "Core/Utility/InstantiateCounter.h"
#include "Core/Math/Mathematics.h"
#include "Core/Math/Vector3.h"
#include "Core/Math/Vector2.h"
#include "Core/Math/Color.h"
#include "Core/Math/Matrix4x4.h"
#include "Core/Math/Extent.h"
#include "Core/Hash/UUID.h"
#include "Core/Random/Random.h"
#include "Core/Utility/RAII.h"
#include "Core/File/Path.h"
#include "Core/Utility/Windows/HandleGuard.h"
#include "Graphics/LowLevelRender/Generic/GenericGraphicsType.h"
#include "Graphics/LowLevelRender/Generic/GenericGraphics.h"
#include "Graphics/LowLevelRender/Texture.h"
#include "Graphics/LowLevelRender/OpenGL/OpenGLShader.h"
#include "Graphics/LowLevelRender/OpenGL/OpenGLShaderCode.h"
#include "Graphics/Render/Renderer.h"
#include "Graphics/Render/Quad.h"
#include "Game/Module/GraphicsModule.h"
#include "Game/Module/TimeModule.h"
#include "Graphics/LowLevelRender/VertexBuffer.h"
#include "Graphics/LowLevelRender/IndexBuffer.h"
#include "Graphics/LowLevelRender/Texture.h"
#include "Game/Module/GraphicsModule.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#pragma comment(lib, "assimp-vc140-mtd.lib")
#pragma comment(lib, "IrrXML.lib")

using namespace tgon;

namespace tgon
{

class AssetManager
{
public:
    static AssetManager& GetInstance()
    {
        static AssetManager instance;
        return instance;
    }

    template <typename _AssetType>
    std::shared_ptr<_AssetType>& LoadAsset(const char* assetPath);

    void Purge()
    {
        m_textures.clear();
    }

private:
    AssetManager() = default;

private:
    std::map<StringHash, std::shared_ptr<Texture>> m_textures;
};

template <>
std::shared_ptr<Texture>& AssetManager::LoadAsset<Texture>(const char* assetPath)
{
    StringHash strHash = X65599Hash(assetPath);
    
    // If the asset is already cached, then return it.
    auto iter = m_textures.find(strHash);
    if (iter != m_textures.end())
    {
        return iter->second;
    }
    else
    {
        return m_textures[strHash] = std::make_shared<Texture>(assetPath);
    }
}

}

struct V3F_N4F_C2B
{
};


//class Mesh
//{
//public:
//    template <typename _StringType, typename _VertexBufferType, typename _IndexBufferType, typename _TextureContainerType>
//    Mesh(_StringType&& name, _VertexBufferType&& vertexBuffer, _IndexBufferType&& indexBuffer, _TextureContainerType&& textureContainerType) :
//        m_name(std::forward<_StringType>(name)),
//        m_vertexBuffer(std::forward<_VertexBufferType>(vertexBuffer)),
//        m_indexBuffer(std::forward<_IndexBufferType>(indexBuffer)),
//        m_textures(std::forward<_TextureContainerType>(textureContainerType))
//    {
//    }
//
//public:
//    void Draw(Shader& shader)
//    {
//        m_vertexBuffer.Use();
//        m_indexBuffer.Use();
//
//
//        for (auto i = 0; i < m_textures.size(); ++i)
//        {
//            glActiveTexture(GL_TEXTURE0 + i);
//
//            shader.GetUniformLocation("diffuse");
//        }
//
//        glDrawElements(GL_TRIANGLES, m_indexBuffer.GetDataBytes() / 4, GL_UNSIGNED_INT, nullptr);
//    }
//
//    const VertexBuffer& GetVertexBuffer() const
//    {
//        return m_vertexBuffer;
//    }
//
//    const IndexBuffer& GetIndexBuffer() const
//    {
//        return m_indexBuffer;
//    }
//
//private:
//    std::string m_name;
//    VertexBuffer m_vertexBuffer;
//    IndexBuffer m_indexBuffer;
//    std::vector<std::shared_ptr<Texture>> m_textures;
//};
//
//class Material
//{
//public:
//
//};
//
//class Light
//{
//};
//
//class DirectionalLight :
//    public Light
//{
//public:
//};
//
//class Model
//{
//public:
//    Model(const std::string& modelPath) :
//        m_modelPath(modelPath)
//    {
//        this->ImportModel(modelPath);
//    }
//
//public:
//    void Draw(Shader& shader)
//    {
//        for (auto& mesh : m_meshes)
//        {
//            mesh.Draw(shader);
//        }
//    }
//
//private:
//    bool ImportModel(const std::string& modelPath)
//    {
//        m_modelPath = modelPath;
//
//        Assimp::Importer importer;
//        const aiScene* scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs);
//        if (scene == nullptr)
//        {
//            return false;
//        }
//
//        aiNode* rootNode = scene->mRootNode;
//        if (scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || rootNode == nullptr)
//        {
//            return false;
//        }
//
//        this->ProcessNode(rootNode, scene);
//
//        return true;
//    }
//
//    void ProcessNode(const aiNode* node, const aiScene* scene)
//    {
//        m_meshes.reserve(m_meshes.capacity() + node->mNumMeshes);
//
//        for (unsigned int i = 0; i < node->mNumMeshes; ++i)
//        {
//            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
//            m_meshes.push_back(ProcessMesh(mesh, scene));
//        }
//
//        for (unsigned int i = 0; i < node->mNumChildren; ++i)
//        {
//            this->ProcessNode(node->mChildren[i], scene);
//        }
//    }
//
//    Mesh ProcessMesh(const aiMesh* mesh, const aiScene* scene)
//    {
//        std::vector<P3F_N3F_U2F> vertices;
//        {
//            vertices.reserve(mesh->mNumVertices);
//
//            for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
//            {
//                const auto& position = mesh->mVertices[i];
//                const auto& normal = mesh->mNormals[i];
//
//                if (mesh->HasTextureCoords(0))
//                {
//                    const auto& uv = mesh->mTextureCoords[0][i];
//
//                    vertices.push_back({
//                        Vector3(position.x, position.y, position.z),
//                        Vector3(normal.x, normal.y, normal.z),
//                        Vector2(uv.x, uv.y)
//                    });
//                }
//                else
//                {
//                    vertices.push_back({
//                        Vector3(position.x, position.y, position.z),
//                        Vector3(normal.x, normal.y, normal.z),
//                        Vector2(0.0f, 0.0f)
//                    });
//                }
//            }
//        }
//
//        std::vector<unsigned int> indices;
//        {
//            indices.reserve(mesh->mNumFaces * 3);
//
//            for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
//            {
//                aiFace& face = mesh->mFaces[i];
//                for (unsigned j = 0; j < face.mNumIndices; ++j)
//                {
//                    indices.push_back(face.mIndices[j]);
//                }
//            }
//        }
//
//        std::vector<std::shared_ptr<Texture>> textures;
//        if (mesh->mMaterialIndex >= 0)
//        {
//            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
//
//            auto diffuseTextures = this->LoadMaterialTextures(material, aiTextureType_DIFFUSE);
//            textures.insert(textures.begin(), diffuseTextures.begin(), diffuseTextures.end());
//
//            auto specularTextures = this->LoadMaterialTextures(material, aiTextureType_SPECULAR);
//            textures.insert(textures.begin(), specularTextures.begin(), specularTextures.end());
//        }
//
//        std::initializer_list<VertexBufferDesc> vertexBufferDescs =
//        {
//            VertexBufferDesc
//            {
//                VertexAttributeIndex::Position,
//                sizeof(P3F_N3F_U2F::position) / sizeof(P3F_N3F_U2F::position[0]),
//                VertexFormatType::Float,
//                false,
//                sizeof(P3F_N3F_U2F),
//                offsetof(P3F_N3F_U2F, position),
//            },
//            VertexBufferDesc
//            {
//                VertexAttributeIndex::Normal,
//                sizeof(P3F_N3F_U2F::normal) / sizeof(P3F_N3F_U2F::normal[0]),
//                VertexFormatType::Float,
//                true,
//                sizeof(P3F_N3F_U2F),
//                offsetof(P3F_N3F_U2F, normal),
//            },
//            VertexBufferDesc
//            {
//                VertexAttributeIndex::UV,
//                sizeof(P3F_N3F_U2F::uv) / sizeof(P3F_N3F_U2F::uv[0]),
//                VertexFormatType::Float,
//                false,
//                sizeof(P3F_N3F_U2F),
//                offsetof(P3F_N3F_U2F, uv),
//            },
//        };
//
//        VertexBuffer vertexBuffer(vertices.data(), sizeof(vertices[0]) * vertices.size(), false, vertexBufferDescs);
//        IndexBuffer indexBuffer(indices.data(), sizeof(indices[0]) * indices.size(), false);
//
//        return Mesh(std::string(mesh->mName.C_Str(), mesh->mName.length), std::move(vertexBuffer), std::move(indexBuffer), std::move(textures));
//    }
//
//    std::vector<std::shared_ptr<Texture>> LoadMaterialTextures(aiMaterial* material, aiTextureType textureType)
//    {   
//        auto textureCount = material->GetTextureCount(textureType);
//        std::vector<std::shared_ptr<Texture>> textures(textureCount);
//
//        char modelPathDirectory[256];
//        GetDirectoryName(m_modelPath.c_str(), modelPathDirectory);
//
//        for (int i = 0; i < textureCount; ++i)
//        {
//            aiString texturePath;
//            material->GetTexture(textureType, i, &texturePath);
//
//            std::string textureFullPath = std::string(modelPathDirectory) + "/" + texturePath.C_Str();
//
//            std::shared_ptr<Texture> texture = AssetManager::GetInstance().LoadAsset<Texture>(textureFullPath.c_str());
//            textures[i] = texture;
//        }
//
//        return textures;
//    }
//
//private:
//    std::string m_modelPath;
//    std::vector<Mesh> m_meshes;
//};

//#include <glm/glm/matrix.hpp>
//#include <glm/glm/common.hpp>
//#include <d3d9.h>
//#include <glm/glm/gtx/transform.hpp>
//#include <DirectXMath.h>

/*

shader = std::make_unique<Shader>(g_positionNormalUVVert, g_positionNormalUVFrag);

model = new Model("E:/Users/ggomdyu/Desktop/box.obj");


Model* model = nullptr;
shader->Use();
{
shader->SetParameterMatrix4fv("g_uMVP", &MVP[0][0]);

model->Draw(shader);
}
shader->Unuse();

*/

class A
{
public:
    A& operator=(const A& rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }

        return *this->Clone();
    }

    virtual A* Clone() const
    {
        A* temp = new A;
        temp->a = a;
        return temp;
    }

    int a;
};

class B :
    public A
{
public:
    B& operator=(const B& rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }

        A::operator=(rhs);

        b = rhs.b;

        return *this;
    }

    int b;
};

class TGON_API ThousandParty :
    public GameApplication
{
public:
    TGON_RUNTIME_OBJECT(ThousandParty)

    Texture m_texture;
    Quad m_quad;

public:
    ThousandParty() :
        GameApplication([&]()
    {
        WindowStyle windowStyle;
        {
            auto primaryScreen = GetPrimaryScreen();

            float aspectRatio = (float)primaryScreen.width / (float)primaryScreen.height;

            windowStyle.width = 350 * aspectRatio;
            windowStyle.height = 350 * aspectRatio;
            windowStyle.showMiddle = false;
            windowStyle.enableSystemButton = true;
            windowStyle.hasCaption = true;
            windowStyle.resizeable = true;
        }
        return windowStyle;
    }(),
        [&]()
    {
        VideoMode videoMode;
        {
            videoMode.graphicsSDK = GraphicsSDK::OpenGL4_0;
            videoMode.enableHardwareAccelerate = true;
            videoMode.enableMultiSampling = true;
        }
        return videoMode;
    }()),
        m_texture(GetDesktopDirectory() + "/printTestImage.png"),
        m_quad(FindModule<GraphicsModule>()->GetGraphics()),
        m_shader(g_positionColorVert, g_positionColorFrag)
    {

    }

    ~ThousandParty()
    {

    }

    Shader m_shader;
    Matrix4x4 MVP;

    virtual void OnWillLaunch() override
    {
        SuperType::OnWillLaunch();
    }

    virtual void OnDidLaunch() override
    {
        SuperType::OnDidLaunch();
    }

    virtual void OnUpdate() override
    {
        SuperType::OnUpdate();
        
        decltype(auto) extent = GetRootWindow()->GetSize();

        static float x = 0.0f;
        auto M2 = Matrix4x4::RotateX(x);
        M2 *= Matrix4x4::RotateY(x);
        auto V2 = Matrix4x4::LookAtRH({ 0.0f, 0.0f, 50.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });
        auto P2 = Matrix4x4::PerspectiveRH(Pi / 8.0f, extent.width / extent.height, 0.1f, 1000.0f);
        x -= 0.005f;
        
        MVP = M2 * V2 * P2;

        this->FindModule<GraphicsModule>()->GetGraphics()->ClearColorDepthBuffer();

        m_shader.Use();
        {
            m_shader.SetParameterMatrix4fv("g_uMVP", MVP[0]);

            m_quad.GetVertexBuffer().Use();
            m_quad.GetIndexBuffer().Use();

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        }
        m_shader.Unuse();

        FindModule<GraphicsModule>()->GetGraphics()->SwapBuffer();
    }
};

TGON_DECLARE_APPLICATION(ThousandParty)