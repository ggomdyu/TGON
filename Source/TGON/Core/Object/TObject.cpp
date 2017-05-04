#include "PrecompiledHeader.h"
#include "TObject.h"

#include <cassert>

namespace tgon {
namespace object {

std::shared_ptr<TObject> TObject::Clone() const
{
    assert(false && "Clone is not implemented!");
    return nullptr;
}

} /* namespace object */
} /* namespace tgon */