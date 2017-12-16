#include "GameSystem.h"
#include <iostream>
#include <string>
#include <regex>
#include <random>
#include <time.h>

GameSystem::GameSystem()
{
    _charactersList.reserve(5);
    _monsterList.push_back(Character("哥布林(Goblin)", 1, 6, 1));
    _monsterList.push_back(Character("史莱姆(Slime)", 1, 1, 6));
    _monsterList.push_back(Character("兽人(Orc)", 6, 1, 1));
    _monsterList.push_back(Character("大青蛙(Frog)", 3, 2, 3));			// init the enemy
    _jobList.reserve(12);
    _jobList.push_back(new MeleeJob("盗贼(Thief)", 2, 0, 0));
    _jobList.push_back(new MeleeJob("刺客(Assassinator)", 3, 0, 0));
    _jobList.push_back(new RemoteJob ("猎人(Hunter)", 0, 2, 0));
    _jobList.push_back(new RemoteJob("神射手(Marksman)", 0, 3, 0));
    _jobList.push_back(new DefenseJob("战士(Warrior)", 0, 0, 2));
    _jobList.push_back(new DefenseJob("狂战士(Berserker Warrior)", 0, 0, 3));		// init the job
}

void GameSystem::Start()
{
    const int MAIN_ERROR = -1, MAIN_MENU_CREAT = 1, MAIN_MENU_FIGHT = 2, MAIN_MENU_LIST = 3, MINA_MENU_DELELTE = 4,
              MAIN_MENU_NEWJOB = 5, MAIN_MENU_DELJOB = 6, MAIN_MENU_EXIT = 7;	// different states of game
    int mainMenuState;
    bool init;
    init = true;

    while (init)
    {
        mainMenuState = PrintMenu();

        if (mainMenuState == MAIN_ERROR)
        {
            continue;
        }

        if (mainMenuState == MAIN_MENU_CREAT)		// creating character branch
        {
            Create();
        }

        if (mainMenuState == MAIN_MENU_FIGHT)		// fight branch
        {
            Fight();
        }

        if (mainMenuState == MAIN_MENU_LIST)		// list branch
        {
            List();
        }

        if (mainMenuState == MINA_MENU_DELELTE)		// delete character branch
        {
            DeleteCharacter();
        }

        if (mainMenuState == MAIN_MENU_NEWJOB)		// new job branch
        {
            NewJob();
        }

        if (mainMenuState == MAIN_MENU_DELJOB)
        {
            DeleteJob();
        }

        if (mainMenuState == MAIN_MENU_EXIT)		// Exit branch
        {
            exit(0);
        }
    }
}

int GameSystem::PrintMenu()		// print the main game menu
{
    int mainMenuState;
    string mainMenuSel;
    cout << "1.创建角色(Creating Character) \n2.角色作战(Fight)\n3.列出所有角色(List all characters)" << endl;
    cout << "4.删除角色(Delete Character)\n5.新增职业(New Job)\n6.删除职业(Delete Job)\n7.离开(Exit)" << endl;
    getline(cin, mainMenuSel);

    if (mainMenuSel.compare("1") == 0 || mainMenuSel.compare("2") == 0 ||
            mainMenuSel.compare("3") == 0 || mainMenuSel.compare("4") == 0 ||
            mainMenuSel.compare("5") == 0 || mainMenuSel.compare("6") == 0 || mainMenuSel.compare("7") == 0)
    {
        if (mainMenuSel.find(" ") == 0 || mainMenuSel.empty())
        {
            cout << "指令错误，请重新输入。(Invalid input, please input again.)\n" << endl;
            return -1;
        }
        else
        {
            mainMenuState = atoi(mainMenuSel.c_str());
            return mainMenuState;
        }
    }
    else
    {
        cout << "指令错误，请重新输入。(Invalid input, please input again.)\n" << endl;
        return -1;
    }
}

