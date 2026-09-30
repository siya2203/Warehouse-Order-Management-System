#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>
#include <unordered_map>

using namespace std;

struct Product
{
    string sku;
    string name;
    string category;
    int quantity;
    string location;
    int reorderThreshold;

    Product(
        string s = "",
        string n = "",
        string c = "",
        int q = 0,
        string l = "",
        int r = 0
    );
};

class Inventory
{
private:
    // Hash map:
    // SKU -> Product
    unordered_map<string, Product> products;

public:

    void loadFromFile(string filename);

    void saveToFile(string filename) const;

    bool addProduct(Product product);

    bool isAvailable(
        string sku,
        int quantity
    ) const;

    bool deductStock(
        string sku,
        int quantity
    );

    void addStock(
        string sku,
        int quantity
    );

    Product* getProduct(string sku);

    // Search by SKU
    void searchProduct(string sku) const;

    // Search by name or category
    void searchProducts(string keyword) const;

    void displayInventory() const;

    void checkLowStock() const;
};

#endif