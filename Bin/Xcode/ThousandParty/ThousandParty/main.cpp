#include "PrecompiledHeader.pch"

#define TGON_USING_OPENGL 1
#include "Game/Engine/GameApplication.h"

#include "Core/Random/Random.h"
#include "Core/Object/Object.h"
#include "Core/Platform/Window.h"
#include "Core/Platform/Generic/GenericWindowType.h"
#include "Core/File/Path.h"
#include "Core/Platform/Time.h"
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
#include "Core/Utility/Cast.h"
#include "Core/Math/Mathematics.h"
#include "Core/Math/Vector3.h"
#include "Core/Math/Vector2.h"
#include "Core/Math/Color.h"
#include "Core/Math/Matrix4x4.h"
#include "Core/Math/Extent.h"
#include "Core/Hash/UUID.h"
#include "Graphics/Abstract/Generic/GenericGraphicsType.h"
#include "Graphics/Abstract/Generic/GenericGraphics.h"
#include "Graphics/Abstract/Texture.h"
#include "Graphics/Abstract/OpenGL/OpenGLShader.h"
#include "Graphics/Abstract/OpenGL/OpenGLShaderCode.h"
#include "Graphics/Render/Renderer.h"
#include "Game/Module/GraphicsModule.h"
#include "Game/Module/TimeModule.h"
#include "Graphics/Abstract/VertexBuffer.h"
#include "Graphics/Abstract/IndexBuffer.h"
#include "Graphics/Abstract/Texture.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#pragma comment(lib, "assimp-vc140-mtd.lib")
#pragma comment(lib, "IrrXML.lib")

using namespace tgon;

class Mesh
{
public:
    template <typename _StringType, typename _VertexBufferType, typename _IndexBufferType>
    Mesh(_StringType&& name, _VertexBufferType&& vertexBuffer, _IndexBufferType&& indexBuffer) :
        m_name(std::forward<_StringType>(name)),
        m_vertexBuffer(std::forward<_VertexBufferType>(vertexBuffer)),
        m_indexBuffer(std::forward<_IndexBufferType>(indexBuffer))
    {
    }

public:
    void Draw()
    {
        m_vertexBuffer.Use();
        m_indexBuffer.Use();

        glDrawElements(GL_TRIANGLES, m_indexBuffer.GetDataBytes() / 4, GL_UNSIGNED_INT, nullptr);
    }

    const graphics::VertexBuffer& GetVertexBuffer() const
    {
        return m_vertexBuffer;
    }

    const graphics::IndexBuffer& GetIndexBuffer() const
    {
        return m_indexBuffer;
    }

private:
    std::string m_name;
    graphics::VertexBuffer m_vertexBuffer;
    graphics::IndexBuffer m_indexBuffer;
    std::vector<graphics::Texture> m_textures;
};

class Material
{
public:

};

class Light
{
};

class DirectionalLight :
    public Light
{
public:
};

class Model
{
public:
    Model(const std::string& modelFilePath) :
        m_modelFilePath(modelFilePath)
    {
        this->ImportModel(modelFilePath);
    }

public:
    void Draw()
    {
        for (auto& mesh : m_meshes)
        {
            mesh.Draw();
        }
    }

private:
    bool ImportModel(const std::string& modelFilePath)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(modelFilePath, aiProcess_Triangulate | aiProcess_FlipUVs);
        if (scene == nullptr)
        {
            return false;
        }

        aiNode* rootNode = scene->mRootNode;
        if (scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || rootNode == nullptr)
        {
            return false;
        }

        this->ProcessModelNode(rootNode, scene);

