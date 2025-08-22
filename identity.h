#pragma once
#include <iostream>
using namespace std;
#include "global_file.h"

class Identity
{
public:
    virtual void openMenu() = 0;

    virtual void SetName(string name) = 0;

    virtual string GetName() = 0;

    virtual void SetPwd(string pwd) = 0; 

    virtual string GetPwd() = 0;

protected:
    //用户名
    string m_Name;

    //密码
    string m_Pwd;
};