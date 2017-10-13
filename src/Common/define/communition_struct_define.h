
#ifndef TABLESTRUCT_H
#define TABLESTRUCT_H

#include <string>

// ͨ����Ϣ�ṹ��
struct CommonInfoSt
{
    std::string cmd_code_;
};

// ��½��Ϣ�ṹ��
struct LoginInfoSt
{
    std::string cmd_code_;

    std::string login_name_;
    std::string password_;
    std::string resource_;
};

// ��ѯ���л����˻���Խ��
struct AgencyQrySt
{
    std::string cmd_code_;
    std::string qry_login_name_;
};

// �������˻�
struct TradeAccAddSt
{
    std::string cmd_code_;
    std::string create_login_name_;

    std::string loginname_;
    std::string password_;
    std::string accountname_;
    double      inferiorfund_;
    double      priorityfund_;
    std::string upperfundname_;
    std::string uppermanager_;
    double      warningline_;
    double      forceline_;
    double      limitline_;
    double      leveragerate_;
    double      commissionrate_;
    double      profitcommrate_;
    bool        ishedfeornot_;

};

#endif