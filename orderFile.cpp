#include "orderFile.h"

void StringSplit(string temp, map<string, string> &m)
{
    string key;
    string value;

    int pos = temp.find(':');
    if (pos != -1)
    {
        key = temp.substr(0, pos);
        value = temp.substr(pos + 1, temp.size() - pos - 1);
        m.insert(pair<string, string>(key, value));
    }
}

OrderFile::OrderFile()
{
    ifstream ifs;
    ifs.open(ORDER_FILE, ios::in);

    string date;    // 日期
    string interval;    // 时间段
    string stuId;       // 学生编号
    string stuName;     // 学生姓名
    string roomId;      // 机房编号
    string status;      // 预约状态

    this->m_Size = 0;

    while (ifs >> date && ifs >> interval && ifs >> stuId && ifs >> stuName && ifs >> roomId && ifs >> status)
    {
        map<string, string> m;

        StringSplit(date, m);
        StringSplit(interval, m);
        StringSplit(stuId, m);
        StringSplit(stuName, m);
        StringSplit(roomId, m);
        StringSplit(status, m);

        this->m_orderData.insert(pair<int, map<string, string>>(this->m_Size, m));
        this->m_Size++;
    }

    //测试代码
    // for (map<int, map<string, string>>::iterator it = this->m_orderData.begin(); it != this->m_orderData.end(); it++)
    // {
    //     cout << "key = " << it->first << "    value = " ;
    //     for (map<string, string>::iterator mit = it->second.begin(); mit != it->second.end(); mit++)
    //     {
    //         cout << mit->first << ":" << mit->second << "  ";
    //     }
    //     cout << endl;
    // }
}

// 更新预约记录
void OrderFile::updataOrder()
{
    if (this->m_Size == 0)
    {
        return;
    }

    ofstream ofs(ORDER_FILE, ios::out | ios::trunc);
    for (int i = 0; i < this->m_Size; i++)
    {
        ofs << "date:" << this->m_orderData[i]["date"] << " ";
        ofs << "interval:" << this->m_orderData[i]["interval"] << " ";
        ofs << "stuId:" << this->m_orderData[i]["stuId"] << " ";
        ofs << "stuName:" << this->m_orderData[i]["stuName"] << " ";
        ofs << "roomId:" << this->m_orderData[i]["roomId"] << " ";
        ofs << "status:" << this->m_orderData[i]["status"] << endl;
    }
    ofs.close();
}