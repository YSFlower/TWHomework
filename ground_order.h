//
// Created by huang on 2017/9/9.
//

#ifndef TWHOMEWORK_GROUND_ORDER_H
#define TWHOMEWORK_GROUND_ORDER_H

#include <vector>
#include "user_order.h"
using namespace std;

/*
 * 场地类
 */
class GroundOrder
{
public:
    GroundOrder() { groundName = ""; orderList = {};};
    inline GroundOrder(string groundName):groundName(groundName){};
    string getId(){ return groundName; };
    vector<UserOrder> & getOrderList() { return orderList; };
    int printOrderIncome();
private:
    string groundName;
    vector<UserOrder> orderList;
};

#endif //TWHOMEWORK_GROUND_ORDER_H