bool GameSystem::Create()
{
    const std::regex NAME_PATTERN("[\\\\/:*?\"<>|]");		// regular expression for name
    const std::regex NUM_PATTERN("^[1-9]\\d*$");
    int strTemp, dexTemp, conTemp, pointTemp;
    int jobCount;
    int creatState;
    const int CREAT_NAME = 0, CREAT_POINT = 1, CREAT_JOB = 2, CREAT_INFO = 3;
    string name, pointSel, jobSel;

    if (_charactersList.size() >= 5)
    {
        cout << "角色数量已达上限！(The number of characters has reached the limit!)\n" << endl;
        return false;
    }

    strTemp = dexTemp = conTemp = 1;
    creatState = CREAT_NAME;				// switch game state

    while (creatState == CREAT_NAME)
    {
        cout << "请输入角色名称：(Please input the name of the character:)";

        while (true)
        {
            getline(cin, name);

            if (std::regex_search(name, NAME_PATTERN) || name.find(" ") == 0 || name.empty())		// Check for illegal symbols
            {
                cout << "名称不合规定，请重新输入：(Name is not acceptable format, please input again.";
                continue;
            }
            else
            {
                creatState = CREAT_POINT;
                pointTemp = 5;				// Temporary variable for points
                break;
            }
        }
    }

    while (creatState == CREAT_POINT)		// distribute the points
    {
        cout << "\n1.目前STR :(Current STR) " << strTemp << endl;
        cout << "2.目前DEX : (Current DEX)" << dexTemp << endl;
        cout << "3.目前CON : (Current CON)" << conTemp << endl;
        cout << "目前剩余点数 : (Current remaining points)" << pointTemp << endl;
        cout << "请选择欲增加之属性 : (Please choose to increase the attributes)";
        getline(cin, pointSel);
        pointTemp--;

        if (pointSel.compare("1") == 0)
        {
            strTemp++;
        }
        else if (pointSel.compare("2") == 0)
        {
            dexTemp++;
        }
        else if (pointSel.compare("3") == 0)
        {
            conTemp++;
        }
        else
        {
            cout << "指令错误，请重新输入。(Invalid input, please input again.)" << endl;
            pointTemp++;
            continue;
        }

        if (pointTemp == 0)
        {
            _charactersList.push_back(Character(name, strTemp, dexTemp, conTemp));		// construct instance
            creatState = CREAT_JOB;					// switch game state
        }
    }

    while (creatState == CREAT_JOB)
    {
        string secondSel;
        cout << "\n请选择职业种类：(Please choose the job type:" << endl;
        cout << "1.近距离攻击型(MeleeJob)\n2.远距离攻击型(RemoteJob)\n3.防御系(DefenseJob)" << endl;
        getline(cin, jobSel);

        if (jobSel=="1")
        {
            cout << "请选择职业：" << endl;
            jobCount = ListJobs(1);

            while (true)
            {
                getline(cin, secondSel);

                if (std::regex_match(secondSel,NUM_PATTERN) && atoi(secondSel.c_str())<=jobCount)
                {
                    for (size_t i = 0, j = 0; i < _jobList.size(); i++)
                    {
                        if (_jobList.at(i)->GetType() == "近距离攻击型(MeleeJob)")
                        {
                            j++;
                        }

                        if (j == atoi(secondSel.c_str()))
                        {
                            _charactersList.back().SetJob(_jobList.at(i));		// add to the vector
                            break;
                        }
                    }

                    cout << "创建成功！(Created successfully)\n" << endl;
                    creatState = CREAT_INFO;		// switch game state
                    break;
                }
                else
                {
                    cout << "指令错误，请重新输入。(Invalid input, please input again.)" << endl;
                    continue;
                }
            }
        }
        else if (jobSel=="2")
        {
            cout << "请选择职业：" << endl;
            jobCount = ListJobs(2);

            while (true)
            {
                getline(cin, secondSel);

                if (std::regex_match(secondSel, NUM_PATTERN) && atoi(secondSel.c_str()) <= jobCount)
                {
                    for (size_t i = 0, j = 0; i < _jobList.size(); i++)
                    {
                        if (_jobList.at(i)->GetType() == "远距离攻击型(RemoteJob)")
                        {
                            j++;
                        }

                        if (j == atoi(secondSel.c_str()))
                        {
                            _charactersList.back().SetJob(_jobList.at(i));		// add to the vector
                            break;
                        }
                    }

                    cout << "创建成功！(Created successfully)\n" << endl;
                    creatState = CREAT_INFO;		// switch game state
                    break;
                }
                else
                {
                    cout << "指令错误，请重新输入。(Invalid input, please input again.)" << endl;
                    continue;
                }
            }
        }
        else if (jobSel == "3")
        {
            cout << "请选择职业：" << endl;
            jobCount = ListJobs(3);

            while (true)
            {
                getline(cin, secondSel);

                if (std::regex_match(secondSel, NUM_PATTERN) && atoi(secondSel.c_str()) <= jobCount)
                {
                    for (size_t i = 0, j = 0; i < _jobList.size(); i++)
                    {
                        if (_jobList.at(i)->GetType() == "防御系(DefenseJob)")
                        {
                            j++;
                        }

                        if (j == atoi(secondSel.c_str()))
                        {
                            _charactersList.back().SetJob(_jobList.at(i));		// add to the vector
                            break;
                        }
                    }

                    cout << "创建成功！(Created successfully)\n" << endl;
                    creatState = CREAT_INFO;		// switch game state
                    break;
                }
                else
                {
                    cout << "指令错误，请重新输入。(Invalid input, please input again.)" << endl;
                    continue;
                }
            }
        }
        else
        {
            cout << "指令错误，请重新输入。(Invalid input, please input again.)" << endl;
            continue;
        }
    }

    if (creatState == CREAT_INFO)
    {
        _charactersList.back().GetInformation();		// output the information of the character
    }

    return true;
}

