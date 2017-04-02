#include "PrecompiledHeader.h"
#include "TObject.h"

namespace tgon
{

TObject::~TObject() = default;

std::shared_ptr<TObject> TObject::Clone() const
{
    return nullptr;
}

} /* namespace tgon */
