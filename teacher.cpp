#include "teacher.h"

Teacher::Teacher()
{

}

Teacher::Teacher(int empId, string name, string pwd)
{
    this->m_EmpId = empId;
    this->m_Name = name;
    this->m_Pwd =pwd;
}

//老师菜单页面
void Teacher::openMenu()
{
    cout << "欢迎" << this->m_Name << "老师！" << endl;
    cout << "\t\t ————————————————————————————————————\n";
    cout << "\t\t|                                    |\n";
    cout << "\t\t|           1、显示所有预约          |\n";
    cout << "\t\t|                                    |\n";
    cout << "\t\t|           2、审核预约              |\n";
    cout << "\t\t|                                    |\n";
    cout << "\t\t|           0、注销登录              |\n";
    cout << "\t\t|                                    |\n";
    cout << "\t\t ————————————————————————————————————\n";
    cout << "请选择您的操作：" ;
}

//显示所有预约
void Teacher::showAllOrder()
{
    OrderFile of;
    if (of.m_Size == 0)
    {
        cout << "无预约记录" << endl;
        system("pause");
        system("cls");
        return;
    }
    for (int i = 0; i < of.m_Size; i++)
    {
        cout << i + 1 << "、";
        cout << "学号：" << of.m_orderData[i]["stuId"] << "  ";
        cout << "姓名：" << of.m_orderData[i]["stuName"] << "  ";

        string date;
        int num;
        num = atoi(of.m_orderData[i]["date"].c_str());
        switch(num)
        {
            case 1:
                date = "一";
                break;
            case 2:
                date = "二";
                break;
            case 3:
                date = "三";
                break;
            case 4:
                date = "四";
                break;
            case 5:
                date = "五";
                break;
        }

        cout << "预约日期：周" << date << "  ";
        cout << "时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午") << "  ";
        cout << "机房号：" << of.m_orderData[i]["roomId"] << "  ";
        string status = "状态："; // 0 取消预约   1 审核中   2 已预约  -1 预约失败
        num = atoi(of.m_orderData[i]["status"].c_str());
        switch(num)
        {
            case 1:
                status += "审核中";
                break;
            case 2:
                status += "预约成功";
                break;
            case 0:
                status += "预约已取消";
                break;
            case -1:
                status += "审核未通过，预约失败";
        }
        cout << status << endl;
    }

    system("pause");
    system("cls");
}

//审核预约
void Teacher::validOrder()
{
    OrderFile of;
    if (of.m_Size == 0)
    {
        cout << "无预约记录" << endl;
        system("pause");
        system("cls");
        return;
    }

    bool flag = false;
    for (int i = 0; i < of.m_Size; i++)
    {
        if (of.m_orderData[i]["status"] == "1")
        {
            flag = true;
            break;
        }
    }

    if (!flag)
    {
        cout << "没有需要审核的机房预约！" << endl;
        system("pause");
        system("cls");
        return; 
    }

    cout << "待审核的预约记录如下：" << endl;

    vector<int> v;      // 用于记录预约记录所在的实际位置的下标
    int index = 1;      // 用于用户选择的下标

    for (int i = 0; i < of.m_Size; i++)
    {
        if (of.m_orderData[i]["status"] == "1")
        {
            v.push_back(i);
            cout << index++ << "、";
            cout << "学号：" << of.m_orderData[i]["stuId"] << "  ";
            cout << "姓名：" << of.m_orderData[i]["stuName"] << "  ";

            string date;
            int num;
            num = atoi(of.m_orderData[i]["date"].c_str());
            switch(num)
            {
                case 1:
                    date = "一";
                    break;
                case 2:
                    date = "二";
                    break;
                case 3:
                    date = "三";
                    break;
                case 4:
                    date = "四";
                    break;
                case 5:
                    date = "五";
                    break;
            }

            cout << "预约日期：周" << date << "  ";
            cout << "时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午") << "  ";
            cout << "机房号：" << of.m_orderData[i]["roomId"] << "  ";
            string status = "状态：审核中";
            cout << status << endl;
        }
    }

    cout << "请选择要审核的预约的记录，输入0则表示返回" << endl;
    int choice1 = 0;

    while(true)
    {
        cin >> choice1;
        if (choice1 >= 0 && choice1 < index)
        {
            if (choice1 == 0)
            {
                break;
            }
            else
            {
                cout << "请选择审核后的结果" << endl;
                cout << "1、通过  2、不通过" << endl;
                int choice2 = 0;

                while(true)
                {
                    cin >> choice2;

                    if (choice2 == 1)
                    {
                        of.m_orderData[v[choice1 - 1]]["status"] = "2";
                        of.updataOrder();
                        cout << "审核完毕！" << endl;
                        break;
                    }
                    else if (choice2 == 2)
                    {
                        of.m_orderData[v[choice1 - 1]]["status"] = "-1";
                        of.updataOrder();
                        cout << "审核完毕！" << endl;
                        break;
                    }
                    
                    cout << "输入错误，请重新输入！" << endl;
                }
                break;
            }
        }
        cout << "输入错误，请重新输入！" << endl;
    }

    system("pause");
    system("cls");
}

//设置老师姓名
void Teacher::SetName(string name)
{
    this->m_Name = name;
}

//读取老师姓名
string Teacher::GetName()
{
    return this->m_Name;
}

//设置老师密码
void Teacher::SetPwd(string pwd)
{
    this->m_Pwd = pwd;
}

//读取老师密码
string Teacher::GetPwd()
{
    return this->m_Pwd;
}

//设置职工号的接口
void Teacher::SetEmpId(int id)
{
    this->m_EmpId = id;
}

//读取职工号的接口
int Teacher::GetEmpId()
{
    return this->m_EmpId;
}