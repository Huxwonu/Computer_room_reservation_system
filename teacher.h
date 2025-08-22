#pragma once
#include "identity.h"
#include <string>
#include <vector>
#include "orderFile.h"

class Teacher:public Identity
{
public:
    Teacher();

    Teacher(int empId, string name, string pwd);

    //老师菜单页面
    virtual void openMenu();

    //显示所有预约
    void showAllOrder();

    //审核预约
    void validOrder();

    //设置老师姓名
    virtual void SetName(string name);

    //读取老师姓名
    virtual string GetName();

    //设置老师密码
    virtual void SetPwd(string pwd); 

    //读取老师密码
    virtual string GetPwd();

    //设置职工号的接口
    void SetEmpId(int id);

    //读取职工号的接口
    int GetEmpId();

private:
    //老师职工号
    int m_EmpId;
};