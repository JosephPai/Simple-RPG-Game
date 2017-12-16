#pragma once
#ifndef REMOTE_H
#define REMOTE_H
using namespace std;
#include "Job.h"
class RemoteJob :
    public Job
{
public:
    RemoteJob(string name, int extraStr, int extraDex, int extraCon) :Job(name, extraStr, extraDex, extraCon) {}
    virtual int GetDamage(Character* cha);
    string GetType();
};
#endif

