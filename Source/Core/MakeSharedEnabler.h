#pragma once

namespace tg
{

template <typename _Type>
class MakeSharedEnabler final :
    public _Type
{
/**@section Constructor */
public:
    template <typename... _Args>
    explicit MakeSharedEnabler(_Args&&... args) noexcept;
};

template <typename _Type>
template <typename... _Args>
MakeSharedEnabler<_Type>::MakeSharedEnabler(_Args&&... args) noexcept :
    _Type(std::forward<_Args>(args)...)
{
}

}
