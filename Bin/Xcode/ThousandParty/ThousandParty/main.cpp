#include "PrecompiledHeader.h"

#include "TGON.h"
#include "TestScene.h"

using namespace tgon;

class TGON_API ThousandParty final :
    public Engine
{
public:
    TGON_RUNTIME_OBJECT(ThousandParty);

/* @section Public constructor */
public:
    ThousandParty()
    {
        this->Initialize();
    }

/* @section Private method */
private:
    void Initialize()
    {
        InputMode inputMode;
        {
            inputMode.isUseMouse = false;
            inputMode.isUseKeyboard = true;
            inputMode.isUseGamepad = false;
        }
        this->AddModule<InputModule>(inputMode, Application::GetInstance()->GetRootWindow());
        this->AddModule<TimeModule>();
        this->AddModule<SceneModule>(std::make_unique<TestScene>(), Application::GetInstance()->GetRootWindow(), VideoMode{});
    }

    void Terminate()
    {
    }
    
/* @section Public method */
public:
    virtual void Update() override
    {
        SuperType::Update();
    }
};

TGON_DECLARE_ENGINE(ThousandParty);

