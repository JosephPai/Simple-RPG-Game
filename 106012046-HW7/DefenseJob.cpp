#include "DefenseJob.h"

int DefenseJob::GetDamage(Character* cha)
{
    if (cha->GetJob()->GetType() == "�����빥����(MeleeJob)")
    {
        return 2;
    }

    return 0;
}

string DefenseJob::GetType()
{
    return "����ϵ(DefenseJob)";
}
