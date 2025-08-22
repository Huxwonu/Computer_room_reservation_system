#include <iostream>
using namespace std;
#include <fstream>
#include "global_file.h"
#include "identity.h"
#include "student.h"
#include "teacher.h"
#include "manager.h"

void teacherMenu(Identity * &teacher)
{
    Teacher* man = (Teacher*)teacher;

    while (true)
    {
        man->openMenu();

        int choice = 0;

        cin >> choice;

        switch(choice)
        {
            case 0:     //注销登录
                delete man;
                cout << "注销成功！" << endl;
                system("pause");
                system("cls");
                return;
            case 1:     //查看所有预约
                man->showAllOrder();
                break;
            case 2:     //审核预约
                man->validOrder();
                break;
            default:
                cout << "输入错误，请重新输入！" << endl;
                system("pause");
                system("cls");
                break;
        }
    } 
}

void studentMenu(Identity * &student)
{
    Student* man = (Student*)student;

    while (true)
    {
        man->openMenu();

        int choice = 0;

        cin >> choice;

        switch(choice)
        {
            case 0:     //注销登录
                delete man;
                cout << "注销成功！" << endl;
                system("pause");
                system("cls");
                return;
            case 1:     //申请预约
                man->applyOrder();
                break;
            case 2:     //查看我的预约
                man->showMyOrder();
                break;
            case 3:     //查看所有预约
                man->showAllOrder();
                break;
            case 4:     //取消预约
                man->cancelOrder();
                break;
            default:
                cout << "输入错误，请重新输入！" << endl;
                system("pause");
                system("cls");
                break;
        }
    } 
}

void managerMenu(Identity * &manager)
{
    Manager* man = (Manager*)manager;

    while (true)
    {
        man->openMenu();

        int choice = 0;

        cin >> choice;

        switch(choice)
        {
            case 0:     //注销登录
                delete man;
                cout << "注销成功！" << endl;
                system("pause");
                system("cls");
                return;
            case 1:     //添加账号
                man->addPerson();
                break;
            case 2:     //查看账号
                man->showPerson();
                break;
            case 3:     //查看机房
                man->showComputer();
                break;
            case 4:     //清空预约
                man->cleanFile();
                break;
            default:
                cout << "输入错误，请重新输入！" << endl;
                system("pause");
                system("cls");
                break;
        }
    } 
}

void LoginIn(string filename, int type)
{
    Identity *person = nullptr;

    ifstream ifs;
    ifs.open(filename, ios::in);

    if (!ifs.is_open())
    {
        cout << "文件不存在" << endl;
        ifs.close();
        return;
    }

    int id = 0;
    string name;
    string pwd;

    if (type == 1)
    {
        cout << "请输入你的学号：" << endl;
        cin >> id;
    }
    else if (type == 2)
    {
        cout << "请输入你的职工编号：" << endl;
        cin >> id;
    }

    cout << "请输入用户名：" << endl;
    cin >> name;

    cout << "请输入密码：" << endl;
    cin >> pwd;

    if (type == 1)
    {
        //学生登录
        int fid;
        string fname;
        string fpwd;

        while (ifs >> fid && ifs >> fname && ifs >> fpwd)
        {
            if (id == fid && name == fname && pwd == fpwd)
            {
                cout << "登录成功，欢迎" << name << "同学" << endl;
                system("pause");
                system("cls");

                person = new Student(id, name, pwd);

                studentMenu(person);

                return;
            }
        }

    }
    else if (type == 2)
    {
        //老师登录
        int fid;
        string fname;
        string fpwd;

        while (ifs >> fid && ifs >> fname && ifs >> fpwd)
        {
            if (id == fid && name == fname && pwd == fpwd)
            {
                cout << "登录成功，欢迎" << name << "老师" << endl;
                system("pause");
                system("cls");

                person = new Teacher(id, name, pwd);

                teacherMenu(person);

                return;
            }
        }

    }
    else if (type == 3)
    {
        //管理员登录
        string fname;
        string fpwd;

        while (ifs >> fname && ifs >> fpwd)
        {
            if (name == fname && pwd == fpwd)
            {
                cout << "登录成功，欢迎" << name << "管理员" << endl;
                system("pause");
                system("cls");

                person = new Manager(name, pwd);

                managerMenu(person);

                return;
            }
        }

    }

    cout << "验证登录失败！" << endl;

    system("pause");
    system("cls");
    return;
}


int main()
{
    int choice = 0;

    while(true)
    {
        cout << "=========================  欢迎来到机房预约系统  =========================" << endl;
        cout << endl << "请选择您的身份" << endl;
        cout << "\t\t ————————————————————————————————————\n";
        cout << "\t\t|                                    |\n";
        cout << "\t\t|           1、学生代表              |\n";
        cout << "\t\t|                                    |\n";
        cout << "\t\t|           2、老    师              |\n";
        cout << "\t\t|                                    |\n";
        cout << "\t\t|           3、管 理 员              |\n";
        cout << "\t\t|                                    |\n";
        cout << "\t\t|           0、退    出              |\n";
        cout << "\t\t|                                    |\n";
        cout << "\t\t ————————————————————————————————————\n";

        cout << "请输入您的选择：";

        cin >> choice;

        switch(choice)
        {
            case 0:     //退出系统
                cout << "欢迎下次使用^_^" << endl;
                system("pause");
                return 0;
                break;     // 多余
            case 1:     //学生身份
                LoginIn(STUDENT_FILE, 1);
                break;
            case 2:     //老师身份
                LoginIn(TEACHER_FILE, 2);
                break;
            case 3:     //管理员身份
                LoginIn(ADMIN_FILE, 3);
                break;
            default:
                cout << "输入错误，请重新选择！" << endl;
                system("pause");
                system("cls");
                break;
        }
    }

    system("pause");
    return 0;
}