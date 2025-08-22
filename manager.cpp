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

//����Ա�˵�ҳ��
void Manager::openMenu()
{
    cout << "��ӭ" << this->m_Name << "����Ա��" << endl;
    cout << "\t\t ������������������������������������������������������������������������\n";
    cout << "\t\t|                                    |\n";
    cout << "\t\t|           1������˺�              |\n";
    cout << "\t\t|                                    |\n";
    cout << "\t\t|           2���鿴�˺�              |\n";
    cout << "\t\t|                                    |\n";
    cout << "\t\t|           3���鿴����              |\n";
    cout << "\t\t|                                    |\n";
    cout << "\t\t|           4�����ԤԼ              |\n";
    cout << "\t\t|                                    |\n";
    cout << "\t\t|           0��ע����¼              |\n";
    cout << "\t\t|                                    |\n";
    cout << "\t\t ������������������������������������������������������������������������\n";
    cout << "��ѡ�����Ĳ�����" ;
}

//����˺�
void Manager::addPerson()
{
    string filename;
    string tip;
    ofstream ofs;

    int choice = 0;

    while(true)
    {
        cout << "��������Ҫ��ӵ�����" << endl;
        cout << "1�����ѧ��" << endl;
        cout << "2�������ʦ" << endl;

        cin >> choice;

        if (choice == 1)
        {
            filename = STUDENT_FILE;
            tip = "ѧ��";
            break;
        }
        else if (choice == 2)
        {
            filename = TEACHER_FILE;
            tip = "ְ�����";
            break;
        }
        else
        {
            cout << "�������" << endl;
            system("pause");
            system("cls");

            this->openMenu();
        }
    }

    int id;
    string name;
    string pwd;

    cout << "������" << tip << ':';
    cin >> id;

    while (true)
    {
        if (this->checkRepeat(id, choice))
        {
            cout << tip << id << "�Ѵ��ڣ�" << endl;
        }
        else
        {
            break; // ѧ��/��Ų����ڣ�����ѭ��
        }

        cout << "����������" << tip << ':';
        cin >> id;
    }

    cout << "������������" ;
    cin >> name;

    cout << "���������룺";
    cin >> pwd;

    ofs.open(filename, ios::out | ios::app);

    ofs << id << " " << name << " " << pwd << " " << endl;
    cout << "��ӳɹ���" << endl;

    system("pause");
    system("cls");

    ofs.close();

    //������ӵ��ļ�����Ҫ��ӵ���Ӧ������
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
    cout << "ѧ�ţ�" << s.GetId() << "\t������" << s.GetName() << "\t���룺" << s.GetPwd() << endl;
}

void printTeacher(Teacher & t)
{
    cout << "ְ����ţ�" << t.GetEmpId() << "\t������" << t.GetName() << "\t���룺" << t.GetPwd() << endl;
}

//�鿴�˺�
void Manager::showPerson()
{
    cout << "��ѡ��Ҫ�鿴������" << endl;
    cout << "1���鿴����ѧ��" << endl;
    cout << "2���鿴������ʦ" << endl;

    int choice = 0;
    cin >> choice;

    while(true)
    {
        if (choice == 1)
        {
            cout << "����ѧ����Ϣ���£�" << endl;
            for_each(this->vStu.begin(), this->vStu.end(), printStudent);
            break;
        }
        else if (choice == 2)
        {
            cout << "���н�ʦ��Ϣ���£�" << endl;
            for_each(this->vTea.begin(), this->vTea.end(), printTeacher);
            break;
        }
        else
        {
            cout << "�������������ѡ��" << endl;
            cout << "1���鿴����ѧ��" << endl;
            cout << "2���鿴������ʦ" << endl;
            cin >> choice;
        }
    }
    system("pause");
    system("cls");
}

//�鿴������Ϣ
void Manager::showComputer()
{
    cout << "������Ϣ���£�" << endl;
    for (vector<ComputerRoom>::iterator it = this->vCom.begin(); it != this->vCom.end(); it++)
    {
        cout << "������ţ�" <<  it->m_ComId << "\t�������������" << it->m_MaxNum << endl;
    }

    system("pause");
    system("cls");
}

//���ԤԼ��¼
void Manager::cleanFile()
{
    ofstream ofs(ORDER_FILE, ios::trunc);
    ofs.close();

    cout << "��ճɹ�" << endl;
    system("pause");
    system("cls");
}

//���ù���Ա����
void Manager::SetName(string name)
{
    this->m_Name = name;
}

//��ȡ����Ա����
string Manager::GetName()
{
    return this->m_Name;
}

//���ù���Ա����
void Manager::SetPwd(string pwd)
{
    this->m_Pwd = pwd;
}

//��ȡ����Ա����
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
        cout << STUDENT_FILE <<"�ļ���ȡʧ��" << endl;
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
    // cout << "��ǰѧ������Ϊ��" << vStu.size() << endl;
    ifs.close();

    ifs.open(TEACHER_FILE, ios::in);
    if (!ifs.is_open())
    {
        cout << TEACHER_FILE <<"�ļ���ȡʧ��" << endl;
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
    // cout << "��ǰ��ʦ����Ϊ��" << vTea.size() << endl;
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
        cout << COMPUTER_FILE << "�����ڣ�" << endl;
    }
    else
    {
        ComputerRoom c;

        while (ifs >> c.m_ComId && ifs >> c.m_MaxNum)
        {
            this->vCom.push_back(c);
        }

        // cout << "��ǰ������������" << this->vCom.size() << endl;
        
        ifs.close();
    }
    
}