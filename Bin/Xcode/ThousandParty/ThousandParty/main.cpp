#include "PrecompiledHeader.h"

#include "TGON.h"
#include "TestScene.h"

#include <GL/glew.h>

using namespace tgon;

class TGON_API ThousandParty final :
    public Engine
{
public:
    TGON_RUNTIME_OBJECT(ThousandParty);

/* @section Public event handler */
public:
    ThousandParty()
    {
    }

    virtual void OnDidLaunch() override
    {
        SuperType::OnDidLaunch();
        
        InputMode inputMode;
        {
            inputMode.isUseMouse = false;
            inputMode.isUseKeyboard = true;
            inputMode.isUseGamepad = false;
        }
        this->AddModule<InputModule>(inputMode, Application::GetInstance().GetRootWindow());
        
        this->AddModule<TimeModule>();
        
        this->AddModule<SceneModule>(std::make_unique<TestScene>(), Application::GetInstance().GetRootWindow(), VideoMode{});

        // Create a frame buffer.
//        GLuint frameBufferId = 0;
//        glGenFramebuffers(1, &frameBufferId);
//        glBindFramebuffer(GL_FRAMEBUFFER, frameBufferId);
//    
//        
//        // We will create a texture which contains RGB.
//        GLuint colorRenderTexture;
//        glGenTextures(1, &colorRenderTexture);
//        glBindTexture(GL_TEXTURE_2D, colorRenderTexture);
//        // Fill the empty image.
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1024, 768, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
//        //
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//
//    
//        // Create a Depth buffer.
//        GLuint depthRenderBuffer;
//        glGenRenderbuffers(1, &depthRenderBuffer);
//        glBindRenderbuffer(GL_RENDERBUFFER, depthRenderBuffer);
//        
//        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1024, 768);
//        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderBuffer);
//        
//        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, colorRenderTexture, 0);
//        GLenum bufferToDraw[] = {GL_COLOR_ATTACHMENT0};
//        glDrawBuffers(1, bufferToDraw);
//        
//        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//        {
//        }
//        
//        m_sharedMesh = MakeTriangle();
    }

    virtual void OnWillTerminate() override
    {
        SuperType::OnWillTerminate();
    }
    
/* @section Public method */
public:
    virtual void Update() override
    {
        SuperType::Update();
    }
    
private:
    std::shared_ptr<Mesh> m_sharedMesh;
};

TGON_DECLARE_ENGINE(ThousandParty);

