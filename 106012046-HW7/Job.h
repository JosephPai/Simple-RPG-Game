#pragma once
#ifndef JOB_H
#define JOB_H
#include <string>
using namespace std;
#include "Character.h"

class Character;	//前置声明，解决头文件.h重复包含问题

class Job
{
public:
    Job(string name, int extraStr, int extraDex, int extraCon);
    string GetName();
    int GetExtraStr();
    int GetExtraDex();
    int GetExtraCon();
    virtual int GetDamage(Character* cha);
    virtual ~Job()=default;
    virtual string GetType();
private:
    string _name;
    int _extraStr;
    int _extraDex;
    int _extraCon;
};
#endif

