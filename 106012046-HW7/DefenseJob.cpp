#include "DefenseJob.h"

int DefenseJob::GetDamage(Character* cha)
{
    if (cha->GetJob()->GetType() == "½ü¾àÀë¹¥»÷ĞÍ(MeleeJob)")
    {
        return 2;
    }

    return 0;
}

string DefenseJob::GetType()
{
    return "·ÀÓùÏµ(DefenseJob)";
}