        return true;
    }

    void ProcessModelNode(const aiNode* node, const aiScene* scene)
    {
        m_meshes.reserve(m_meshes.capacity() + node->mNumMeshes);

        for (unsigned int i = 0; i < node->mNumMeshes; ++i)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            m_meshes.push_back(ProcessModelMesh(mesh, scene));
        }

        for (unsigned int i = 0; i < node->mNumChildren; ++i)
        {
            this->ProcessModelNode(node->mChildren[i], scene);
        }
    }

    Mesh ProcessModelMesh(const aiMesh* mesh, const aiScene* scene)
    {
        struct V3F_N4F_C2B
        {
            core::Vector3 position;
            core::Vector3 color;
        };

        std::vector<V3F_N4F_C2B> vertices;
        {
            vertices.reserve(mesh->mNumVertices);

            // Fill the vertex information
            for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
            {
                const auto& position = mesh->mVertices[i];
                const auto& normal = mesh->mNormals[i];

                if (mesh->HasTextureCoords(0))
                {
                    const auto& uv = mesh->mTextureCoords[0][i];

                    vertices.push_back(V3F_N4F_C2B{
                        core::Vector3(position.x, position.y, position.z),
                        //core::Vector3(normal.x, normal.y, normal.z),
                        core::Vector3(1.0f, 1.0f, 1.0f)
                        });
                }
                else
                {
                    vertices.push_back(V3F_N4F_C2B{
                        core::Vector3(position.x, position.y, position.z),
                        //core::Vector3(normal.x, normal.y, normal.z),
                        core::Vector3(1.0f, 1.0f, 1.0f)
                        //core::Vector2(0, 0)
                        });
                }
            }
        }

        std::vector<unsigned int> indices;
        {
            indices.reserve(mesh->mNumFaces * 3);

            for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
            {
                aiFace& face = mesh->mFaces[i];
                for (unsigned j = 0; j < face.mNumIndices; ++j)
                {
                    indices.push_back(face.mIndices[j]);
                }
            }
        }

        std::initializer_list<graphics::VertexBufferDesc> vertexBufferDescs =
        {
            graphics::VertexBufferDesc
            {
                graphics::VertexAttributeIndex::Position,
                3,
                graphics::VertexFormatType::Float,
                false,
                sizeof(V3F_N4F_C2B),
                offsetof(V3F_N4F_C2B, position),
            },
            graphics::VertexBufferDesc
            {
                graphics::VertexAttributeIndex::UV,
                3,
                graphics::VertexFormatType::Float,
                true,
                sizeof(V3F_N4F_C2B),
                offsetof(V3F_N4F_C2B, color),
            },
        };

        graphics::VertexBuffer vertexBuffer(vertices.data(), sizeof(vertices[0]) * vertices.size(), false, vertexBufferDescs);
        graphics::VertexBuffer vertexBuffer2(vertices.data(), sizeof(vertices[0]) * vertices.size(), false, vertexBufferDescs);
        graphics::IndexBuffer indexBuffer(indices.data(), sizeof(indices[0]) * indices.size(), false);

        vertexBuffer = std::move(vertexBuffer2);

        return Mesh(std::string(mesh->mName.C_Str(), mesh->mName.length), std::move(vertexBuffer), std::move(indexBuffer));
    }

private:
    std::string m_modelFilePath;
    std::vector<Mesh> m_meshes;
};

//#include <glm/glm/matrix.hpp>
//#include <glm/glm/common.hpp>
//#include <d3d9.h>
//#include <glm/glm/gtx/transform.hpp>
//#include <DirectXMath.h>

template <typename T>
void PrintMat(const T& matA)
{
    core::Log("%f   %f  %f  %f\n%f   %f  %f  %f\n%f   %f  %f  %f\n%f   %f  %f  %f\n",
        matA[0][0], matA[0][1], matA[0][2], matA[0][3],
        matA[1][0], matA[1][1], matA[1][2], matA[1][3],
        matA[2][0], matA[2][1], matA[2][2], matA[2][3],
        matA[3][0], matA[3][1], matA[3][2], matA[3][3]);
}

