#include "../include/Warehouse.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Warehouse::Warehouse()
    : warehouseGraph(8),
      nextOrderId(1001)
{
    /*
        Warehouse locations:

        0 = Receiving
        1 = Zone A
        2 = Zone B
        3 = Zone C
        4 = Picking Station
        5 = Packing Station
        6 = Dispatch
        7 = Storage
    */

    warehouseGraph.addEdge(0, 1, 2);
    warehouseGraph.addEdge(1, 2, 3);
    warehouseGraph.addEdge(2, 3, 2);
    warehouseGraph.addEdge(1, 4, 4);
    warehouseGraph.addEdge(2, 4, 2);
    warehouseGraph.addEdge(3, 5, 3);
    warehouseGraph.addEdge(4, 5, 2);
    warehouseGraph.addEdge(5, 6, 2);
    warehouseGraph.addEdge(2, 7, 4);
}

Warehouse::~Warehouse()
{
    for (Order* order : allOrders)
    {
        delete order;
    }
}

void Warehouse::loadInventory(string filename)
{
    inventory.loadFromFile(filename);

    cout << "\nInventory loaded successfully." << endl;
}

void Warehouse::loadOrders(string filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        cout << "Could not open orders file." << endl;
        return;
    }

    string line;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);

        string idText;
        string customer;
        string typeText;
        string statusText;
        string itemsText;

        getline(ss, idText, '|');
        getline(ss, customer, '|');
        getline(ss, typeText, '|');
        getline(ss, statusText, '|');
        getline(ss, itemsText, '|');

        int id = stoi(idText);

        OrderType type;

        if (typeText == "URGENT")
            type = OrderType::URGENT;
        else
            type = OrderType::STANDARD;

        vector<OrderItem> items;

        stringstream itemStream(itemsText);
        string itemData;

        while (getline(itemStream, itemData, ','))
        {
            size_t separator = itemData.find(':');

            if (separator == string::npos)
                continue;

            string sku =
                itemData.substr(0, separator);

            int quantity =
                stoi(itemData.substr(separator + 1));

            items.emplace_back(sku, quantity);
        }

        Order* order = new Order(
            id,
            customer,
            items,
            type
        );

        // Restore order status
        if (statusText == "ALLOCATED")
            order->setStatus(OrderStatus::ALLOCATED);

        else if (statusText == "PICKING")
            order->setStatus(OrderStatus::PICKING);

        else if (statusText == "PICKED")
            order->setStatus(OrderStatus::PICKED);

        else if (statusText == "PACKED")
            order->setStatus(OrderStatus::PACKED);

        else if (statusText == "READY_FOR_DISPATCH")
            order->setStatus(
                OrderStatus::READY_FOR_DISPATCH
            );

        else if (statusText == "DISPATCHED")
            order->setStatus(OrderStatus::DISPATCHED);

        else if (statusText == "CANCELLED")
            order->setStatus(OrderStatus::CANCELLED);

        else
            order->setStatus(OrderStatus::CREATED);

        allOrders.push_back(order);
        orderIndex[id] = order;

        // Put active CREATED orders back into queues
        if (order->getStatus() == OrderStatus::CREATED)
        {
            if (type == OrderType::URGENT)
                urgentOrders.push(order);
            else
                standardOrders.push(order);
        }

        // Keep future order IDs unique
        if (id >= nextOrderId)
            nextOrderId = id + 1;
    }

    file.close();

    cout << "Orders loaded successfully." << endl;
}

bool Warehouse::validateOrder(Order* order)
{
    for (const auto& item : order->getItems())
    {
        if (item.quantity <= 0)
        {
            cout << "\nInvalid quantity for SKU: "
                 << item.sku << endl;

            return false;
        }

        Product* product =
            inventory.getProduct(item.sku);

        if (product == nullptr)
        {
            cout << "\nInvalid SKU: "
                 << item.sku << endl;

            return false;
        }

        if (!inventory.isAvailable(
                item.sku,
                item.quantity))
        {
            cout << "\nInsufficient stock for SKU: "
                 << item.sku << endl;

            return false;
        }
    }

    return true;
}

void Warehouse::addOrder(
    string customer,
    vector<OrderItem> items
)
{
    Order* order = new Order(
        nextOrderId++,
        customer,
        items,
        OrderType::STANDARD
    );

    if (!validateOrder(order))
    {
        delete order;
        return;
    }

    allOrders.push_back(order);
    orderIndex[order->getOrderId()] = order;
    standardOrders.push(order);

    cout << "\nStandard order created successfully.";
    cout << "\nOrder ID: "
         << order->getOrderId()
         << endl;

    // Save order to file
    ofstream file("data/orders.txt", ios::app);

    if (file.is_open())
    {
        file << order->getOrderId()
             << "|"
             << order->getCustomerName()
             << "|"
             << order->getTypeString()
             << "|"
             << order->getStatusString()
             << "|";

        for (size_t i = 0;
             i < order->getItems().size();
             i++)
        {
            file << order->getItems()[i].sku
                 << ":"
                 << order->getItems()[i].quantity;

            if (i + 1 < order->getItems().size())
                file << ",";
        }

        file << endl;

        file.close();
    }
    else
    {
        cout << "Warning: Could not save order to file."
             << endl;
    }
}

