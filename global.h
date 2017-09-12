//
// Created by huang on 2017/9/11.
//

#ifndef TWHOMEWORK_GLOBAL_H
#define TWHOMEWORK_GLOBAL_H

#include "ground_order.h"
#include <map>
#include <regex>
using namespace std;

enum STATUS
{
    Error,
    Conflict,
    CancelError,
    Success
};

bool matchCancelOrder(UserOrder& order, vector<UserOrder>& vector);
bool isConflict(UserOrder& order, vector<UserOrder>& vector);
void initGround(map<string,GroundOrder> &ground);
Date parseDate(string dateString);
STATUS parseOrder(string order);
void printTotalIncome();


extern map<string,GroundOrder> ground;
#endif //TWHOMEWORK_GLOBAL_H
