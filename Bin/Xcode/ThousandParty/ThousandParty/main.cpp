#include "PrecompiledHeader.pch"

#include "Game/Engine/GameApplication.h"

#include "Core/Random/Random.h"
#include "Core/Object/Object.h"
#include "Core/Platform/ApplicationType.h"
#include "Core/Platform/Window.h"
#include "Core/Platform/WindowType.h"
#include "Core/Platform/Time.h"
#include "Core/Debug/Log.h"
#include "Core/Platform/Screen.h"
#include "Core/String/FixedString.h"
#include "Core/String/FixedStringUtility.h"
#include "Core/String/StringView.h"
#include "Core/Utility/InstantiateCounter.h"
#include "Core/Utility/AutoCast.h"
#include "Core/Math/Mathematics.h"
#include "Core/Math/Vector3.h"
#include "Core/Math/Color.h"
#include "Core/Math/Matrix4x4.h"
#include "Core/Math/Extent.h"
#include "Core/Hash/UUID.h"
#include "Graphics/RHI/RHIType.h"
#include "Graphics/RHI/IDynamicRHI.h"
#include "Graphics/RHI/OpenGL/OpenGLShader.h"
#include "Graphics/RHI/OpenGL/OpenGLShaderCode.h"
#include "Graphics/Render/Renderer.h"
#include "Game/Module/GraphicsModule.h"
#include "Game/Module/TimeModule.h"

#include "Graphics/RHI/VertexBuffer.h"

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

using namespace tgon;
class TGON_API ThousandParty :
    public game::GameApplication
{
public:
    TGON_RUNTIME_OBJECT(ThousandParty)

    GLuint m_indexBuffer;
    GLuint m_vertexArray = 0;

public:
    ThousandParty() :
        game::GameApplication([&]()
        {
            core::WindowStyle windowStyle;
            {
                windowStyle.width = 500;
                windowStyle.height = 500;
                windowStyle.showMiddle = true;
                windowStyle.title = u8"ㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋ";
                windowStyle.enableSystemButton = true;
                windowStyle.hasCaption = true;
                windowStyle.resizeable = false;
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
        }())
    {
        struct V3F_C4B
        {
            core::Vector3 position;
        };

        V3F_C4B v[] =
        {
            {core::Vector3(-1.0f, -1.0f, 0.0f)},
            {core::Vector3(-1.0f, 1.0f, 0.0f)},
            {core::Vector3(1.0f, 1.0f, 0.0f)},
            {core::Vector3(1.0f, -1.0f, 0.0f)},
        };
        unsigned int i[] =
        {
            0,1,2,0,2,3
        };
        std::initializer_list<graphics::VertexInputAttributeDescription> viad =
        {
            graphics::VertexInputAttributeDescription
            {
                graphics::VertexAttributeType::Position,
                3,
                graphics::VertexType::Float,
                false,
                0,
                offsetof(V3F_C4B, position),
            }
        };

        vb = new graphics::VertexBuffer(v, viad);
        
        // Create INDEX BUFFER
        glGenBuffers(1, &m_indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(i), i, GL_STATIC_DRAW);

        // Create VAO
        glGenVertexArrays(1, &m_vertexArray);
        glBindVertexArray(m_vertexArray);
        {
            vb->BeginScene();
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
        }
        glBindVertexArray(0);

        shader = new graphics::OpenGLShader();
        bool ss  = shader->Initialize(g_positionColorVert, g_positionColorFrag);
        if (ss)
        {
            int n = 3;
        }

        auto e = glGetError();
    }

    ~ThousandParty()
    {
        // Release VAO
        glBindVertexArray(0);
        glDeleteVertexArrays(1, &m_vertexArray);

        delete vb;
    }

    graphics::VertexBuffer* vb;
    graphics::OpenGLShader* shader;
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
        auto M2 = core::Matrix4x4::Translate(x, 0.0f, 0.0f);
        auto V2 = core::Matrix4x4::LookAtRH({ 0.0f, 0.0f, -5.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });
        auto P2 = core::Matrix4x4::PerspectiveRH(3.14159268f / 8.0f, 500.0f / 500.0f, 0.1f, 1000.0f);
        x += 0.005f;
        
        MVP = M2 * V2 * P2;
        

        glClear(GL_COLOR_BUFFER_BIT);
        shader->BeginScene();
        {
            shader->SetParameterMatrix4fv("g_uMVP", &MVP[0][0]);

            glBindVertexArray(m_vertexArray);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
            glBindVertexArray(0);
        }
        shader->EndScene();

        /*
        static float x = 0.0f;
        static float y = 0.0f;

        float newX = std::sin(x += 0.01);
        float newY = std::sin(y += 0.01);

        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_TRIANGLES);
        glVertex2f(0.0 + newX, 0.5 + newY);
        glVertex2f(-0.5 + newX, -0.5 + newY);
        glVertex2f(0.5 + newX, -0.5 + newY);
        glEnd();
        glFinish();
        */

        FindModule<game::GraphicsModule>()->GetRHI()->SwapBuffer();
    }
};
TGON_DECLARE_APPLICATION(ThousandParty)
