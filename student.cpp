#include "student.h"

Student::Student()
{

}

Student::Student(int id, string name, string pwd)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_Pwd = pwd;

    ifstream ifs;
    ifs.open(COMPUTER_FILE, ios::in);

    if(!ifs.is_open())
    {
        cout << COMPUTER_FILE << "�����ڣ�" << endl;
    }
    else
    {
        ComputerRoom c;

        while (ifs >> c.m_ComId && ifs >> c.m_MaxNum)
        {
            vCom.push_back(c);
        }

        ifs.close();
    }
    
}

//ѧ���˵�ҳ��
void Student::openMenu()
{
    cout << "��ӭ" << this->m_Name << "ͬѧ��" << endl;
    cout << "\t\t ������������������������������������������������������������������������\n";
    cout << "\t\t|                                    |\n";
    cout << "\t\t|           1������ԤԼ              |\n";
    cout << "\t\t|                                    |\n";
    cout << "\t\t|           2���鿴�ҵ�ԤԼ          |\n";
    cout << "\t\t|                                    |\n";
    cout << "\t\t|           3���鿴����ԤԼ          |\n";
    cout << "\t\t|                                    |\n";
    cout << "\t\t|           4��ȡ��ԤԼ              |\n";
    cout << "\t\t|                                    |\n";
    cout << "\t\t|           0��ע����¼              |\n";
    cout << "\t\t|                                    |\n";
    cout << "\t\t ������������������������������������������������������������������������\n";
    cout << "��ѡ�����Ĳ�����" ;
}

//����ԤԼ
void Student::applyOrder()
{
    OrderFile of;

    cout << "��������ʱ��Ϊ��һ������" << endl;
    cout << "1����һ";
    cout << "  2���ܶ�";
    cout << "  3������";
    cout << "  4������";
    cout << "  5������" << endl;
    cout << "��ѡ������ԤԼ��ʱ�䣺" << endl;
    int date = 0;   // ѡ�������
    int interval = 0;   // ѡ���ʱ��Σ���������磩
    int room = 0;   // ѡ��Ļ���

    while (true)
    {
        cin >> date;

        if (date >= 1 && date <= 5)
        {
            break;
        }
        cout << "����������������룡" << endl;
    }

    cout << "��ѡ������ԤԼ��ʱ��Σ�" << endl;
    cout << "1������";
    cout << "  2������" << endl;

    while (true)
    {
        cin >> interval;

        if (interval >= 1 && interval <= 2)
        {
            break;
        }
        cout << "����������������룡" << endl;
    }

    cout << "��ѡ�������" << endl;
    for (vector<ComputerRoom>::iterator it = this->vCom.begin(); it != this->vCom.end(); it++)
    {
        cout << it->m_ComId << "�Ż���������" << it->m_MaxNum << "    ";
    }
    cout << endl;

    while (true)
    {
        cin >> room;

        if (room >= 1 && room <= 3)
        {
            break;
        }
        cout << "����������������룡" << endl;
    }

    for (int i = 0; i < of.m_Size; i++)
    {
        if (date == atoi(of.m_orderData[i]["date"].c_str()) && interval == atoi(of.m_orderData[i]["interval"].c_str()) && room == atoi(of.m_orderData[i]["roomId"].c_str()))
        {
            string status = of.m_orderData[i]["status"];
            if (status == "1")
            {
                cout << "ԤԼʧ�ܣ�����ѡ���ʱ��λ�����������У�" << endl;
                system("pause");
                system("cls");
                return; 
            }
            else if(status == "2")
            {
                cout << "ԤԼʧ�ܣ�����ѡ���ʱ��λ����ѱ�ռ�ã�" << endl;
                system("pause");
                system("cls");
                return; 
            }
        }
    }

    cout << "ԤԼ�ɹ��������..." << endl;

    ofstream ofs(ORDER_FILE, ios::app);

    ofs << "date:" << date << " "; 
    ofs << "interval:" << interval << " "; 
    ofs << "stuId:" << this->GetId() << " "; 
    ofs << "stuName:" << this->GetName() << " "; 
    ofs << "roomId:" << room << " "; 
    ofs << "status:" << 1 << " " << endl;

    ofs.close();

    system("pause");
    system("cls");
}

//�鿴����ԤԼ
void Student::showMyOrder()
{
    OrderFile of;
    if (of.m_Size == 0)
    {
        cout << "��ԤԼ��¼" << endl;
        system("pause");
        system("cls");
        return;
    }
    bool flag = false; // �ж��Լ��Ƿ���ԤԼ��¼
    for (int i = 0; i < of.m_Size; i++)
    {
        if (atoi(of.m_orderData[i]["stuId"].c_str()) == this->m_Id)
        {
            flag = true;
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
    }
    if (!flag)
    {
        cout << "�����κ�ԤԼ��¼��" << endl;
    }

    system("pause");
    system("cls");
}

//�鿴����ԤԼ
void Student::showAllOrder()
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

//ȡ��ԤԼ
void Student::cancelOrder()
{
    OrderFile of;
    if (of.m_Size == 0)
    {
        cout << "��ԤԼ��¼" << endl;
        system("pause");
        system("cls");
        return;
    }

    cout << "����л�ԤԼ�ɹ��ļ�¼����ȡ������ѡ��Ҫȡ����ԤԼ" << endl;

    vector<int> v;      // ���ڼ�¼ԤԼ��¼���ڵ�ʵ��λ�õ��±�
    int index = 1;      // �����û�ѡ����±�

    for (int i = 0; i < of.m_Size; i++)
    {
        if (this->GetId() == atoi(of.m_orderData[i]["stuId"].c_str()))
        {
            if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
            {
                v.push_back(i);
                cout << index++ << "��";
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
                }
                cout << status << endl;
            }
        }
    }

    cout << "��ѡ��Ҫȡ����ԤԼ��¼������0���ʾ����" << endl;
    int choice = 0;
    while(true)
    {
        cin >> choice;
        if (choice >= 0 && choice < index)
        {
            if (choice == 0)
            {
                break;
            }
            else
            {
                of.m_orderData[v[choice - 1]]["status"] = "0";
                of.updataOrder();
                cout << "��ȡ��ԤԼ��" << endl;
                break;
            }
        }
        cout << "�����������������" << endl;
    }

    system("pause");
    system("cls");
}

//����ѧ������
void Student::SetName(string name)
{
    this->m_Name = name;
}

//��ȡѧ������
string Student::GetName()
{
    return this->m_Name;
}

//����ѧ������
void Student::SetPwd(string pwd)
{
    this->m_Pwd = pwd;
}

//��ȡѧ������
string Student::GetPwd()
{
    return this->m_Pwd;
}

//����ѧ�ŵĽӿ�
void Student::SetId(int id)
{
    this->m_Id = id;
}

//��ȡѧ�ŵĽӿ�
int Student::GetId()
{
    return this->m_Id;
}