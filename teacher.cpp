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

//��ʦ�˵�ҳ��
void Teacher::openMenu()
{
    cout << "��ӭ" << this->m_Name << "��ʦ��" << endl;
    cout << "\t\t ������������������������������������������������������������������������\n";
    cout << "\t\t|                                    |\n";
    cout << "\t\t|           1����ʾ����ԤԼ          |\n";
    cout << "\t\t|                                    |\n";
    cout << "\t\t|           2�����ԤԼ              |\n";
    cout << "\t\t|                                    |\n";
    cout << "\t\t|           0��ע����¼              |\n";
    cout << "\t\t|                                    |\n";
    cout << "\t\t ������������������������������������������������������������������������\n";
    cout << "��ѡ�����Ĳ�����" ;
}

//��ʾ����ԤԼ
void Teacher::showAllOrder()
{
    OrderFile of;
    if (of.m_Size == 0)
    {
        cout << "��ԤԼ��¼" << endl;
        system("pause");
        system("cls");
        return;
    }
    for (int i = 0; i < of.m_Size; i++)
    {
        cout << i + 1 << "��";
        cout << "ѧ�ţ�" << of.m_orderData[i]["stuId"] << "  ";
        cout << "������" << of.m_orderData[i]["stuName"] << "  ";

        string date;
        int num;
        num = atoi(of.m_orderData[i]["date"].c_str());
        switch(num)
        {
            case 1:
                date = "һ";
                break;
            case 2:
                date = "��";
                break;
            case 3:
                date = "��";
                break;
            case 4:
                date = "��";
                break;
            case 5:
                date = "��";
                break;
        }

        cout << "ԤԼ���ڣ���" << date << "  ";
        cout << "ʱ�Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����") << "  ";
        cout << "�����ţ�" << of.m_orderData[i]["roomId"] << "  ";
        string status = "״̬��"; // 0 ȡ��ԤԼ   1 �����   2 ��ԤԼ  -1 ԤԼʧ��
        num = atoi(of.m_orderData[i]["status"].c_str());
        switch(num)
        {
            case 1:
                status += "�����";
                break;
            case 2:
                status += "ԤԼ�ɹ�";
                break;
            case 0:
                status += "ԤԼ��ȡ��";
                break;
            case -1:
                status += "���δͨ����ԤԼʧ��";
        }
        cout << status << endl;
    }

    system("pause");
    system("cls");
}

//���ԤԼ
void Teacher::validOrder()
{
    OrderFile of;
    if (of.m_Size == 0)
    {
        cout << "��ԤԼ��¼" << endl;
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
        cout << "û����Ҫ��˵Ļ���ԤԼ��" << endl;
        system("pause");
        system("cls");
        return; 
    }

    cout << "����˵�ԤԼ��¼���£�" << endl;

    vector<int> v;      // ���ڼ�¼ԤԼ��¼���ڵ�ʵ��λ�õ��±�
    int index = 1;      // �����û�ѡ����±�

    for (int i = 0; i < of.m_Size; i++)
    {
        if (of.m_orderData[i]["status"] == "1")
        {
            v.push_back(i);
            cout << index++ << "��";
            cout << "ѧ�ţ�" << of.m_orderData[i]["stuId"] << "  ";
            cout << "������" << of.m_orderData[i]["stuName"] << "  ";

            string date;
            int num;
            num = atoi(of.m_orderData[i]["date"].c_str());
            switch(num)
            {
                case 1:
                    date = "һ";
                    break;
                case 2:
                    date = "��";
                    break;
                case 3:
                    date = "��";
                    break;
                case 4:
                    date = "��";
                    break;
                case 5:
                    date = "��";
                    break;
            }

            cout << "ԤԼ���ڣ���" << date << "  ";
            cout << "ʱ�Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����") << "  ";
            cout << "�����ţ�" << of.m_orderData[i]["roomId"] << "  ";
            string status = "״̬�������";
            cout << status << endl;
        }
    }

    cout << "��ѡ��Ҫ��˵�ԤԼ�ļ�¼������0���ʾ����" << endl;
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
                cout << "��ѡ����˺�Ľ��" << endl;
                cout << "1��ͨ��  2����ͨ��" << endl;
                int choice2 = 0;

                while(true)
                {
                    cin >> choice2;

                    if (choice2 == 1)
                    {
                        of.m_orderData[v[choice1 - 1]]["status"] = "2";
                        of.updataOrder();
                        cout << "�����ϣ�" << endl;
                        break;
                    }
                    else if (choice2 == 2)
                    {
                        of.m_orderData[v[choice1 - 1]]["status"] = "-1";
                        of.updataOrder();
                        cout << "�����ϣ�" << endl;
                        break;
                    }
                    
                    cout << "����������������룡" << endl;
                }
                break;
            }
        }
        cout << "����������������룡" << endl;
    }

    system("pause");
    system("cls");
}

//������ʦ����
void Teacher::SetName(string name)
{
    this->m_Name = name;
}

//��ȡ��ʦ����
string Teacher::GetName()
{
    return this->m_Name;
}

//������ʦ����
void Teacher::SetPwd(string pwd)
{
    this->m_Pwd = pwd;
}

//��ȡ��ʦ����
string Teacher::GetPwd()
{
    return this->m_Pwd;
}

//����ְ���ŵĽӿ�
void Teacher::SetEmpId(int id)
{
    this->m_EmpId = id;
}

//��ȡְ���ŵĽӿ�
int Teacher::GetEmpId()
{
    return this->m_EmpId;
}