void Warehouse::addUrgentOrder(
    string customer,
    vector<OrderItem> items
)
{
    Order* order = new Order(
        nextOrderId++,
        customer,
        items,
        OrderType::URGENT
    );

    if (!validateOrder(order))
    {
        delete order;
        return;
    }

    allOrders.push_back(order);
    orderIndex[order->getOrderId()] = order;
    urgentOrders.push(order);

    cout << "\nUrgent order created successfully.";
    cout << "\nOrder ID: "
         << order->getOrderId()
         << endl;

    // Save order to file
    ofstream file("data/orders.txt", ios::app);

    if (file.is_open())
    {
        file << order->getOrderId()
             << "|"
             << order->getCustomerName()
             << "|"
             << order->getTypeString()
             << "|"
             << order->getStatusString()
             << "|";

        for (size_t i = 0;
             i < order->getItems().size();
             i++)
        {
            file << order->getItems()[i].sku
                 << ":"
                 << order->getItems()[i].quantity;

            if (i + 1 < order->getItems().size())
                file << ",";
        }

        file << endl;

        file.close();
    }
    else
    {
        cout << "Warning: Could not save order to file."
             << endl;
    }
}

void Warehouse::viewPendingOrders() const
{
    cout << "\n========== STANDARD ORDERS ==========\n";

    if (standardOrders.empty())
    {
        cout << "No standard orders pending.\n";
    }
    else
    {
        queue<Order*> temp = standardOrders;

        while (!temp.empty())
        {
            temp.front()->display();
            temp.pop();
        }
    }

    cout << "\n========== URGENT ORDERS ==========\n";

    if (urgentOrders.empty())
    {
        cout << "No urgent orders pending.\n";
    }
    else
    {
        auto temp = urgentOrders;

        while (!temp.empty())
        {
            temp.top()->display();
            temp.pop();
        }
    }
}

void Warehouse::processNextOrder()
{
    Order* order = nullptr;

    // Urgent orders are processed first
    if (!urgentOrders.empty())
    {
        order = urgentOrders.top();
        urgentOrders.pop();

        cout << "\nProcessing URGENT order...\n";
    }

    // Otherwise process standard order
    else if (!standardOrders.empty())
    {
        order = standardOrders.front();
        standardOrders.pop();

        cout << "\nProcessing STANDARD order...\n";
    }

    else
    {
        cout << "\nNo pending orders.\n";
        return;
    }

    processOrder(order);
}

void Warehouse::processOrder(Order* order)
{
    cout << "\nProcessing Order ID: "
         << order->getOrderId()
         << endl;

    // ALLOCATION
    order->setStatus(OrderStatus::ALLOCATED);

    for (auto& item : order->getItems())
    {
        if (!inventory.deductStock(
                item.sku,
                item.quantity))
        {
            cout << "\nInventory allocation failed.\n";

            order->setStatus(
                OrderStatus::CANCELLED
            );

            return;
        }
    }

    cout << "Inventory allocated successfully.\n";

    // PICKING
    order->setStatus(OrderStatus::PICKING);

    generatePickingList(order);

    for (auto& item : order->getItems())
    {
        item.pickedQuantity = item.quantity;
    }

    order->setStatus(OrderStatus::PICKED);

    cout << "\nAll items picked successfully.\n";

    // PACKING
    cout << "\nPacking order...\n";

    order->setStatus(OrderStatus::PACKED);

    string history =
        "Order " +
        to_string(order->getOrderId()) +
        " packed";

    packingHistory.push(history);

    cout << "Order packed successfully.\n";

    // READY FOR DISPATCH
    order->setStatus(
        OrderStatus::READY_FOR_DISPATCH
    );

    // DISPATCH
    cout << "\nDispatching order...\n";

    order->setStatus(
        OrderStatus::DISPATCHED
    );

    cout << "\nOrder "
         << order->getOrderId()
         << " dispatched successfully!\n";
}

