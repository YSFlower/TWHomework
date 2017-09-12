//
// Created by huang on 2017/9/9.
//
#include <iostream>
#include <algorithm>
#include "ground_order.h"

using namespace std;
/*
 * 打印该场地所有订单
 */
int GroundOrder::printOrderIncome()
{
    //对订单按照时间先后排序
    sort(orderList.begin(),orderList.end(),[](UserOrder userOrder1,UserOrder userOrder2){return userOrder1.getOrderTime()<userOrder2.getOrderTime();});
    float sum = 0;
//    printf("场地: %s\n",this->groundName);
    cout<<"场地： "<<this->groundName<<endl;
    for(auto order : orderList)
    {
//        printf("%s ",order.getOrderTime());
        cout<<order.getOrderTime()<<" ";
        if(order.getCancel())
            printf("违约金 ");
        printf("%.2f元\n",order.getPrice());

        sum += order.getPrice();
    }
    printf("小计： %.2f元\n",sum);
    cout<<endl;
    return sum;

}