void GameSystem::Fight()
{
    srand((unsigned)time(NULL));							// random seed
    string fightSel;
    int fightPointer1, fightPointer2, randomJobPointer;

    if (_charactersList.empty())
    {
        cout << "没有角色可供选择！(No character to choose from)\n" << endl;
        //continue;
        return;
    }

    int i;

    for (i = 0; i < _charactersList.size(); i++)
        cout << i + 1 << ". " << _charactersList[i].GetName() << endl;

    while (true)
    {
        cout << "请选择角色进行作战：(Please choose a character to fight)";
        getline(cin, fightSel);

        if (fightSel == "0")
        {
            cout << "\n不进行战斗，跳回菜单。(Not fight, jump back to the menu)\n" << endl;
            break;
        }

        if (fightSel.compare("1") == 0 || fightSel.compare("2") == 0 || fightSel.compare("3") == 0
                || fightSel.compare("4") == 0 || fightSel.compare("5") == 0)
        {
            if (fightSel.find(" ") == 0 || fightSel.empty())
            {
                cout << "指令错误，请重新输入。(Invalid input, please input again.)" << endl;
                continue;
            }

            fightPointer1 = atoi(fightSel.c_str()) - 1;

            if (fightPointer1 >= _charactersList.size())		// Determine whether the character exists
            {
                cout << "不存在该角色，请重新选择。(This character does not exist, please select again.)\n" << endl;
                continue;
            }
            else
            {
                fightPointer2 = (rand() % 4);				// Choose enemies randomly
                randomJobPointer = (rand() % _jobList.size());			// the monster have the probility to have the new job
                _monsterList[fightPointer2].SetJob(_jobList[randomJobPointer]);
                _charactersList[fightPointer1].Fight(_monsterList[fightPointer2]);
                break;
            }
        }
        else
        {
            cout << "指令错误，请重新输入。(Invalid input, please input again.)" << endl;
        }
    }
}

void GameSystem::List()
{
    if (_charactersList.empty())
    {
        cout << "没有角色可供选择！(No character to choose from)\n" << endl;
        //continue;
        return;
    }

    int i;

    for (i = 0; i < _charactersList.size(); i++)
        _charactersList[i].GetInformation();		// output the information for each character one by one
}

