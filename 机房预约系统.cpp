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
            case 0:     //ע����¼
                delete man;
                cout << "ע���ɹ���" << endl;
                system("pause");
                system("cls");
                return;
            case 1:     //�鿴����ԤԼ
                man->showAllOrder();
                break;
            case 2:     //���ԤԼ
                man->validOrder();
                break;
            default:
                cout << "����������������룡" << endl;
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
            case 0:     //ע����¼
                delete man;
                cout << "ע���ɹ���" << endl;
                system("pause");
                system("cls");
                return;
            case 1:     //����ԤԼ
                man->applyOrder();
                break;
            case 2:     //�鿴�ҵ�ԤԼ
                man->showMyOrder();
                break;
            case 3:     //�鿴����ԤԼ
                man->showAllOrder();
                break;
            case 4:     //ȡ��ԤԼ
                man->cancelOrder();
                break;
            default:
                cout << "����������������룡" << endl;
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
            case 0:     //ע����¼
                delete man;
                cout << "ע���ɹ���" << endl;
                system("pause");
                system("cls");
                return;
            case 1:     //����˺�
                man->addPerson();
                break;
            case 2:     //�鿴�˺�
                man->showPerson();
                break;
            case 3:     //�鿴����
                man->showComputer();
                break;
            case 4:     //���ԤԼ
                man->cleanFile();
                break;
            default:
                cout << "����������������룡" << endl;
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
        cout << "�ļ�������" << endl;
        ifs.close();
        return;
    }

    int id = 0;
    string name;
    string pwd;

    if (type == 1)
    {
        cout << "���������ѧ�ţ�" << endl;
        cin >> id;
    }
    else if (type == 2)
    {
        cout << "���������ְ����ţ�" << endl;
        cin >> id;
    }

    cout << "�������û�����" << endl;
    cin >> name;

    cout << "���������룺" << endl;
    cin >> pwd;

    if (type == 1)
    {
        //ѧ����¼
        int fid;
        string fname;
        string fpwd;

        while (ifs >> fid && ifs >> fname && ifs >> fpwd)
        {
            if (id == fid && name == fname && pwd == fpwd)
            {
                cout << "��¼�ɹ�����ӭ" << name << "ͬѧ" << endl;
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
        //��ʦ��¼
        int fid;
        string fname;
        string fpwd;

        while (ifs >> fid && ifs >> fname && ifs >> fpwd)
        {
            if (id == fid && name == fname && pwd == fpwd)
            {
                cout << "��¼�ɹ�����ӭ" << name << "��ʦ" << endl;
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
        //����Ա��¼
        string fname;
        string fpwd;

        while (ifs >> fname && ifs >> fpwd)
        {
            if (name == fname && pwd == fpwd)
            {
                cout << "��¼�ɹ�����ӭ" << name << "����Ա" << endl;
                system("pause");
                system("cls");

                person = new Manager(name, pwd);

                managerMenu(person);

                return;
            }
        }

    }

    cout << "��֤��¼ʧ�ܣ�" << endl;

    system("pause");
    system("cls");
    return;
}


int main()
{
    int choice = 0;

    while(true)
    {
        cout << "=========================  ��ӭ��������ԤԼϵͳ  =========================" << endl;
        cout << endl << "��ѡ���������" << endl;
        cout << "\t\t ������������������������������������������������������������������������\n";
        cout << "\t\t|                                    |\n";
        cout << "\t\t|           1��ѧ������              |\n";
        cout << "\t\t|                                    |\n";
        cout << "\t\t|           2����    ʦ              |\n";
        cout << "\t\t|                                    |\n";
        cout << "\t\t|           3���� �� Ա              |\n";
        cout << "\t\t|                                    |\n";
        cout << "\t\t|           0����    ��              |\n";
        cout << "\t\t|                                    |\n";
        cout << "\t\t ������������������������������������������������������������������������\n";

        cout << "����������ѡ��";

        cin >> choice;

        switch(choice)
        {
            case 0:     //�˳�ϵͳ
                cout << "��ӭ�´�ʹ��^_^" << endl;
                system("pause");
                return 0;
                break;     // ����
            case 1:     //ѧ�����
                LoginIn(STUDENT_FILE, 1);
                break;
            case 2:     //��ʦ���
                LoginIn(TEACHER_FILE, 2);
                break;
            case 3:     //����Ա���
                LoginIn(ADMIN_FILE, 3);
                break;
            default:
                cout << "�������������ѡ��" << endl;
                system("pause");
                system("cls");
                break;
        }
    }

    system("pause");
    return 0;
}