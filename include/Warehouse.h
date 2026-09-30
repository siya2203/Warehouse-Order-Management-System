#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include "Order.h"
#include "Inventory.h"
#include "Graph.h"
#include "ReportManager.h"

#include <queue>
#include <stack>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

struct UrgentOrderComparator
{
    bool operator()(Order* a, Order* b)
    {
        return a->getOrderId() > b->getOrderId();
    }
};

class Warehouse
{
private:
    queue<Order*> standardOrders;

    priority_queue<
        Order*,
        vector<Order*>,
        UrgentOrderComparator
    > urgentOrders;

    stack<string> packingHistory;

    vector<Order*> allOrders;

    unordered_map<int, Order*> orderIndex;

    Inventory inventory;

    Graph warehouseGraph;

    ReportManager reportManager;

    int nextOrderId;

    bool validateOrder(Order* order);

    bool orderIdExists(int orderId) const;

    void processOrder(Order* order);

    void generatePickingList(Order* order);

    void updateOrderFile();

public:
    Warehouse();

    ~Warehouse();

    void loadInventory(string filename);

    void loadOrders(string filename);

    void addOrder(
        string customer,
        vector<OrderItem> items
    );

    void addUrgentOrder(
        string customer,
        vector<OrderItem> items
    );

    void viewPendingOrders() const;

    void processNextOrder();

    void searchProduct(string sku) const;

    void searchProducts(string keyword) const;

    void findRoute(
        int start,
        int destination
    );

    void viewInventory() const;

    void showReports() const;

    void displayPackingHistory() const;

    void displayMenu();

    void run();
};

#endif