void GameSystem::DeleteCharacter()
{
    string deleteSel;
    int deletePointer;

    if (_charactersList.empty())
    {
        cout << "没有角色可供选择！(No character to choose from)\n" << endl;
        //continue;
        return;
    }

    int i;

    for (i = 0; i < _charactersList.size(); i++)
        cout << i + 1 << ". " << _charactersList[i].GetName() << endl;

    while (true)
    {
        cout << "请输入欲删除的角色：(Please enter the character you want to delete)\n";
        getline(cin, deleteSel);

        if (deleteSel == "0")
        {
            cout << "\n不删除角色，跳回菜单。(Not delete the character, jump back to the menu)\n" << endl;
            break;
        }

        if (deleteSel.compare("1") == 0 || deleteSel.compare("2") == 0 || deleteSel.compare("3") == 0
                || deleteSel.compare("4") == 0 || deleteSel.compare("5") == 0)
        {
            if (deleteSel.find(" ") == 0 || deleteSel.empty())
            {
                cout << "指令错误，请重新输入。(Invalid input, please input again.)" << endl;
                continue;
            }

            deletePointer = atoi(deleteSel.c_str())-1;

            if (deletePointer >= _charactersList.size())		// Determine whether the character exists
            {
                cout << "不存在该角色，请重新选择。(This character does not exist, please select again.)\n" << endl;
                continue;
            }
            else
            {
                cout << "已删除角色：(Character deleted:)" << _charactersList[deletePointer].GetName() << "。\n" << endl;
                _charactersList.erase(_charactersList.begin() + deletePointer);
                break;
            }
        }
        else
        {
            cout << "指令错误，请重新输入。(Invalid input, please input again.)" << endl;
        }
    }
}

void GameSystem::NewJob()
{
    const std::regex NAME_PATTERN("[\\\\/:*?\"<>|]");		// regular expression for name
    const std::regex NUM_PATTERN("^[0-3]$");
    string strTemp, dexTemp, conTemp;
    int creatState;
    const int CREAT_NAME = 0, CREAT_POINT = 1, CREATE_TYPE = 2;
    string typeSel,jobName;
    bool repeatFlag=false;						// flag var for repeat name
    creatState = CREATE_TYPE;				// switch game state

    if (_jobList.size() == 12)
    {
        cout << "职业数量上限为12（The maximum number of jobs is 12\n" << endl;
        return;
    }

    while (creatState == CREATE_TYPE)
    {
        cout << "请选择职业种类：(Please choose the job type:" << endl;
        cout << "\n1.近距离攻击型(MeleeJob)\n2.远距离攻击型(RemoteJob)\n3.防御系(DefenseJob)" << endl;
        getline(cin, typeSel);

        if (typeSel=="1" || typeSel=="2" || typeSel=="3")
        {
            creatState = CREAT_NAME;
            break;
        }
        else
        {
            cout << "指令错误，请重新输入。(Invalid input, please input again.)" << endl;
        }
    }

    while (creatState == CREAT_NAME)
    {
        cout << "请输入职业名称，不接受空格：(Please input the name of the job，containing space is not accepted:)";

        while (true)
        {
            getline(cin, jobName);

            if (std::regex_search(jobName, NAME_PATTERN) || jobName.find(" ") == 0 || jobName.empty() || jobName.find(' ')!=string::npos  )		// Check for illegal symbols
            {
                cout << "名称不合规定，请重新输入：(Name is not acceptable format, please input again.";
                continue;
            }
            else
            {
                repeatFlag = false;

                for (size_t i = 0; i < _jobList.size(); i++)
                {
                    if (_jobList.at(i)->GetName() == jobName)
                    {
                        repeatFlag = true;						// check wheather the job already exists
                        break;
                    }
                }

                if (repeatFlag)
                {
                    cout << "名称重复，请重新输入(Job name already exists, please input again: ";
                }
                else
                {
                    creatState = CREAT_POINT;
                    cout << "\n";
                    break;
                }
            }
        }
    }

    while (creatState == CREAT_POINT)
    {
        cout << "请设定STR额外加成(Please set STR extra：";

        while (true)
        {
            getline(cin, strTemp);

            if (!std::regex_match(strTemp, NUM_PATTERN))
            {
                cout << "指令错误，请重新输入(Invalid input, please input again:";
                continue;
            }

            break;
        }

        cout <<"请设定DEX额外加成(Please set DEX extra：";

        while (true)
        {
            getline(cin, dexTemp);

            if (!std::regex_match(dexTemp, NUM_PATTERN))
            {
                cout << "指令错误，请重新输入(Invalid input, please input again:";
                continue;
            }

            break;
        }

        cout << "请设定CON额外加成(Please set CON extra：";

        while (true)
        {
            getline(cin, conTemp);

            if (!std::regex_match(conTemp, NUM_PATTERN))
            {
                cout << "指令错误，请重新输入(Invalid input, please input again:";
                continue;
            }

            break;
        }

        if ( (atoi(strTemp.c_str()) + atoi(dexTemp.c_str()) + atoi(conTemp.c_str())) > 3 )
        {
            cout << "\n额外加成数值总和超过3，请重新输入。(The sum of extra bonus values exceeds 3, please input again\n" << endl;
            continue;
        }
        else
        {
            if (typeSel=="1")
            {
                _jobList.push_back(new MeleeJob(jobName, atoi(strTemp.c_str()), atoi(dexTemp.c_str()), atoi(conTemp.c_str())));
            }
            else if (typeSel=="2")
            {
                _jobList.push_back(new RemoteJob(jobName, atoi(strTemp.c_str()), atoi(dexTemp.c_str()), atoi(conTemp.c_str())));
            }
            else
            {
                _jobList.push_back(new DefenseJob(jobName, atoi(strTemp.c_str()), atoi(dexTemp.c_str()), atoi(conTemp.c_str())));
            }

            cout << "\n";
            return;
        }
    }
}

