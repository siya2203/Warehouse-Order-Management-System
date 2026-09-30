#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <vector>

using namespace std;

enum class OrderType
{
    STANDARD,
    URGENT
};

enum class OrderStatus
{
    CREATED,
    ALLOCATED,
    PICKING,
    PICKED,
    PACKED,
    READY_FOR_DISPATCH,
    DISPATCHED,
    CANCELLED
};

struct OrderItem
{
    string sku;
    int quantity;
    int pickedQuantity;

    OrderItem(string s, int q)
    {
        sku = s;
        quantity = q;
        pickedQuantity = 0;
    }
};

class Order
{
private:

    int orderId;
    string customerName;
    vector<OrderItem> items;

    OrderType type;
    OrderStatus status;

public:

    Order(
        int id,
        string customer,
        vector<OrderItem> orderItems,
        OrderType orderType
    );

    int getOrderId() const;

    string getCustomerName() const;

    // Used when modifying order items
    vector<OrderItem>& getItems();

    // Used when only reading order items
    const vector<OrderItem>& getItems() const;

    OrderType getType() const;

    OrderStatus getStatus() const;

    void setStatus(OrderStatus newStatus);

    string getStatusString() const;

    string getTypeString() const;

    void display() const;
};

#endif