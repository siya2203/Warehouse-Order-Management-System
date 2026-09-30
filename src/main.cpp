// // // #include <iostream>
// // // using namespace std;

// // // int main()
// // // {
// // //     cout << "========================================" << endl;
// // //     cout << "   WAREHOUSE ORDER MANAGEMENT SYSTEM" << endl;
// // //     cout << "========================================" << endl;

// // //     cout << "\nSystem started successfully!" << endl;

// // //     return 0;
// // // }
// // #include <iostream>
// // #include "../include/Inventory.h"

// // using namespace std;

// // int main()
// // {
// //     cout << "========================================" << endl;
// //     cout << "   WAREHOUSE ORDER MANAGEMENT SYSTEM" << endl;
// //     cout << "========================================" << endl;

// //     Inventory inventory;

// //     inventory.loadFromFile("data/inventory.txt");

// //     inventory.displayInventory();

// //     inventory.searchProduct("P003");

// //     inventory.checkLowStock();

// //     return 0;
// // }

// #include <iostream>

// #include "../include/Graph.h"

// using namespace std;


// int main()
// {
//     cout << "========================================" << endl;
//     cout << "   WAREHOUSE ORDER MANAGEMENT SYSTEM" << endl;
//     cout << "========================================" << endl;


//     // Create warehouse with 8 locations
//     Graph warehouse(8);


//     /*
//         Warehouse locations:

//         0 = Receiving
//         1 = Zone A
//         2 = Zone B
//         3 = Zone C
//         4 = Picking Station
//         5 = Packing Station
//         6 = Dispatch
//         7 = Storage
//     */


//     warehouse.addEdge(0, 1, 2);

//     warehouse.addEdge(1, 2, 3);

//     warehouse.addEdge(2, 3, 2);

//     warehouse.addEdge(1, 4, 4);

//     warehouse.addEdge(2, 4, 2);

//     warehouse.addEdge(3, 5, 3);

//     warehouse.addEdge(4, 5, 2);

//     warehouse.addEdge(5, 6, 2);

//     warehouse.addEdge(2, 7, 4);


//     // Display warehouse graph
//     warehouse.displayGraph();


//     // BFS
//     cout << "\nBFS Route from Receiving to Dispatch:\n";

//     vector<int> bfsPath =
//         warehouse.bfs(0, 6);


//     for (int location : bfsPath)
//     {
//         cout << location << " ";
//     }


//     // Dijkstra
//     cout << "\n\nDijkstra Route from Receiving to Dispatch:\n";

//     vector<int> dijkstraPath =
//         warehouse.dijkstra(0, 6);


//     for (int location : dijkstraPath)
//     {
//         cout << location << " ";
//     }


//     cout << "\n";


//     return 0;
// }

#include <iostream>

#include "../include/Warehouse.h"

using namespace std;


int main()
{
    Warehouse warehouse;


    warehouse.loadInventory(
        "data/inventory.txt"
    );


    warehouse.run();


    return 0;
}