void GameSystem::DeleteJob()
{
    const std::regex NUM_PATTERN("^[1-9]\\d*|0$");
    string delSel;
    ListJobs(0);
    cout << "请输入欲删除的职业(Please input the job you want to delete:" << endl;

    while (true)
    {
        getline(cin, delSel);

        if (_jobList.size() == 1)
        {
            cout << "无法再删除职业！(Can not delete a job anymore)\n" << endl;		// check the number of jobs
            return;
        }

        if (std::regex_match(delSel, NUM_PATTERN))
        {
            if (delSel == "0")
            {
                cout << "\n不删除职业，跳回菜单。(Not delete the job, jump back to the menu)\n" << endl;
                return;
            }

            if (atoi(delSel.c_str()) > _jobList.size())						// invalid input
            {
                cout << "指令错误，请重新输入。(Invalid input, please input again.)" << endl;
                continue;
            }
            else
            {
                int delIndex = atoi(delSel.c_str()) - 1;
                bool repeatFlag = false;

                for (size_t i = 0; i < _charactersList.size(); i++)
                {
                    if (_charactersList.at(i).GetJob()->GetName() == _jobList.at(delIndex)->GetName() )
                    {
                        repeatFlag = true;								// check weather the jobs still have characters
                        break;
                    }
                }

                if (repeatFlag)
                {
                    cout << "\n这个职业尚有角色，无法删除。请重新输入(This job has a character, can not be deleted. Please input again：";
                    continue;
                }
                else
                {
                    cout << "已删除职业(This job is being deleted：" << _jobList.at(delIndex)->GetName() << "。\n";
                    _jobList.erase(_jobList.begin() + delIndex);
                    return;
                }
            }
        }
        else
        {
            cout << "指令错误，请重新输入。(Invalid input, please input again.)" << endl;
            continue;
        }
    }
}

int GameSystem::ListJobs(int x)
{
    int j = 0, i;

    if (x==0)
    {
        for (i = 0; i < _jobList.size(); i++)
        {
            cout << i + 1 << "." << _jobList.at(i)->GetName() << endl;
        }
    }
    else if (x==1)
    {
        for (i = 0,j=1; i < _jobList.size(); i++)
        {
            if (_jobList.at(i)->GetType()=="近距离攻击型(MeleeJob)")
            {
                cout << j << "." << _jobList.at(i)->GetName() << endl;
                j++;
            }
        }
    }
    else if (x == 2)
    {
        for (i = 0, j = 1; i < _jobList.size(); i++)
        {
            if (_jobList.at(i)->GetType() == "远距离攻击型(RemoteJob)")
            {
                cout << j << "." << _jobList.at(i)->GetName() << endl;
                j++;
            }
        }
    }
    else if (x == 3)
    {
        for (i = 0, j = 1; i < _jobList.size(); i++)
        {
            if (_jobList.at(i)->GetType() == "防御系(DefenseJob)")
            {
                cout << j << "." << _jobList.at(i)->GetName() << endl;
                j++;
            }
        }
    }

    return j - 1;
}

GameSystem::~GameSystem()
{
    _charactersList.clear();
    _monsterList.clear();
    _jobList.clear();
    vector <Character>().swap(_charactersList);		// clear the vector
    vector <Character>().swap(_monsterList);
    vector <Job*>().swap(_jobList);
}