#include "RemoteJob.h"

int RemoteJob::GetDamage(Character* cha)
{
    if (cha->GetJob()->GetType() == "����ϵ(DefenseJob)")
    {
        return 2;
    }

    return 0;
}

string RemoteJob::GetType()
{
    return "Զ���빥����(RemoteJob)";
}
