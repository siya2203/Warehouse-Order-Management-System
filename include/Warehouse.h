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
    // Standard orders -> FIFO Queue
    queue<Order*> standardOrders;

    // Urgent orders -> Priority Queue
    priority_queue<
        Order*,
        vector<Order*>,
        UrgentOrderComparator
    > urgentOrders;

    // Recent packing operations -> Stack
    stack<string> packingHistory;

    // Stores all orders
    vector<Order*> allOrders;

    // Fast order lookup
    unordered_map<int, Order*> orderIndex;

    // Inventory management
    Inventory inventory;

    // Warehouse routes
    Graph warehouseGraph;

    // Report management
    ReportManager reportManager;

    // Generates order IDs
    int nextOrderId;

    // Internal functions
    bool validateOrder(Order* order);
    void processOrder(Order* order);
    void generatePickingList(Order* order);

public:
    Warehouse();

    ~Warehouse();

    // Inventory
    void loadInventory(string filename);

    // Orders
    void loadOrders(string filename);

    void addOrder(
        string customer,
        vector<OrderItem> items
    );

    void addUrgentOrder(
        string customer,
        vector<OrderItem> items
    );

    // Order processing
    void viewPendingOrders() const;
    void processNextOrder();

    // Product search
    void searchProduct(string sku) const;

    // Warehouse routing
    void findRoute(
        int start,
        int destination
    );

    // Inventory display
    void viewInventory() const;

    // Reports
    void showReports() const;

    // Packing history
    void displayPackingHistory() const;

    // User interface
    void displayMenu();
    void run();
};

#endif