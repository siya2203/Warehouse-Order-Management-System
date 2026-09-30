#include "../include/ReportManager.h"

#include <iostream>

using namespace std;

void ReportManager::showOrderReport(
    const vector<Order*>& orders
) const
{
    cout << "\n========== ORDER REPORT ==========\n";

    cout << "Total Orders: "
         << orders.size()
         << endl;

    int created = 0;
    int allocated = 0;
    int picking = 0;
    int picked = 0;
    int packed = 0;
    int readyForDispatch = 0;
    int dispatched = 0;
    int cancelled = 0;

    for (const Order* order : orders)
    {
        switch (order->getStatus())
        {
            case OrderStatus::CREATED:
                created++;
                break;

            case OrderStatus::ALLOCATED:
                allocated++;
                break;

            case OrderStatus::PICKING:
                picking++;
                break;

            case OrderStatus::PICKED:
                picked++;
                break;

            case OrderStatus::PACKED:
                packed++;
                break;

            case OrderStatus::READY_FOR_DISPATCH:
                readyForDispatch++;
                break;

            case OrderStatus::DISPATCHED:
                dispatched++;
                break;

            case OrderStatus::CANCELLED:
                cancelled++;
                break;
        }
    }

    cout << "Created Orders        : " << created << endl;
    cout << "Allocated Orders      : " << allocated << endl;
    cout << "Picking Orders        : " << picking << endl;
    cout << "Picked Orders         : " << picked << endl;
    cout << "Packed Orders         : " << packed << endl;
    cout << "Ready for Dispatch    : " << readyForDispatch << endl;
    cout << "Dispatched Orders     : " << dispatched << endl;
    cout << "Cancelled Orders      : " << cancelled << endl;

    cout << "==================================\n";
}

void ReportManager::showDispatchedOrders(
    const vector<Order*>& orders
) const
{
    cout << "\n====== DISPATCHED ORDERS ======\n";

    bool found = false;

    for (const Order* order : orders)
    {
        if (order->getStatus() == OrderStatus::DISPATCHED)
        {
            cout << "Order ID: "
                 << order->getOrderId()
                 << " | Customer: "
                 << order->getCustomerName()
                 << endl;

            found = true;
        }
    }

    if (!found)
    {
        cout << "No dispatched orders.\n";
    }

    cout << "===============================\n";
}

void ReportManager::showPendingOrders(
    const vector<Order*>& orders
) const
{
    cout << "\n======= PENDING ORDERS =======\n";

    bool found = false;

    for (const Order* order : orders)
    {
        OrderStatus status = order->getStatus();

        if (status != OrderStatus::DISPATCHED &&
            status != OrderStatus::CANCELLED)
        {
            cout << "Order ID: "
                 << order->getOrderId()
                 << " | Customer: "
                 << order->getCustomerName()
                 << " | Status: "
                 << order->getStatusString()
                 << endl;

            found = true;
        }
    }

    if (!found)
    {
        cout << "No pending orders.\n";
    }

    cout << "==============================\n";
}