void Warehouse::generatePickingList(Order* order)
{
    cout << "\n========== PICKING LIST ==========\n";

    for (const auto& item : order->getItems())
    {
        Product* product =
            inventory.getProduct(item.sku);

        if (product != nullptr)
        {
            cout << "SKU      : "
                 << product->sku
                 << endl;

            cout << "Product  : "
                 << product->name
                 << endl;

            cout << "Quantity : "
                 << item.quantity
                 << endl;

            cout << "Location : "
                 << product->location
                 << endl;

            cout << "-----------------------------\n";
        }
    }

    cout << "==================================\n";
}

void Warehouse::searchProduct(string sku) const
{
    inventory.searchProduct(sku);
}

void Warehouse::findRoute(
    int start,
    int destination
)
{
    cout << "\n========== BFS ROUTE ==========\n";

    vector<int> bfsPath =
        warehouseGraph.bfs(
            start,
            destination
        );

    if (bfsPath.empty())
    {
        cout << "No route found using BFS.\n";
    }
    else
    {
        for (int location : bfsPath)
        {
            cout << location << " ";
        }

        cout << endl;
    }

    cout << "\n========== DIJKSTRA ROUTE ==========\n";

    vector<int> dijkstraPath =
        warehouseGraph.dijkstra(
            start,
            destination
        );

    if (dijkstraPath.empty())
    {
        cout << "No route found using Dijkstra.\n";
    }
    else
    {
        for (int location : dijkstraPath)
        {
            cout << location << " ";
        }

        cout << endl;
    }
}

void Warehouse::viewInventory() const
{
    inventory.displayInventory();
    inventory.checkLowStock();
}

void Warehouse::showReports() const
{
    reportManager.showOrderReport(allOrders);

    reportManager.showDispatchedOrders(allOrders);

    reportManager.showPendingOrders(allOrders);
}

void Warehouse::displayPackingHistory() const
{
    cout << "\n========== PACKING HISTORY ==========\n";

    if (packingHistory.empty())
    {
        cout << "No packing operations recorded.\n";
        return;
    }

    stack<string> temp = packingHistory;

    while (!temp.empty())
    {
        cout << temp.top() << endl;
        temp.pop();
    }
}

void Warehouse::displayMenu()
{
    cout << "\n\n========================================\n";
    cout << "     WAREHOUSE ORDER MANAGEMENT SYSTEM\n";
    cout << "========================================\n";

    cout << "1. Add Standard Order\n";
    cout << "2. Add Urgent Order\n";
    cout << "3. View Pending Orders\n";
    cout << "4. Process Next Order\n";
    cout << "5. Search Product by SKU\n";
    cout << "6. Find Warehouse Route\n";
    cout << "7. View Inventory\n";
    cout << "8. View Reports\n";
    cout << "9. View Packing History\n";
    cout << "10. Exit\n";

    cout << "========================================\n";
}

void Warehouse::run()
{
    int choice;

    while (true)
    {
        displayMenu();

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            case 2:
            {
                string customer;
                int numberOfItems;

                cout << "Enter customer name: ";
                cin.ignore();
                getline(cin, customer);

                cout << "Enter number of items: ";
                cin >> numberOfItems;

                vector<OrderItem> items;

                for (int i = 0;
                     i < numberOfItems;
                     i++)
                {
                    string sku;
                    int quantity;

                    cout << "\nEnter SKU: ";
                    cin >> sku;

                    cout << "Enter quantity: ";
                    cin >> quantity;

                    items.emplace_back(
                        sku,
                        quantity
                    );
                }

                if (choice == 1)
                {
                    addOrder(
                        customer,
                        items
                    );
                }
                else
                {
                    addUrgentOrder(
                        customer,
                        items
                    );
                }

                break;
            }

            case 3:
                viewPendingOrders();
                break;

            case 4:
                processNextOrder();
                break;

            case 5:
            {
                string sku;

                cout << "Enter SKU: ";
                cin >> sku;

                searchProduct(sku);

                break;
            }

            case 6:
            {
                int start;
                int destination;

                cout << "\nWarehouse Locations:\n";
                cout << "0 = Receiving\n";
                cout << "1 = Zone A\n";
                cout << "2 = Zone B\n";
                cout << "3 = Zone C\n";
                cout << "4 = Picking Station\n";
                cout << "5 = Packing Station\n";
                cout << "6 = Dispatch\n";
                cout << "7 = Storage\n";

                cout << "\nEnter starting location: ";
                cin >> start;

                cout << "Enter destination: ";
                cin >> destination;

                findRoute(
                    start,
                    destination
                );

                break;
            }

            case 7:
                viewInventory();
                break;

            case 8:
                showReports();
                break;

            case 9:
                displayPackingHistory();
                break;

            case 10:
                cout << "\nThank you for using the system!\n";
                return;

            default:
                cout << "\nInvalid choice. Try again.\n";
        }
    }
}