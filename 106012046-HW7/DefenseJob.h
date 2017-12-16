#pragma once
#ifndef DEFENSEJOB_H
#define DEFENSEJOB_H
using namespace std;
#include "Job.h"
class DefenseJob :
    public Job
{
public:
    DefenseJob(string name, int extraStr, int extraDex, int extraCon):Job(name,extraStr,extraDex,extraCon) {}
    virtual int GetDamage(Character* cha);
    string GetType();
};
#endif
