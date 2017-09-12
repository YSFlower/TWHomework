#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include "ground_order.h"
#include "global.h"
#include "test.h"

using namespace std;

int main(int argc,const char** argv) {
    initGround(ground);                  //初始化球场类对象
    string order;
    while(getline(cin,order))           //循环读入订单
    {
        if(order == "")
            break;

        switch (parseOrder(order))      //解析订单，返回解析结果
        {
            case Error:
                cout<<"Error: the booking is invalid!"<<endl;
                break;
            case Conflict:
                cout<<"Error: the booking conflicts with existing bookings! "<<endl;
                break;
            case CancelError:
                cout<<"Error: the booking being cancelled does not exist! "<<endl;
                break;
            case Success:
                cout<<"Success: the booking is accepted!"<<endl;
                break;
            default:
                break;
        }
    }
    printTotalIncome();          //输出收入汇总
    return 0;
}

