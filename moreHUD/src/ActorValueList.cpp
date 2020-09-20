#include "PCH.h"
#include "ActorValueList.h"


namespace SKSE
{

    ActorValueList* ActorValueList::GetSingleton(void)
    {
        using func_t = decltype(&ActorValueList::GetSingleton);
        REL::Relocation<func_t> func{ REL::ID(514139) };
        return func();
    }


}