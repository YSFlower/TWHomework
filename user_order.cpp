//
// Created by huang on 2017/9/9.
//
#include "user_order.h"

using namespace std;

/*
 * 计算当前订单的收入
 */
bool UserOrder::calculate()
{
    if(date.weekday < 5)
        for(int i=startTime-9;i<endTime-9;++i)
            price += workdayPrice[i];
    else
        for(int i=startTime-9;i<endTime-9;++i)
            price += weekendPrice[i];
}

/*
 * 取消订单
 */
bool UserOrder::cancelOrder()
{
    this -> cancel = true;
    if(this -> date.weekday < 5)
        this -> price *= 0.5;
    else
        this -> price *= 0.25;
    return true;

}



int calculateWeekday(int y, int m, int d) //基姆拉尔森公式计算周几
{
    if(m==1 || m==2) //把一月和二月换算成上一年的十三月和十四月
    {
        m += 12;
        y--;
    }
    int week = (d + 2 * m + 3 * ( m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7;
    return week;
}