#include "PrecompiledHeader.pch"

#define TGON_ENABLE_LOG_ON_RELEASE 1
#define TGON_USING_OPENGL 1
#include "Game/Engine/GameApplication.h"

#include "Core/Utility/StaticInvoke.h"
#include "Core/Audio/AudioBuffer.h"
#include "Core/Audio/AudioPlayer.h"
#include "Core/Random/Random.h"
#include "Core/Object/Object.h"
#include "Game/Object/GameObject.h"
#include "Game/Object/Component.h"
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
#include "Core/Audio/Importer/Wav/WavAudioImporter.h"
#include "Core/Audio/Importer/OggVorbis/OggVorbisAudioImporter.h"
#include "Core/Random/Random.h"
#include "Core/Utility/RAII.h"
#include "Core/File/Path.h"
#include "Core/Utility/Windows/HandleGuard.h"
#include "Core/Utility/Stopwatch.h"
#include "Core/Utility/Algorithm.h"
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
        m_mesh->GetVertexBuffer()->Use();
        m_mesh->GetIndexBuffer()->Use();

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

using tgon::UnderlyingCast;

// see: https://www.media.mit.edu/pia/Research/deepview/exif.html

class ExifHeader
{
    /* @section Public enum */
public:
    enum class TagID : uint16_t
    {
        ImageWidth = 0x0100,
        ImageHeight = 0x0101,
        DateTimeOriginal = 0x9003,
    };

public:
    
};

class JPGImageProcessor
{
/* @section Private class */
private:
    

/* @section Private enum */
private:
    enum class MarkerType : uint16_t
    {
        SOI = 0xD8FF,
        APP0 = 0xE0FF,
        APP1 = 0xE1FF,
        APP2 = 0xE2FF,
        APP3 = 0xE3FF,
        APP4 = 0xE4FF,
        APP5 = 0xE5FF,
        APP6 = 0xE6FF,
        APP7 = 0xE7FF,
        APP8 = 0xE8FF,
        APP9 = 0xE9FF,
        APP10 = 0xEAFF,
        APP11 = 0xEBFF,
        APP12 = 0xECFF,
        APP13 = 0xEDFF,
        APP14 = 0xEEFF,
        APP15 = 0xEFFF,
        DQT = 0xDBFF,
        SOF0 = 0xC0FF,
        SOF1 = 0xC1FF,
        SOF2 = 0xC2FF,
        SOF3 = 0xC3FF,
        SOF4 = 0xC4FF,
        SOF5 = 0xC5FF,
        SOF6 = 0xC6FF,
        SOF7 = 0xC7FF,
        SOF8 = 0xC8FF,
        SOF9 = 0xC9FF,
        SOF10 = 0xCAFF,
        SOF11 = 0xCBFF,
        SOF12 = 0xCCFF,
        SOF13 = 0xCDFF,
        SOF14 = 0xCEFF,
        SOF15 = 0xCFFF,
        DHT = 0xC4FF,
        SOS = 0xDAFF,
        DRI = 0xDDFF,
        RST0 = 0xD0FF,
        RST1 = 0xD1FF,
        RST2 = 0xD2FF,
        RST3 = 0xD3FF,
        RST4 = 0xD4FF,
        RST5 = 0xD5FF,
        RST6 = 0xD6FF,
        RST7 = 0xD7FF,
        RST8 = 0xD8FF,
        RST9 = 0xD9FF,
        RST10 = 0xDAFF,
        RST11 = 0xDBFF,
        RST12 = 0xDCFF,
        RST13 = 0xDDFF,
        RST14 = 0xDEFF,
        RST15 = 0xDFFF,
        DNL = 0xDCFF,
        EOI = 0xD9FF,
        COM = 0xFEFF,
    };

/* @section Public method */
public:
    void Import(const uint8_t* srcFile)
    {
        const uint8_t* iter = srcFile;
        while (true)
        {
            MarkerType markerType = static_cast<MarkerType>(*reinterpret_cast<const uint16_t*>(iter));
            iter += sizeof(markerType);

            switch (markerType)
            {
            case MarkerType::SOI:
                {
                    int n = 3;
                }
                break;

            case MarkerType::APP1:
                {
                    char chunkSizeStr[2] = {*(iter + 1), *iter};
                    uint16_t chunkSize = *reinterpret_cast<const uint16_t*>(chunkSizeStr);

                    const uint8_t* exifIter = iter;
                    while (true)
                    {
                        // Byte align
                        exifIter += 8;
                        bool isMotorolaAlign = (*reinterpret_cast<const uint16_t*>(exifIter)) == 0x4D4D;

                        // TAG Mark
                        exifIter += 2;
                        auto tagMark = Parse<uint16_t>(exifIter, isMotorolaAlign);

                        // TAG Mark
                        exifIter += 2;
                        uint32_t offsetToFirstIFD = Parse<uint32_t>(exifIter, isMotorolaAlign);

                        exifIter += 4;
                        uint16_t dirEntryCount = Parse<uint16_t>(exifIter, isMotorolaAlign);
                        
                        // IFD
                        while (true)
                        {
                            exifIter += (12 * dirEntryCount) + 2; // We will jump IFD.
                            uint32_t offsetToNextIFD = Parse<uint32_t>(exifIter, isMotorolaAlign);
                            if (offsetToNextIFD == 0)
                            {
                                break;
                            }
                            else
                            {
                                exifIter += offsetToNextIFD;
                            }
                        }

                        //uint16_t dirEntryCount = Parse<uint16_t>(exifIter, isMotorolaAlign);


                        int n = 3;
                    }

                    iter += chunkSize;

                    break;
                }

            case MarkerType::EOI:    
                return;
            }
        }

    }

