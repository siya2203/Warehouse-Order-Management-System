#include "../include/Order.h"

#include <iostream>

using namespace std;

Order::Order(
    int id,
    string customer,
    vector<OrderItem> orderItems,
    OrderType orderType
)
{
    orderId = id;
    customerName = customer;
    items = orderItems;
    type = orderType;
    status = OrderStatus::CREATED;
}

int Order::getOrderId() const
{
    return orderId;
}

string Order::getCustomerName() const
{
    return customerName;
}

vector<OrderItem>& Order::getItems()
{
    return items;
}

const vector<OrderItem>& Order::getItems() const
{
    return items;
}

OrderType Order::getType() const
{
    return type;
}

OrderStatus Order::getStatus() const
{
    return status;
}

void Order::setStatus(OrderStatus newStatus)
{
    status = newStatus;
}

string Order::getStatusString() const
{
    switch (status)
    {
        case OrderStatus::CREATED:
            return "CREATED";

        case OrderStatus::ALLOCATED:
            return "ALLOCATED";

        case OrderStatus::PICKING:
            return "PICKING";

        case OrderStatus::PICKED:
            return "PICKED";

        case OrderStatus::PACKED:
            return "PACKED";

        case OrderStatus::READY_FOR_DISPATCH:
            return "READY_FOR_DISPATCH";

        case OrderStatus::DISPATCHED:
            return "DISPATCHED";

        case OrderStatus::CANCELLED:
            return "CANCELLED";
    }

    return "UNKNOWN";
}

string Order::getTypeString() const
{
    if (type == OrderType::URGENT)
        return "URGENT";

    return "STANDARD";
}

void Order::display() const
{
    cout << "\n-----------------------------" << endl;

    cout << "Order ID   : "
         << orderId << endl;

    cout << "Customer   : "
         << customerName << endl;

    cout << "Type       : "
         << getTypeString() << endl;

    cout << "Status     : "
         << getStatusString() << endl;

    cout << "Items:" << endl;

    for (const auto& item : items)
    {
        cout << "  SKU: "
             << item.sku
             << " | Quantity: "
             << item.quantity
             << " | Picked: "
             << item.pickedQuantity
             << endl;
    }

    cout << "-----------------------------" << endl;
}