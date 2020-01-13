/**
 * @file    UIElement.h
 * @author  ggomdyu
 * @since   11/20/2019
 */

#pragma once
#include <vector>

#include "Core/NonCopyable.h"

#include "UIBatch.h"

namespace tgon
{

class UIElement :
    private NonCopyable
{
/**@section Destructor */
public:
    virtual ~UIElement() = default;
    
/**@section Method */
public:
    virtual void GetBatches(std::vector<UIBatch>* batches, const Matrix4x4& matWorld, std::vector<float>* vertices) const = 0;
    void SetMaterial(std::shared_ptr<Material>&& material) noexcept;
    void SetMaterial(const std::shared_ptr<Material>& material) noexcept;
    std::shared_ptr<Material> GetMaterial() noexcept;
    std::shared_ptr<const Material> GetMaterial() const noexcept;

/**@section Variable */
protected:
    std::shared_ptr<Material> m_material;
};

} /* namespace tgon */
