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
        cout << COMPUTER_FILE << "不存在！" << endl;
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

//学生菜单页面
void Student::openMenu()
{
    cout << "欢迎" << this->m_Name << "同学！" << endl;
    cout << "\t\t ————————————————————————————————————\n";
    cout << "\t\t|                                    |\n";
    cout << "\t\t|           1、申请预约              |\n";
    cout << "\t\t|                                    |\n";
    cout << "\t\t|           2、查看我的预约          |\n";
    cout << "\t\t|                                    |\n";
    cout << "\t\t|           3、查看所有预约          |\n";
    cout << "\t\t|                                    |\n";
    cout << "\t\t|           4、取消预约              |\n";
    cout << "\t\t|                                    |\n";
    cout << "\t\t|           0、注销登录              |\n";
    cout << "\t\t|                                    |\n";
    cout << "\t\t ————————————————————————————————————\n";
    cout << "请选择您的操作：" ;
}

//申请预约
void Student::applyOrder()
{
    OrderFile of;

    cout << "机房开发时间为周一至周五" << endl;
    cout << "1、周一";
    cout << "  2、周二";
    cout << "  3、周三";
    cout << "  4、周四";
    cout << "  5、周五" << endl;
    cout << "请选择申请预约的时间：" << endl;
    int date = 0;   // 选择的日期
    int interval = 0;   // 选择的时间段（上午或下午）
    int room = 0;   // 选择的机房

    while (true)
    {
        cin >> date;

        if (date >= 1 && date <= 5)
        {
            break;
        }
        cout << "输入错误，请重新输入！" << endl;
    }

    cout << "请选择申请预约的时间段：" << endl;
    cout << "1、上午";
    cout << "  2、下午" << endl;

    while (true)
    {
        cin >> interval;

        if (interval >= 1 && interval <= 2)
        {
            break;
        }
        cout << "输入错误，请重新输入！" << endl;
    }

    cout << "请选择机房：" << endl;
    for (vector<ComputerRoom>::iterator it = this->vCom.begin(); it != this->vCom.end(); it++)
    {
        cout << it->m_ComId << "号机房容量：" << it->m_MaxNum << "    ";
    }
    cout << endl;

    while (true)
    {
        cin >> room;

        if (room >= 1 && room <= 3)
        {
            break;
        }
        cout << "输入错误，请重新输入！" << endl;
    }

    for (int i = 0; i < of.m_Size; i++)
    {
        if (date == atoi(of.m_orderData[i]["date"].c_str()) && interval == atoi(of.m_orderData[i]["interval"].c_str()) && room == atoi(of.m_orderData[i]["roomId"].c_str()))
        {
            string status = of.m_orderData[i]["status"];
            if (status == "1")
            {
                cout << "预约失败，您所选择的时间段机房正在审核中！" << endl;
                system("pause");
                system("cls");
                return; 
            }
            else if(status == "2")
            {
                cout << "预约失败，您所选择的时间段机房已被占用！" << endl;
                system("pause");
                system("cls");
                return; 
            }
        }
    }

    cout << "预约成功，审核中..." << endl;

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

//查看自身预约
void Student::showMyOrder()
{
    OrderFile of;
    if (of.m_Size == 0)
    {
        cout << "无预约记录" << endl;
        system("pause");
        system("cls");
        return;
    }
    bool flag = false; // 判断自己是否有预约记录
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
    }
    if (!flag)
    {
        cout << "您无任何预约记录！" << endl;
    }

    system("pause");
    system("cls");
}

//查看所有预约
void Student::showAllOrder()
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

//取消预约
void Student::cancelOrder()
{
    OrderFile of;
    if (of.m_Size == 0)
    {
        cout << "无预约记录" << endl;
        system("pause");
        system("cls");
        return;
    }

    cout << "审核中或预约成功的记录可以取消，请选择要取消的预约" << endl;

    vector<int> v;      // 用于记录预约记录所在的实际位置的下标
    int index = 1;      // 用于用户选择的下标

    for (int i = 0; i < of.m_Size; i++)
    {
        if (this->GetId() == atoi(of.m_orderData[i]["stuId"].c_str()))
        {
            if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
            {
                v.push_back(i);
                cout << index++ << "、";
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
                }
                cout << status << endl;
            }
        }
    }

    cout << "请选择要取消的预约记录，输入0则表示返回" << endl;
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
                cout << "已取消预约！" << endl;
                break;
            }
        }
        cout << "输入错误，请重新输入" << endl;
    }

    system("pause");
    system("cls");
}

//设置学生姓名
void Student::SetName(string name)
{
    this->m_Name = name;
}

//读取学生姓名
string Student::GetName()
{
    return this->m_Name;
}

//设置学生密码
void Student::SetPwd(string pwd)
{
    this->m_Pwd = pwd;
}

//读取学生密码
string Student::GetPwd()
{
    return this->m_Pwd;
}

//设置学号的接口
void Student::SetId(int id)
{
    this->m_Id = id;
}

//读取学号的接口
int Student::GetId()
{
    return this->m_Id;
}