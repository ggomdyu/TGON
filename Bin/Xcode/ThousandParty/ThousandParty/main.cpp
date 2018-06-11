#include "PrecompiledHeader.h"

#include "TGON.h"

using namespace tgon;

class TGON_API ThousandParty final :
    public Engine
{
public:
    TGON_RUNTIME_OBJECT(ThousandParty);
    
public:
    ThousandParty()
    {
    }

/* @section Public destructor */
public:
    virtual ~ThousandParty()
    {
        int n = 3;
    }

/* @section Public event handler */
public:
    virtual void Update() override
    {
    }
};

TGON_DECLARE_ENGINE(ThousandParty);
