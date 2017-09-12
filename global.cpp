//
// Created by huang on 2017/9/11.
//


#include "global.h"
#include <vector>
#include <iostream>
#include <map>
#include <sstream>

using namespace std;


/*
 * 取消订单，必须与历史订单中的一条记录完全匹配进行取消
 */
bool matchCancelOrder(UserOrder& order, vector<UserOrder>& vector)
{
    for(auto &i : vector)
    {
        if(order.getOrderString().substr(0,29)==i.getOrderString().substr(0,29) && i.getCancel()==false)
        {
            i.cancelOrder();
            return true;
        }
    }
    return false;
}

/*
 * 判断当前订单是否和历史订单冲突
 */
bool isConflict(UserOrder& order, vector<UserOrder>& vector)
{
    for(auto i : vector)
    {
        if(order.getStartTime()>=i.getEndTime() || order.getEndTime()<=i.getStartTime())
            continue;
        else if(i.getCancel()==true)
            continue;
        else
            return true;
    }
    return false;
}
/*
 * 初始化场地对象
 */
void initGround(map<string,GroundOrder> &ground)
{
    GroundOrder ga = GroundOrder("A");
    GroundOrder gb = GroundOrder("B");
    GroundOrder gc = GroundOrder("C");
    GroundOrder gd = GroundOrder("D");
    ground["A"] = ga;
    ground["B"] = gb;
    ground["C"] = gc;
    ground["D"] = gd;
}


/*
 * 解析日期，鸡西结果返回一个Date对象
 */
Date parseDate(string dateString)
{
    string yearString = dateString.substr(0,dateString.find('-'));
    int year = stoi(yearString);
    dateString = dateString.substr(dateString.find('-')+1);
    string monthString = dateString.substr(0,dateString.find('-'));
    int month = stoi(monthString);
    dateString = dateString.substr(dateString.find('-')+1);
    string dayString = dateString.substr(1);
    int day = stoi(dayString);
    int weekday = calculateWeekday(year, month, day);
    Date d(year,month,day,weekday);
    return d;
}

/*
 * 解析订单预定的时间区间
 */
void parseTimeFromTo(string timeFromTo,int& start,int& end)
{
    string startString = timeFromTo.substr(0,timeFromTo.find(':'));
    start = stoi(startString);
    string endString = timeFromTo.substr(timeFromTo.find('~')+1,timeFromTo.find(':'));
    end = stoi(endString);
}


/*
 * 解析订单
 */
STATUS parseOrder(string order)
{
    regex bookPattern("^(U\\d{3}) (\\d{4}-\\d{2}-\\d{2}) (\\d{2}):00~(\\d{2}):00 ([ABCD])( C)?$");
    if(!regex_match(order,bookPattern))
    {
        return Error;
    }
    stringstream stream;        //输入流
    stream<<order;
    string userId;              //用户ID
    string dateString;          //日期字符串
    string timeString;          //时间字符串
    string groundId;            //场地ID
    string cancelSymbol;        //取消标记

    stream>>userId;

    regex datePattern("((([0-9]{3}[1-9]|[0-9]{2}[1-9][0-9]{1}|[0-9]{1}[1-9][0-9]{2}|[1-9][0-9]{3})-(((0[13578]|1[02])-(0[1-9]|[12][0-9]|3[01]))|((0[469]|11)-(0[1-9]|[12][0-9]|30))|(02-(0[1-9]|[1][0-9]|2[0-8]))))|((([0-9]{2})(0[48]|[2468][048]|[13579][26])|((0[48]|[2468][048]|[3579][26])00))-02-29))");
    stream>>dateString;
    if(!regex_match(dateString,datePattern))            //正则表达式匹配日期
        return Error;
    Date d = parseDate(dateString);


    stream>>timeString;
    int start;
    int end;
    parseTimeFromTo(timeString,start,end);              //解析订单时间区间
    if(start >= end || start<9 || end>22)
    {
        return Error;
    }


    stream>>groundId;

    bool cancel = false;
    stream>>cancelSymbol;
    if(order.length() > 29 && cancelSymbol == "C")      //判断是否为取消订单
    {
        cancel = true;
    }
    UserOrder userOrder(userId,d,start,end,groundId,cancel,order);          //生成订单对象

    if(cancel && !matchCancelOrder(userOrder,ground[groundId].getOrderList()))  //取消订单是否能匹配历史订单
    {
        return CancelError;
    }

    if(!cancel && isConflict(userOrder,ground[groundId].getOrderList()))        //当前订单是否与历史订单冲突
    {
        return Conflict;
    }
    if(!cancel)
        ground[groundId].getOrderList().push_back(userOrder);                   //将非取消订单计入该场地的订单队列里面
    return Success;
}

/*
 * 打印收入汇总
 */
void printTotalIncome()
{

    cout<<"收入汇总:"<<endl;
    cout<<"---"<<endl;
    float sum = 0;
    for(auto i : ground)
    {
        sum += i.second.printOrderIncome();
    }
    printf("---\n");
    printf("总计: %.2f元",sum);
}

map<string,GroundOrder> ground;