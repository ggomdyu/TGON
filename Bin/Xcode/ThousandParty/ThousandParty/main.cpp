#include <iostream>
#include <ctime>
#include <cmath>
#include <string>

#include "Core/Object/Object.h"
#include "Core/Platform/Window.h"
#include "Core/Platform/Time.h"
#include "Core/Platform/Screen.h"
#include "Core/String/FixedString.h"
#include "Core/String/FixedStringUtility.h"
#include "Core/String/StringView.h"
#include "Core/Utility/InstantiateCounter.h"
#include "Core/Utility/AutoCast.h"
#include "Core/Math/Mathematics.h"
#include "Core/Math/Vector3.h"
#include "Core/Math/Color.h"
#include "Graphics/RHI/OpenGL/OpenGLRHI.h"
#include "Game/Engine/GameApplication.h"

#include <vector>
#include <AppKit/NSOpenGL.h>
#include <AppKit/NSOpenGLView.h>
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <OpenGL/gl3.h>
#include <AppKit/NSWindow.h>
#include <limits>

void RotateZ(tgon::math::Vector3& v, float radian)
{
    const float radCos = cosf(radian);
    const float radSin = sinf(radian);

    v.x *= radCos;
    v.y *= -radSin;
}

using namespace tgon;

class TGON_API ThousandParty :
    public engine::GameApplication
{
public:
    ThousandParty() :
        engine::GameApplication([&]()
        {
            platform::WindowStyle windowStyle;
            windowStyle.width = 500;
            windowStyle.height = 500;
            windowStyle.showMiddle = true;
            windowStyle.caption = u8"Caption";

            return windowStyle;
        }())
    {
    };

    virtual void OnUpdate() override
    {

    }

private:
    NSOpenGLView* view;
};

TGON_DECLARE_APPLICATION(ThousandParty)
//TGON_DECLARE_ENGINE(ThousandParty)
