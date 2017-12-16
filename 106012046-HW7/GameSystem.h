#pragma once
#ifndef GAMESYS_H
#define GAMESYS_H
#include <vector>
using namespace std;
#include "Character.h"
#include "MeleeJob.h"
#include "RemoteJob.h"
#include "DefenseJob.h"
class GameSystem
{
public:
    GameSystem();
    void Start();
    int PrintMenu();
    bool Create();
    void Fight();
    void List();
    void DeleteCharacter();
    void NewJob();
    void DeleteJob();
    int ListJobs(int x);
    ~GameSystem();

private:
    vector<Character> _charactersList;
    vector<Character> _monsterList;
    vector<Job*> _jobList;
};

#endif

