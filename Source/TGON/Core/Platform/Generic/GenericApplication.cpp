#include "PrecompiledHeader.h"
#include "GenericApplication.h"

namespace tgon {
namespace platform {

//TGON_API void ShowOkPopup(const char* message)
//{
//    ShowOkPopup(message, "", nullptr);
//}

TGON_API void ShowOkPopup(const char* message, OkPopupEventHandler handler)
{
    ShowOkPopup(message, "", handler);
}

//TGON_API void ShowOkPopup(const char* message, const char* caption)
//{
//    ShowOkPopup(message, caption, nullptr);
//}

//TGON_API void ShowYesNoPopup(const char* message)
//{
//    ShowYesNoPopup(message, "", nullptr);
//}
//
//TGON_API void ShowYesNoPopup(const char* message, const char* caption)
//{
//    ShowYesNoPopup(message, caption, nullptr);
//}

} /* namespace platform */
} /* namespace tgon */