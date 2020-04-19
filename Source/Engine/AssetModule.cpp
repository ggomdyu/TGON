#include "PrecompiledHeader.h"

#include "Diagnostics/Debug.h"

#include "AssetModule.h"

namespace tg
{

AssetModule::AssetModule() :
    m_fontFactory([]()
    {
        auto fontFactory = FontFactory::Create();
        if (fontFactory.has_value() == false)
        {
            Debug::Fail("Failed to create FontFactory.");
        }

        return std::move(*fontFactory);
    } ())
{
}

}
