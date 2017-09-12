//
// Created by 小霸王 on 17/9/12.
//


#ifndef TWHOMEWORK_TEST_H
#define TWHOMEWORK_TEST_H

#include "global.h"
#include <fstream>
#include <iostream>
using namespace std;

void test(string fileName)
{
    initGround(ground);
    fstream file(fileName);
    if(!file.is_open())
    {
        cout<<"Failed openning "<<fileName<<endl;
        return;
    }
    string order;
    while(getline(file,order))           //循环读入订单
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
    printTotalIncome();
}

void test1()
{
    test("/Users/apple/Documents/TWHomework/test/test1");
}

void test2()
{
    test("/Users/apple/Documents/TWHomework/test/test2");
}

#endif //TWHOMEWORK_TEST_H
