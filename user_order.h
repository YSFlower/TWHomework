//
// Created by huang on 2017/9/9.
//
#include <string>
#include <vector>

using namespace std;
#ifndef TWHOMEWORK_USER_ORDER_H
#define TWHOMEWORK_USER_ORDER_H
//U123 2016-06-02 20:00~22:00 A C
/*
 * 日期类
 */
class Date
{
public:
    Date(int year,int month,int day,int weekday):
        year(year),month(month),day(day),weekday(weekday){};

    int year = 0;
    int month = 0;
    int day = 0;
    int weekday = 0;


};
/*
 * 用户订单类
 */
class UserOrder
{
public:
    UserOrder();
//    ~UserOrder();
    UserOrder(string userId,Date date,int startTime,int endTime,string groundId,bool cancel,string orderString):
            userId(userId),date(date),startTime(startTime),endTime(endTime),groundId(groundId),cancel(cancel),orderString(orderString)
    {
        calculate();
    };

     bool cancelOrder();
     bool calculate();
    string getGroundId() { return groundId; };
    string getOrderString() { return orderString; };
    string getOrderTime() { return orderString.substr(5,22); };
    bool getCancel() { return cancel; };
    float getPrice() { return price; };
    int getStartTime() { return startTime; };
    int getEndTime() { return endTime; };
private:
    string userId;
    Date date;
    int startTime;
    int endTime;
    string groundId;
    bool cancel = false;
    string orderString;
    float price = 0;
    vector<int> workdayPrice = { 30,30,30,50,50,50,50,50,50,80,80,60,60 };         //工作日价格
    vector<int> weekendPrice = { 40,40,40,50,50,50,50,50,50,60,60,60,60 };          //周末价格
};


int calculateWeekday(int y, int m, int d); //基姆拉尔森公式计算周几

#endif //TWHOMEWORK_USER_ORDER_H
