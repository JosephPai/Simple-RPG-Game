#include "MeleeJob.h"

int MeleeJob::GetDamage(Character* cha)
{
    if (cha->GetJob()->GetType()=="Զ���빥����(RemoteJob)")
    {
        return 2;
    }

    return 0;
}

string MeleeJob::GetType()
{
    return "�����빥����(MeleeJob)";
}
