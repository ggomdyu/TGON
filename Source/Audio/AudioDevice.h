#pragma once

#include <optional>

#include "Core/RuntimeObject.h"

struct ALCdevice;
struct ALCcontext;

namespace tg
{

class AudioDevice final :
    public RuntimeObject
{
public:
    TGON_DECLARE_RTTI(AudioDevice)

/**@section Constructor */
public:
    AudioDevice(const std::shared_ptr<ALCdevice>& device, const std::shared_ptr<ALCcontext>& context) noexcept;
    
/**@section Method */
public:
    static std::optional<AudioDevice> Create();
    void MakeCurrent();
    std::shared_ptr<ALCdevice> GetDevice() noexcept;
    std::shared_ptr<const ALCdevice> GetDevice() const noexcept;
    std::shared_ptr<ALCcontext> GetContext() noexcept;
    std::shared_ptr<const ALCcontext> GetContext() const noexcept;

/**@section Variable */
private:
    std::shared_ptr<ALCdevice> m_device;
    std::shared_ptr<ALCcontext> m_context;
};

}
