#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>
#include <string>
using namespace std;
#include "Job.h"

class Job;	//前置声明，解决头文件.h重复包含问题

class Character
{
public:
    Character();
    ~Character();
    Character(string name, int str, int dex, int con);
    Character(string name, int str, int dex, int con, Job* job);
    string GetName();
    void GetName(string name);
    int GetLevel();
    void SetLevel(int levle);
    int GetStr();
    void SetStr(int str);
    int GetDex();
    void SetDex(int dex);
    int GetCon();
    void SetCon(int con);
    int GetExp();
    void SetExp(int exp);
    int GetTotalFightTimes();
    void SetTotalFightTimes(int times);
    int GetFailFightTimes();
    void SetFailFightTimes(int time);
    bool Fight(Character &monster);
    void GetInformation();
    void LevelUp(int lv);
    void SetJob(Job* job);
    Job* GetJob();
private:
    string _name;
    int _level;
    int _str;
    int _dex;
    int _con;
    int _exp;
    int _totalFightTimes;
    int _failFighttTimes;
    Job* _job;
};
#endif
