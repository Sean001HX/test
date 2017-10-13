
#ifndef TABLESTRUCT_H
#define TABLESTRUCT_H

#include <string>

// 通用消息结构体
struct CommonInfoSt
{
    std::string cmd_code_;
};

// 登陆消息结构体
struct LoginInfoSt
{
    std::string cmd_code_;

    std::string login_name_;
    std::string password_;
    std::string resource_;
};

// 查询所有机构账户含越级
struct AgencyQrySt
{
    std::string cmd_code_;
    std::string qry_login_name_;
};

// 新增子账户
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