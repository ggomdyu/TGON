#include "PrecompiledHeader.pch"

#define TGON_ENABLE_LOG_ON_RELEASE 1
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
#include "Core/Drawing/Image.h"
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
#include "Core/Hash/Hash.h"
#include "Core/Random/Random.h"
#include "Core/Utility/RAII.h"
#include "Core/File/Path.h"
#include "Core/Utility/Windows/HandleGuard.h"
#include "Core/Utility/Stopwatch.h"
#include "Graphics/LowLevelRender/Generic/GenericGraphicsType.h"
#include "Graphics/LowLevelRender/Generic/GenericGraphics.h"
#include "Graphics/LowLevelRender/Texture.h"
#include "Graphics/LowLevelRender/OpenGL/OpenGLShader.h"
#include "Graphics/LowLevelRender/OpenGL/OpenGLShaderCode.h"
#include "Graphics/Render/Renderer.h"
#include "Graphics/Render/MeshUtility.h"
#include "Game/Module/GraphicsModule.h"
#include "Game/Module/TimeModule.h"
#include "Graphics/LowLevelRender/VertexBuffer.h"
#include "Graphics/LowLevelRender/IndexBuffer.h"
#include "Graphics/LowLevelRender/Texture.h"
#include "Graphics/Render/FVF.h"
#include "Game/Module/GraphicsModule.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <al.h>
#include <alc.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "assimp-vc140-mt.lib")
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

class MeshRenderer
{
public:
    MeshRenderer(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material) :
        m_material(material)
    {
    }

public:
    void Draw()
    {
        m_mesh->GetVertexBuffer().Use();
        m_mesh->GetIndexBuffer().Use();

        for (size_t i = 0; i < m_textures.size(); ++i)
        {
            glActiveTexture(GL_TEXTURE0 + i);

            //shader.GetUniformLocation("diffuse");
        }

        //glDrawElements(GL_TRIANGLES, m_indexBuffer.GetDataBytes() / 4, GL_UNSIGNED_INT, nullptr);
    }

private:
    std::shared_ptr<Mesh> m_mesh;
    std::shared_ptr<Material> m_material;
    std::vector<std::shared_ptr<Texture>> m_textures;
};

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
//            //mesh.Draw(shader);
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
//        std::vector<V3F_N3F_T2F> vertices;
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

class WAVImporter
{
    using _AllocatorType = std::allocator<uint8_t>;

public:
    explicit WAVImporter(const char* srcFilePath) : 
        m_buffer(nullptr),
        m_formatType(0),
        m_channels(0),
        m_sampleRate(0),
        m_isValid(false)
    {
    }

    explicit WAVImporter(const uint8_t* srcData) :
        m_isValid(VerifyFormat(srcData))
    {
    }

public:
    
    bool IsValid()
    {
        return false;
    }

private:
    /* @brief   Verifies the importing file is exactly WAV. */
    bool VerifyFormat(const uint8_t* srcData) const
    {
        if (strcmp(reinterpret_cast<const char*>(&srcData[0]), "RIFF") == true)
        {
            return false;
        }

        if (strcmp(reinterpret_cast<const char*>(&srcData[8]), "WAVE") == true)
        {
            return false;
        }

        if (strcmp(reinterpret_cast<const char*>(&srcData[12]), "fmt ") == true)
        {
            return false;
        }

        return true;
    }

private:
    uint8_t* m_buffer;
    short m_formatType;
    short m_channels;
    uint32_t m_sampleRate;
    bool m_isValid;
};

class TGON_API ThousandParty :
    public GameApplication
{
public:
    TGON_RUNTIME_OBJECT(ThousandParty)

    Texture m_texture;
    Cube m_quad;

public:
    ThousandParty() :
        GameApplication(WindowStyle(), VideoMode()),
        m_texture(GetDesktopDirectory() + "/printTestImage.png"),
        m_quad(FindModule<GraphicsModule>()->GetGraphics()),
        m_shader(g_positionUVVert, g_positionUVFrag)
    {
        m_texture.TransferToVideo();
        m_texture.UpdateParemeters();

        FILE* file = fopen("E:/Users/ggomdyu/Desktop/SmallExplosion.wav", "rb");
        
        /*char type[4];
        fread(type, sizeof(char), 4, file);
        if (strcmp(type, "RIFF"))
        {
            assert(false);
        }
        */
        //DWORD size, chunkSize;
        //fread(&size, sizeof(DWORD), 1, file);
        //fread(&chunkSize, sizeof(char), 4, file);


        //short formatType, channels;
        //DWORD sampleRate, avgBytesPerSec;
        //short bytesPerSample, bitsPerSample;
        //DWORD dataSize;

        //
        //fclose(file);

        //ALuint alBuffer;
        //alGenBuffers(1, &alBuffer);
        //auto err = alGetError();
        //if (err != AL_NO_ERROR)
        //{
        //int n = 3;
        //}

        //alBufferData(alBuffer, AL_FORMAT_STEREO16, soundData.data(), soundData.size(), 705);
        //if (err != AL_NO_ERROR)
        //{
        //    int n = 3;
        //}
        //alListener3f(AL_POSITION, 0, 0, 0);
        //if (err != AL_NO_ERROR)
        //{
        //    int n = 3;
        //}
        //alListener3f(AL_VELOCITY, 0,0,0);
        //if (err != AL_NO_ERROR)
        //{
        //    int n = 3;
        //}
        ////

        //ALuint alSource;
        //alGenSources(1, &alSource);
        //if (err != AL_NO_ERROR)
        //{
        //    int n = 3;
        //}
        //alSourcef(alSource, AL_GAIN, 1);
        //if (err != AL_NO_ERROR)
        //{
        //    int n = 3;
        //}
        //alSourcef(alSource, AL_PITCH, 1);
        //if (err != AL_NO_ERROR)
        //{
        //    int n = 3;
        //}
        //alSource3f(alSource, AL_POSITION, 0, 0, 0);
        //if (err != AL_NO_ERROR)
        //{
        //    int n = 3;
        //}

        //alSourcei(alSource, AL_BUFFER, alBuffer);
        //if (err != AL_NO_ERROR)
        //{
        //    int n = 3;
        //}
        //alSourcePlay(alSource);
        //if (err != AL_NO_ERROR)
        //{
        //    int n = 3;
        //}

        int n  =3 ;
    }

    ~ThousandParty()
    {

    }

    Stopwatch m_stopWatch;
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
        
        /*m_stopWatch.Start();
        for (volatile int i = 0; i < 10000000; ++i)
        {
            auto v = m_stopWatch.GetElapsedNanoseconds();
        }
        auto b = m_stopWatch.GetElapsedMilliseconds();
        Log("%d\n", b);*/

        decltype(auto) extent = GetRootWindow()->GetSize();

        static float x = 0.0f;
        auto M2 = Matrix4x4::RotateX(x);
        M2 *= Matrix4x4::RotateX(x);
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

            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
        }
        m_shader.Unuse();

        FindModule<GraphicsModule>()->GetGraphics()->SwapBuffer();
    }
};

TGON_DECLARE_APPLICATION(ThousandParty)