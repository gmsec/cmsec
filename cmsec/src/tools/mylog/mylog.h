/********************************************************************
    ����ʱ�䣺    2016/08/03  17:50:19
    �ļ�����      OnLogDeal.h
    ���ߣ�        лС��

    ���ܣ�        1.��־���
                 2.

    ˵����        1.
                 2.
*********************************************************************/

#ifndef _ONLOGDEAL_H_
#define _ONLOGDEAL_H_
#include <string>
#include <vector>
#include <map>
#include <mutex>

class MyLog
{
public:
    static void PrintToFile(const std::string& fname, const std::vector<std::string>& prints, bool isClear = true);
public:
    static void OnDealCallBack();//��ʼ������־
private:
    static std::mutex m_mutex;
    static std::map<std::string, std::vector<std::string>> m_log_map;
    static void PrintError(const std::string& strerror);

};


#endif // 
