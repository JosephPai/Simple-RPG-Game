#include "MeleeJob.h"

int MeleeJob::GetDamage(Character* cha)
{
    if (cha->GetJob()->GetType()=="Ô¶¾àÀë¹¥»÷ĞÍ(RemoteJob)")
    {
        return 2;
    }

    return 0;
}

string MeleeJob::GetType()
{
    return "½ü¾àÀë¹¥»÷ĞÍ(MeleeJob)";
}
