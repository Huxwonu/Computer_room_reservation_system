#pragma once
#include "identity.h"
#include <string>
#include <fstream>
#include <vector>
#include "computerRoom.h"
#include "orderFile.h"

class Student:public Identity
{
public:
    Student();

    Student(int id, string name, string pwd);

    //学生菜单页面
    virtual void openMenu();

    //申请预约
    void applyOrder();

    //查看自身预约
    void showMyOrder();

    //查看所有预约
    void showAllOrder();

    //取消预约
    void cancelOrder();

    //设置学生姓名
    virtual void SetName(string name);

    //读取学生姓名
    virtual string GetName();

    //设置学生密码
    virtual void SetPwd(string pwd); 

    //读取学生密码
    virtual string GetPwd();

    //设置学号的接口
    void SetId(int id);

    //读取学号的接口
    int GetId();

    //机房容器
    vector<ComputerRoom> vCom;

private:
    //学生学号
    int m_Id;
};