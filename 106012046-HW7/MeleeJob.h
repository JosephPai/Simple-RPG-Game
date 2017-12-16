#pragma once
#ifndef MELEEJOB_H
#define MELEEJOB_H
using namespace std;
#include "Job.h"
class MeleeJob :
    public Job
{
public:
    MeleeJob(string name, int extraStr, int extraDex, int extraCon) :Job(name, extraStr, extraDex, extraCon) {}
    virtual int GetDamage(Character* cha);
    string GetType();
};
#endif

