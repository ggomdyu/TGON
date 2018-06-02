#include "PrecompiledHeader.h"

#include "GenericMouse.h"

namespace tgon
{

GenericMouse::~GenericMouse() = default;

I32Point GenericMouse::GetPosition() const
{
    int32_t x, y;
    this->GetPosition(&x, &y);

    return I32Point(x, y);
}

} /* namespace tgon */
