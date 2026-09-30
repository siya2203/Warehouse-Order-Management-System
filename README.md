# Warehouse Order Management System

A C++ console-based Warehouse Order Management System that demonstrates the practical use of data structures and algorithms for managing orders, inventory, product search, warehouse routes, picking, packing, and dispatch.

## Overview

The Warehouse Order Management System simulates the basic workflow of a warehouse:

1. Create an order
2. Validate products and quantities
3. Place the order in the appropriate queue
4. Allocate inventory
5. Generate a picking list
6. Pick and pack the order
7. Dispatch the order
8. Store order and inventory information
9. Generate reports

The project was developed as an academic C++ prototype to demonstrate the application of Data Structures and Algorithms in a warehouse environment.

## Features

- Standard order processing using FIFO Queue
- Urgent order processing using Priority Queue
- Packing history using Stack
- Inventory management using Hash Map
- Product search by SKU
- Product search by name or category
- Inventory availability checking
- Low-stock detection
- Inventory persistence using text files
- Order persistence using text files
- Warehouse route finding using Graphs
- BFS-based route finding
- Dijkstra's shortest path algorithm
- Order status tracking
- Order validation
- Duplicate order ID detection
- Picking list generation
- Packing and dispatch workflow
- Order and inventory reports

## Data Structures and Algorithms

| Data Structure / Algorithm | Application |
|---|---|
| Queue | Standard orders |
| Priority Queue | Urgent orders |
| Stack | Recent packing operations |
| Vector | Order items and stored orders |
| Hash Map | Fast SKU and order lookup |
| Graph | Warehouse layout and routes |
| BFS | Warehouse route traversal |
| Dijkstra | Weighted shortest path |

## Order Workflow

```text
Create Order
     |
     v
Validate Order
     |
     v
Check Inventory
     |
     v
Queue / Priority Queue
     |
     v
Allocate Inventory
     |
     v
Generate Picking List
     |
     v
Pick Items
     |
     v
Pack Order
     |
     v
Ready for Dispatch
     |
     v
Dispatch Order