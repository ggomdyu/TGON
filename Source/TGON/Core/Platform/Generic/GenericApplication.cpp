#include "PrecompiledHeader.h"
#include "GenericApplication.h"

namespace tgon
{

void GenericApplication::ShowOkPopup(const char* message)
{
    ShowOkPopup(message, "", nullptr);
}

void GenericApplication::ShowOkPopup(const char* message, OkPopupEventHandler handler)
{
    ShowOkPopup(message, "", handler);
}

void GenericApplication::ShowOkPopup(const char* message, const char* caption)
{
    ShowOkPopup(message, caption, nullptr);
}

void GenericApplication::ShowYesNoPopup(const char* message)
{
    ShowYesNoPopup(message, "", nullptr);
}

void GenericApplication::ShowYesNoPopup(const char* message, YesNoPopupEventHandler handler)
{
    ShowYesNoPopup(message, "", handler);
}

void GenericApplication::ShowYesNoPopup(const char* message, const char* caption)
{
    ShowYesNoPopup(message, caption, nullptr);
}

}