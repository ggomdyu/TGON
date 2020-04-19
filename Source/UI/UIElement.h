#pragma once

#include <vector>

#include "Core/RuntimeObject.h"

#include "UIBatch.h"

namespace tg
{

class UIElement :
    public RuntimeObject
{
public:
    TGON_DECLARE_RTTI(UIElement)

/**@section Constructor */
public:
    UIElement();

/**@section Method */
public:
    virtual void GetBatches(std::vector<UIBatch>* batches, const Matrix4x4& matWorld, std::vector<float>* vertices) const = 0;
    void SetMaterial(std::shared_ptr<Material>&& material) noexcept;
    void SetMaterial(const std::shared_ptr<Material>& material) noexcept;
    std::shared_ptr<Material> GetMaterial() noexcept;
    std::shared_ptr<const Material> GetMaterial() const noexcept;

private:
    void InitializeDefaultMaterial();

/**@section Variable */
protected:
    std::shared_ptr<Material> m_material;
    inline static std::shared_ptr<Material> m_defaultMaterial;

};

}
