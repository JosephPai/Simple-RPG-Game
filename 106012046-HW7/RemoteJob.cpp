#include "RemoteJob.h"

int RemoteJob::GetDamage(Character* cha)
{
    if (cha->GetJob()->GetType() == "·ÀÓùÏµ(DefenseJob)")
    {
        return 2;
    }

    return 0;
}

string RemoteJob::GetType()
{
    return "Ô¶¾àÀë¹¥»÷ĞÍ(RemoteJob)";
}
