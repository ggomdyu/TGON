#include "PrecompiledHeader.pch"

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
#include "Core/Platform/ScreenType.h"
#include "Core/String/Encoding.h"
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
#include "Graphics/Abstract/OpenGL/OpenGLShader.h"
#include "Graphics/Abstract/OpenGL/OpenGLShaderCode.h"
#include "Graphics/Render/Renderer.h"
#include "Game/Module/GraphicsModule.h"
#include "Game/Module/TimeModule.h"
#include "Graphics/Abstract/VertexBuffer.h"
#include "Graphics/Abstract/IndexBuffer.h"

//#include <glm/glm/matrix.hpp>
//#include <glm/glm/common.hpp>
//#include <d3d9.h>
//#include <glm/glm/gtx/transform.hpp>
//#include <DirectXMath.h>

using namespace tgon;

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
    core::Bitmap m_bitmap;

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
                windowStyle.title = std::string("¾È³ç!!HI!!");
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
        m_bitmap(core::GetDesktopDirectory() + "/printTestImage.png")
    {
        struct V3F_C4B
        {
            core::Vector3 position;
            core::Vector2 uv;
        };

        V3F_C4B v[] =
        {
            {core::Vector3(-1.0f, -1.0f, 0.0f), core::Vector2(0.0f, 0.0f)},
            {core::Vector3(-1.0f, 1.0f, 0.0f), core::Vector2(0.0f, 1.0f)},
            {core::Vector3(1.0f, 1.0f, 0.0f), core::Vector2(1.0f, 1.0f)},
            {core::Vector3(1.0f, -1.0f, 0.0f), core::Vector2(1.0f, 0.0f)},
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
        };

        m_vb = std::make_unique<graphics::VertexBuffer>(v, false, viad);
        m_ib = std::make_unique<graphics::IndexBuffer>(i, false);

        // Create VAO
        glGenVertexArrays(1, &m_vertexArray);
        glBindVertexArray(m_vertexArray);
        {
            m_vb->Use();
            m_ib->Use();
        }
        glBindVertexArray(0);

        shader = std::make_unique<graphics::Shader>(g_positionUVVert, g_positionUVFrag);
        
        GLuint texture;
        glGenTextures(1, &texture);
        auto err = glGetError();
        if (err != 0)
        {
            int n(3);
        }
        glBindTexture(GL_TEXTURE_2D, texture);
        err = glGetError();
        if (err != 0)
        {
            int n(3);
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_bitmap.GetWidth(), m_bitmap.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_bitmap.GetBits().data());
        err = glGetError();
        if (err != 0)
        {
            int n(3);
        }
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        err = glGetError();
        if (err != 0)
        {
            int n(3);
        }
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        err = glGetError();
        if (err != 0)
        {
            int n(3);
        }

       /* glGenerateMipmap(GL_TEXTURE_2D);
*/
        
        {
            const char * utf8_strings = u8"ABab°¡³ª";

            // 
            char buf[256];
            auto wow = core::UTF8::Convert<core::UTF16LE>(utf8_strings, strlen(utf8_strings), buf, 256);

            char buf2[256];
            auto a = core::UTF16LE::GetMaxCharSize() * wow;
            auto wow2 = core::UTF16LE::Convert<core::UTF8>(buf, a, buf2, 256);

            char buf3[256];
            auto wow3 = core::UTF8::Convert<core::UTF16LE>(buf2, strlen(buf2), buf3, 256);

            MessageBoxW(nullptr, (const wchar_t*)buf3, L"", 0);


            // Iterating
            UErrorCode err;
            UConverter* conv = ucnv_open("UTF-8", &err);
            size_t len = strlen(utf8_strings);
            size_t acclen = 0;
            const char* curr = utf8_strings;
            do {
                const char* prev = curr;
                auto ch = ucnv_getNextUChar(conv, &curr, curr + len, &err);
                ++acclen;
            } while (curr < utf8_strings + len);
            ucnv_close(conv);

            core::Log("%d", acclen);
        }
    }

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
        auto M2 = core::Matrix4x4::Translate(0.0f, 0, -x);
        auto V2 = core::Matrix4x4::LookAtRH({ 0.0f, 0.0f, -5.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });
        auto P2 = core::Matrix4x4::PerspectiveRH(3.14159268f / 8.0f, 500.0f / 500.0f, 0.1f, 1000.0f);
        x -= 0.05f;
        
        MVP = M2 * V2 * P2;
        
        glClear(GL_COLOR_BUFFER_BIT);
        shader->Use();
        {
            shader->SetParameterMatrix4fv("g_uMVP", &MVP[0][0]);

            glBindVertexArray(m_vertexArray);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
            glBindVertexArray(0);
        }
        shader->Unuse();

        FindModule<game::GraphicsModule>()->GetGraphics()->SwapBuffer();
    }
};

TGON_DECLARE_APPLICATION(ThousandParty)