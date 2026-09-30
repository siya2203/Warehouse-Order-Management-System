#include "../include/Inventory.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

Product::Product(
    string s,
    string n,
    string c,
    int q,
    string l,
    int r
)
{
    sku = s;
    name = n;
    category = c;
    quantity = q;
    location = l;
    reorderThreshold = r;
}

void Inventory::loadFromFile(string filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        cout << "Could not open inventory file." << endl;
        return;
    }

    string line;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);

        string sku;
        string name;
        string category;
        string quantityText;
        string location;
        string thresholdText;

        getline(ss, sku, '|');
        getline(ss, name, '|');
        getline(ss, category, '|');
        getline(ss, quantityText, '|');
        getline(ss, location, '|');
        getline(ss, thresholdText, '|');

        int quantity = stoi(quantityText);
        int threshold = stoi(thresholdText);

        Product product(
            sku,
            name,
            category,
            quantity,
            location,
            threshold
        );

        addProduct(product);
    }

    file.close();
}

void Inventory::saveToFile(string filename) const
{
    ofstream file(filename);

    if (!file.is_open())
    {
        cout << "Could not save inventory file." << endl;
        return;
    }

    for (const auto& pair : products)
    {
        const Product& product = pair.second;

        file << product.sku
             << "|"
             << product.name
             << "|"
             << product.category
             << "|"
             << product.quantity
             << "|"
             << product.location
             << "|"
             << product.reorderThreshold
             << endl;
    }

    file.close();
}

bool Inventory::addProduct(Product product)
{
    if (products.find(product.sku) != products.end())
    {
        cout << "SKU already exists: "
             << product.sku
             << endl;

        return false;
    }

    products[product.sku] = product;

    return true;
}

bool Inventory::isAvailable(
    string sku,
    int quantity
) const
{
    auto it = products.find(sku);

    if (it == products.end())
        return false;

    return it->second.quantity >= quantity;
}

bool Inventory::deductStock(
    string sku,
    int quantity
)
{
    auto it = products.find(sku);

    if (it == products.end())
        return false;

    if (it->second.quantity < quantity)
        return false;

    it->second.quantity -= quantity;

    return true;
}

void Inventory::addStock(
    string sku,
    int quantity
)
{
    auto it = products.find(sku);

    if (it != products.end())
    {
        it->second.quantity += quantity;
    }
}

Product* Inventory::getProduct(string sku)
{
    auto it = products.find(sku);

    if (it == products.end())
        return nullptr;

    return &it->second;
}

void Inventory::searchProduct(string sku) const
{
    auto it = products.find(sku);

    if (it == products.end())
    {
        cout << "\nProduct not found." << endl;
        return;
    }

    const Product& product = it->second;

    cout << "\n========== PRODUCT ==========" << endl;

    cout << "SKU               : "
         << product.sku
         << endl;

    cout << "Name              : "
         << product.name
         << endl;

    cout << "Category          : "
         << product.category
         << endl;

    cout << "Quantity          : "
         << product.quantity
         << endl;

    cout << "Warehouse Location: "
         << product.location
         << endl;

    cout << "Reorder Threshold : "
         << product.reorderThreshold
         << endl;

    cout << "=============================" << endl;
}

void Inventory::searchProducts(string keyword) const
{
    string searchKeyword = keyword;

    // Convert search keyword to lowercase
    transform(
        searchKeyword.begin(),
        searchKeyword.end(),
        searchKeyword.begin(),
        [](unsigned char c)
        {
            return static_cast<char>(
                tolower(c)
            );
        }
    );

    bool found = false;

    cout << "\n========== SEARCH RESULTS ==========\n";

    for (const auto& pair : products)
    {
        const Product& product = pair.second;

        string name = product.name;
        string category = product.category;

        // Convert name to lowercase
        transform(
            name.begin(),
            name.end(),
            name.begin(),
            [](unsigned char c)
            {
                return static_cast<char>(
                    tolower(c)
                );
            }
        );

        // Convert category to lowercase
        transform(
            category.begin(),
            category.end(),
            category.begin(),
            [](unsigned char c)
            {
                return static_cast<char>(
                    tolower(c)
                );
            }
        );

        if (name.find(searchKeyword) != string::npos ||
            category.find(searchKeyword) != string::npos)
        {
            cout << "\nSKU       : "
                 << product.sku
                 << endl;

            cout << "Name      : "
                 << product.name
                 << endl;

            cout << "Category  : "
                 << product.category
                 << endl;

            cout << "Quantity  : "
                 << product.quantity
                 << endl;

            cout << "Location  : "
                 << product.location
                 << endl;

            cout << "-----------------------------\n";

            found = true;
        }
    }

    if (!found)
    {
        cout << "No products found for: "
             << keyword
             << endl;
    }

    cout << "=====================================\n";
}

void Inventory::displayInventory() const
{
    cout << "\n========== INVENTORY ==========" << endl;

    for (const auto& pair : products)
    {
        const Product& product = pair.second;

        cout << "SKU: "
             << product.sku
             << " | Name: "
             << product.name
             << " | Quantity: "
             << product.quantity
             << " | Location: "
             << product.location
             << endl;
    }

    cout << "===============================" << endl;
}

void Inventory::checkLowStock() const
{
    cout << "\n========== LOW STOCK ==========" << endl;

    bool found = false;

    for (const auto& pair : products)
    {
        const Product& product = pair.second;

        if (product.quantity <=
            product.reorderThreshold)
        {
            cout << product.sku
                 << " - "
                 << product.name
                 << " | Stock: "
                 << product.quantity
                 << endl;

            found = true;
        }
    }

    if (!found)
    {
        cout << "No low-stock products." << endl;
    }

    cout << "===============================" << endl;
}