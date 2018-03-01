/**
 * @filename    GenericShader.h
 * @author      ggomdyu
 * @since       02/17/2018
 */

#pragma once
#include <cstdlib>
#include <cstdint>

namespace tgon
{
namespace graphics
{

class GenericShader
{
/* @section Public destructor */
public:
    virtual ~GenericShader() = 0;

/* @section Public method */
public:
    virtual void Use() = 0;
    virtual void Unuse() = 0;
    
    virtual void SetParameter1f(const char* name, float f) = 0;
    virtual void SetParameter2f(const char* name, float f1, float f2) = 0;
    virtual void SetParameter3f(const char* name, float f1, float f2, float f3) = 0;
    virtual void SetParameter4f(const char* name, float f1, float f2, float f3, float f4) = 0;
    virtual void SetParameterMatrix4fv(const char* name, const float* f) = 0;
    virtual void SetParameter1f(int32_t location, float f) = 0;
    virtual void SetParameter2f(int32_t location, float f1, float f2) = 0;
    virtual void SetParameter3f(int32_t location, float f1, float f2, float f3) = 0;
    virtual void SetParameter4f(int32_t location, float f1, float f2, float f3, float f4) = 0;
    virtual void SetParameterMatrix4fv(int32_t location, const float* f) = 0;
    virtual void SetParameterSampler(int32_t location, uint32_t textureSlot, uint32_t sampler) = 0;

    virtual void BindAttributeLocation(const char* name, uint32_t location) = 0;
    virtual int GetUniformLocation(const char* name) const = 0;

    /* @brief   Checks the shader was loaded successfully. */
    virtual bool IsValid() const noexcept = 0;
};

inline GenericShader::~GenericShader() = default;

} /* namespace graphics */
} /* namespace tgon */