class TGON_API ThousandParty :
    public game::GameApplication
{
public:
    TGON_RUNTIME_OBJECT(ThousandParty)

        GLuint m_vertexArray = 0;
    graphics::Texture m_texture;

public:
    ThousandParty() :
        game::GameApplication([&]()
    {
        core::WindowStyle windowStyle;
        {
            auto primaryScreen = core::GetPrimaryScreen();

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
        graphics::VideoMode videoMode;
        {
            videoMode.graphicsSDK = graphics::GraphicsSDK::OpenGL4_0;
            videoMode.enableHardwareAccelerate = true;
            videoMode.enableMultiSampling = true;
        }
        return videoMode;
    }()),
        m_texture(core::GetDesktopDirectory() + "/printTestImage.png")
    {
        /*struct V3F_C4B
        {
            core::Vector3 position;
            core::Vector2 uv;
        };

        V3F_C4B v[] =
        {
            { core::Vector3(-1.0f, -1.0f, 0.0f), core::Vector2(0.0f, 0.0f) },
            { core::Vector3(-1.0f, 1.0f, 0.0f), core::Vector2(0.0f, 1.0f) },
            { core::Vector3(1.0f, 1.0f, 0.0f), core::Vector2(1.0f, 1.0f) },
            { core::Vector3(1.0f, -1.0f, 0.0f), core::Vector2(1.0f, 0.0f) },
        };

        unsigned int i[] =
        {
            0,1,2,0,2,3
        };

        std::initializer_list<graphics::VertexBufferDesc> viad =
        {
            graphics::VertexBufferDesc
            {
                graphics::VertexAttributeIndex::Position,
                3,
                graphics::VertexFormatType::Float,
                false,
                sizeof(V3F_C4B),
                offsetof(V3F_C4B, position),
            },
            graphics::VertexBufferDesc
            {
                graphics::VertexAttributeIndex::UV,
                2,
                graphics::VertexFormatType::Float,
                true,
                sizeof(V3F_C4B),
                offsetof(V3F_C4B, uv),
            },
        };*/
        
        std::string language = core::GetLanguage().c_str();
        ShowMessageBox(language.c_str());

        //m_vb = std::make_unique<graphics::VertexBuffer>(v, false, viad);
        //m_ib = std::make_unique<graphics::IndexBuffer>(i, false);

        //// Create VAO
        //glGenVertexArrays(1, &m_vertexArray);
        //glBindVertexArray(m_vertexArray);
        //{
        //    m_vb->Use();
        //    m_ib->Use();
        //}
        //glBindVertexArray(0);

        //shader = std::make_unique<graphics::Shader>(g_positionUVVert, g_positionUVFrag);

        shader = std::make_unique<graphics::Shader>(g_positionColorVert, g_positionColorFrag);

        /*m_texture.SetWrapMode(graphics::TextureWrapMode::Clamp);
        m_texture.TransferToVideo();
        m_texture.UpdateParemeters();*/

        model = new Model("E:/Users/ggomdyu/Desktop/box.obj");
    }

    Model* model;

    ~ThousandParty()
    {
        // Release VAO
        glBindVertexArray(0);
        glDeleteVertexArrays(1, &m_vertexArray);
    }

    std::unique_ptr<graphics::VertexBuffer> m_vb;
    std::unique_ptr<graphics::IndexBuffer> m_ib;
    std::unique_ptr<graphics::Shader> shader;
    core::Matrix4x4 MVP;

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

        static float x = 0.0f;
        auto M2 = core::Matrix4x4::Translate(0.0f, 0, x);
        auto V2 = core::Matrix4x4::LookAtRH({ 0.0f, 0.0f, 5.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });
        auto P2 = core::Matrix4x4::PerspectiveRH(3.14159268f / 8.0f, 500.0f / 500.0f, 0.1f, 1000.0f);
        x -= 0.05f;

        MVP = M2 * V2 * P2;

        glClear(GL_COLOR_BUFFER_BIT);
        shader->Use();
        {
            model->Draw();
        }
        shader->Unuse();

       /* shader->Use();
        {
            shader->SetParameterMatrix4fv("g_uMVP", &MVP[0][0]);

            glBindVertexArray(m_vertexArray);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
            glBindVertexArray(0);
        }
        shader->Unuse();
*/
        FindModule<game::GraphicsModule>()->GetGraphics()->SwapBuffer();
    }
};

TGON_DECLARE_APPLICATION(ThousandParty)
