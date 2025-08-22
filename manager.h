#pragma once
#include "identity.h"
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "student.h"
#include "teacher.h"
#include "computerRoom.h"

class Manager:public Identity
{
public:
    Manager();

    Manager(string name, string pwd);

    //管理员菜单页面
    virtual void openMenu();

    //添加账号
    void addPerson();

    //查看账号
    void showPerson();

    //查看机房信息
    void showComputer();

    //清空预约记录
    void cleanFile();

    //设置管理员姓名
    virtual void SetName(string name);

    //读取管理员姓名
    virtual string GetName();

    //设置管理员密码
    virtual void SetPwd(string pwd); 

    //读取管理员密码
    virtual string GetPwd();

    //初始化容器
    void initVector();

    //检查是否有重复的学生学号或者教师编号
    bool checkRepeat(int id, int type);

    //初始化机房
    void initComputerRoom();

    //学生容器
    vector<Student> vStu;

    //老师容器
    vector<Teacher> vTea;

    //机房容器
    vector<ComputerRoom> vCom;
};