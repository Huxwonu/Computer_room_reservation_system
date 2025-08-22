#include "manager.h"

Manager::Manager()
{

}

Manager::Manager(string name, string pwd)
{
    this->m_Name = name;
    this->m_Pwd = pwd;

    this->initVector();

    this->initComputerRoom();
}

//管理员菜单页面
void Manager::openMenu()
{
    cout << "欢迎" << this->m_Name << "管理员！" << endl;
    cout << "\t\t ————————————————————————————————————\n";
    cout << "\t\t|                                    |\n";
    cout << "\t\t|           1、添加账号              |\n";
    cout << "\t\t|                                    |\n";
    cout << "\t\t|           2、查看账号              |\n";
    cout << "\t\t|                                    |\n";
    cout << "\t\t|           3、查看机房              |\n";
    cout << "\t\t|                                    |\n";
    cout << "\t\t|           4、清空预约              |\n";
    cout << "\t\t|                                    |\n";
    cout << "\t\t|           0、注销登录              |\n";
    cout << "\t\t|                                    |\n";
    cout << "\t\t ————————————————————————————————————\n";
    cout << "请选择您的操作：" ;
}

//添加账号
void Manager::addPerson()
{
    string filename;
    string tip;
    ofstream ofs;

    int choice = 0;

    while(true)
    {
        cout << "请输入您要添加的类型" << endl;
        cout << "1、添加学生" << endl;
        cout << "2、添加老师" << endl;

        cin >> choice;

        if (choice == 1)
        {
            filename = STUDENT_FILE;
            tip = "学号";
            break;
        }
        else if (choice == 2)
        {
            filename = TEACHER_FILE;
            tip = "职工编号";
            break;
        }
        else
        {
            cout << "输入错误！" << endl;
            system("pause");
            system("cls");

            this->openMenu();
        }
    }

    int id;
    string name;
    string pwd;

    cout << "请输入" << tip << ':';
    cin >> id;

    while (true)
    {
        if (this->checkRepeat(id, choice))
        {
            cout << tip << id << "已存在！" << endl;
        }
        else
        {
            break; // 学号/编号不存在，跳出循环
        }

        cout << "请重新输入" << tip << ':';
        cin >> id;
    }

    cout << "请输入姓名：" ;
    cin >> name;

    cout << "请输入密码：";
    cin >> pwd;

    ofs.open(filename, ios::out | ios::app);

    ofs << id << " " << name << " " << pwd << " " << endl;
    cout << "添加成功！" << endl;

    system("pause");
    system("cls");

    ofs.close();

    //除了添加到文件，还要添加到对应的容器
    if (choice == 1)
    {
        Student s;
        s.SetId(id);
        s.SetName(name);
        s.SetPwd(pwd);
        this->vStu.push_back(s);
    }
    else
    {
        Teacher t;
        t.SetEmpId(id);
        t.SetName(name);
        t.SetPwd(pwd);
        this->vTea.push_back(t);
    }
}

void printStudent(Student & s)
{
    cout << "学号：" << s.GetId() << "\t姓名：" << s.GetName() << "\t密码：" << s.GetPwd() << endl;
}

void printTeacher(Teacher & t)
{
    cout << "职工编号：" << t.GetEmpId() << "\t姓名：" << t.GetName() << "\t密码：" << t.GetPwd() << endl;
}

//查看账号
void Manager::showPerson()
{
    cout << "请选择要查看的内容" << endl;
    cout << "1、查看所有学生" << endl;
    cout << "2、查看所有老师" << endl;

    int choice = 0;
    cin >> choice;

    while(true)
    {
        if (choice == 1)
        {
            cout << "所有学生信息如下：" << endl;
            for_each(this->vStu.begin(), this->vStu.end(), printStudent);
            break;
        }
        else if (choice == 2)
        {
            cout << "所有教师信息如下：" << endl;
            for_each(this->vTea.begin(), this->vTea.end(), printTeacher);
            break;
        }
        else
        {
            cout << "输入错误！请重新选择" << endl;
            cout << "1、查看所有学生" << endl;
            cout << "2、查看所有老师" << endl;
            cin >> choice;
        }
    }
    system("pause");
    system("cls");
}

//查看机房信息
void Manager::showComputer()
{
    cout << "机房信息如下：" << endl;
    for (vector<ComputerRoom>::iterator it = this->vCom.begin(); it != this->vCom.end(); it++)
    {
        cout << "机房编号：" <<  it->m_ComId << "\t机房最大容量：" << it->m_MaxNum << endl;
    }

    system("pause");
    system("cls");
}

//清空预约记录
void Manager::cleanFile()
{
    ofstream ofs(ORDER_FILE, ios::trunc);
    ofs.close();

    cout << "清空成功" << endl;
    system("pause");
    system("cls");
}

//设置管理员姓名
void Manager::SetName(string name)
{
    this->m_Name = name;
}

//读取管理员姓名
string Manager::GetName()
{
    return this->m_Name;
}

//设置管理员密码
void Manager::SetPwd(string pwd)
{
    this->m_Pwd = pwd;
}

//读取管理员密码
string Manager::GetPwd()
{
    return this->m_Pwd;
}

void Manager::initVector()
{
    int fid;
    string fname;
    string fpwd;
    ifstream ifs;

    this->vStu.clear();
    this->vTea.clear();

    ifs.open(STUDENT_FILE, ios::in);
    if (!ifs.is_open())
    {
        cout << STUDENT_FILE <<"文件读取失败" << endl;
        return;
    }

    Student s;
    while (ifs >> fid && ifs >> fname && ifs >> fpwd)
    {
        s.SetId(fid);
        s.SetName(fname);
        s.SetPwd(fpwd);

        this->vStu.push_back(s);
    }
    // cout << "当前学生数量为：" << vStu.size() << endl;
    ifs.close();

    ifs.open(TEACHER_FILE, ios::in);
    if (!ifs.is_open())
    {
        cout << TEACHER_FILE <<"文件读取失败" << endl;
        return;
    }

    Teacher t;
    while (ifs >> fid && ifs >> fname && ifs >> fpwd)
    {
        t.SetEmpId(fid);
        t.SetName(fname);
        t.SetPwd(fpwd);

        this->vTea.push_back(t);
    }
    // cout << "当前教师数量为：" << vTea.size() << endl;
    ifs.close();
}

bool Manager::checkRepeat(int id, int type)
{
    if (type == 1)
    {
        for (vector<Student>::iterator it = this->vStu.begin(); it != this->vStu.end(); it++)
        {
            if (id == it->GetId())
            {
                return true;
            }
        }
    }
    else
    {
        for (vector<Teacher>::iterator it = this->vTea.begin(); it != this->vTea.end(); it++)
        {
            if (id == it->GetEmpId())
            {
                return true;
            }
        }
    }

    return false;
}

void Manager::initComputerRoom()
{
    ifstream ifs;
    ifs.open(COMPUTER_FILE, ios::in);

    if (!ifs.is_open())
    {
        cout << COMPUTER_FILE << "不存在！" << endl;
    }
    else
    {
        ComputerRoom c;

        while (ifs >> c.m_ComId && ifs >> c.m_MaxNum)
        {
            this->vCom.push_back(c);
        }

        // cout << "当前机房的数量：" << this->vCom.size() << endl;
        
        ifs.close();
    }
    
}