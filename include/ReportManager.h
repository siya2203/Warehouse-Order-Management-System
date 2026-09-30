#ifndef REPORT_MANAGER_H
#define REPORT_MANAGER_H

#include "Order.h"

#include <vector>

using namespace std;

class ReportManager
{
public:
    void showOrderReport(
        const vector<Order*>& orders
    ) const;

    void showDispatchedOrders(
        const vector<Order*>& orders
    ) const;

    void showPendingOrders(
        const vector<Order*>& orders
    ) const;
};

#endif