    template <typename _ParseValueType>
    _ParseValueType Parse(const uint8_t* srcData, bool isMotorolaAlign)
    {
        if (isMotorolaAlign)
        {
            uint8_t temp[sizeof(_ParseValueType)] {};
            for (int i = 0; i < sizeof(_ParseValueType); ++i)
            {
                temp[i] = *((srcData + sizeof(_ParseValueType) - 1) - i);
            }

            return *reinterpret_cast<const _ParseValueType*>(temp);
        }
        else
        {
            return *reinterpret_cast<const _ParseValueType*>(srcData);
        }
    }

private:
    ExifHeader m_exifHeader;
};

template <typename _CastToType, typename _CastFromType, std::enable_if<std::is_convertible_v<_CastFromType, _CastToType>>* = nullptr>
inline _CastToType DynamicCast2(_CastFromType ptr)
{
    return nullptr;
}

template <typename _CastToType, typename _CastFromType, std::enable_if_t<!std::is_convertible_v<_CastFromType, _CastToType>>* = nullptr>
inline _CastToType DynamicCast2(_CastFromType ptr)
{
    return nullptr;
}

class CC : public Component
{
public:
    TGON_RUNTIME_OBJECT(CC)
    CC(GameObject* owner) :Component(owner) {};
    virtual ~CC() override {}
    virtual void Update() override {}
};


class TGON_API ThousandParty final :
    public GameApplication
{
public:
    TGON_RUNTIME_OBJECT(ThousandParty)

    std::shared_ptr<Texture> m_texture;
    std::shared_ptr<Mesh> m_quad;

    std::shared_ptr<AudioBuffer> audioBuffer = std::make_shared<AudioBuffer>("E:/Users/ggomdyu/Desktop/Sulk.wav");
    AudioPlayer audioPlayer;

public:
    ThousandParty() :
        GameApplication(WindowStyle(), VideoMode()),
        m_texture(std::make_shared<Texture>(GetDesktopDirectory() + "/printTestImage.png")),
        m_quad(MakeCube(std::make_shared<GrayscaleTextureMaterial>())),
        m_shader(g_positionColorVert, g_positionColorFrag)
    {
        audioPlayer.SetAudioBuffer(audioBuffer);
        audioPlayer.SetListenerPosition({ 0, 0, 0 });
        audioPlayer.SetListenerVelocity({ 0, 0, 0 });
        audioPlayer.SetPosition({ 0, 0, 0 });
        audioPlayer.SetPitch(1.0f);
        audioPlayer.SetVolume(0.2f);
        audioPlayer.Play();

        std::static_pointer_cast<GrayscaleTextureMaterial>(m_quad->GetMaterial())->SetTexture(m_texture);
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
        
        static float x = 5.0f;
        auto M2 = Matrix4x4::RotateX(x);
        M2 *= Matrix4x4::RotateX(x);
        M2 *= Matrix4x4::RotateY(x);
        auto V2 = Matrix4x4::LookAtRH({ 0.0f, 0.0f, 50.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });
        auto P2 = Matrix4x4::PerspectiveRH(Pi / 8.0f, extent.width / extent.height, 0.1f, 1000.0f);
        x -= 0.1f;

        bool a2 = false;
        if (a2)
        {
            audioPlayer.Pause();
        }
        
        bool b = false;
        if (b)
        {
            audioPlayer.Resume();
        }

        MVP = M2 * V2 * P2;

        float a = audioPlayer.GetTotalProgressInSeconds();
        audioPlayer.SetPosition({x, 0,0});

        auto& mtrl = m_quad->GetMaterial();
 
        this->FindModule<GraphicsModule>()->GetGraphics()->ClearColorDepthBuffer();

        mtrl->Use();
        {
            mtrl->GetShader()->SetParameterMatrix4fv("g_uMVP", MVP[0]);
            
            m_quad->GetVertexBuffer()->Use();
            m_quad->GetIndexBuffer()->Use();

            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
        }
        mtrl->Unuse();

        FindModule<GraphicsModule>()->GetGraphics()->SwapBuffer();
    }
};

TGON_DECLARE_APPLICATION(ThousandParty)