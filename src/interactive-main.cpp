#include "Order.h"
#include "OrderSystem.h"
#include "SmartPtr.h"
#include "BST.h"
#include "HashTable.h"
#include "interactive-main.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

vector<SmartPtr<Order>> parseOrders(string path) {
    vector<SmartPtr<Order>> orders;
    ifstream file(path);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        // The file is in the format of:
        // Output format: oid,price,spicyLevel,soup,ingredient_size,ingredients,takeaway
        // Example: 1,10.0,3,Tomato Soup,3,carrot,beef,onion,1
        int oid, spicyLevel, ingredient_size;
        float price;
        string soup_str;
        vector<string> ingredients;
        bool takeaway;
        char comma;
        // ss >> oid >> comma >> price >> comma >> spicyLevel >> comma >> soup_str >> comma >> ingredient_size; // original
        // modified
        ss >> oid >> comma >> price >> comma >> spicyLevel >> comma;
        while(getline(ss, soup_str, ',')) {
            break;
        }
        ss >> comma >> ingredient_size;
        for (int i = 0; i < ingredient_size; i++) {
            string ingredient;
            ss >> comma >> ingredient;
            ingredients.push_back(ingredient);
        }
        ss >> comma >> takeaway;
        Soup soup = Soup::fromString(soup_str);
        SmartPtr<Order> order {new Order(oid, price, spicyLevel, soup, ingredients, takeaway)};
        orders.push_back(order);
    }
    return orders;
}


InteractiveMain::InteractiveMain(string path) : path(path), orders(parseOrders(path)) {}

void printAction() {
    cout << "Please select an action:" << endl;
    cout << "1. Add an order to the order management system" << endl;
    cout << "2. Remove an order from the order management system" << endl;
    cout << "3. Check if an order is in the order management system" << endl;
    cout << "4. Get an order from the order management system" << endl;
    cout << "5. Print the data structures in the order management system" << endl;
    cout << "6. Trigger getNumberMixianStat function (Using spicyLevel tree)" << endl;
    cout << "7. Trigger getNumberMixianStat function (Using soup tree)" << endl;
    cout << "8. Trigger getPriceSumStat function (Using spicyLevel tree)" << endl;
    cout << "9. Trigger getPriceSumStat function (Using soup tree)" << endl;
    cout << "10. Exit" << endl;
}

void InteractiveMain::run() {
    cout << "Welcome to TamGorDIiDi Mixian Order Management System!" << endl;
    cout << "Importing data from " << this->path << "..." << endl;
    OrderSystem os(orders);
    cout << "Data imported successfully!" << endl;
    cout << "There are " << orders.size() << " orders in the system." << endl;
    int choice;
    while (true) {
        printAction();
        cin >> choice;
        SmartPtr<Order> order {};
        string start_soup;
        string end_soup;
        string start_soup_price;
        string end_soup_price;
        switch (choice) {
            case 1:
                cout << "Enter the oid you want to add to the system: ";
                cout << "Note: You can only add an order which exists in the file." << endl;
                int oid;
                cin >> oid;
                // Find the order
                for (auto o : orders) {
                    if (o->getOid() == oid) {
                        order = o;
                        break;
                    }
                }
                if (order) {
                    os.addOrder(order);
                    cout << "Order added successfully!" << endl;
                } else {
                    cout << "Order not found in the file." << endl;
                }
                break;
            case 2:
                cout << "Enter the oid you want to remove from the system: ";
                int oid_remove;
                cin >> oid_remove;
                if (os.containsOrder(oid_remove)) {
                    os.removeOrder(os.getOrder(oid_remove));
                    cout << "Order removed successfully!" << endl;
                } else {
                    cout << "Order not found in the system." << endl;
                }
                break;
            case 3:
                cout << "Enter the oid you want to check if it is in the system: ";
                int oid_check;
                cin >> oid_check;
                if (os.containsOrder(oid_check)) {
                    cout << "Order found in the system." << endl;
                } else {
                    cout << "Order not found in the system." << endl;
                }
                break;
            case 4:
                cout << "Enter the oid you want to get from the system: ";
                int oid_get;
                cin >> oid_get;
                if (os.containsOrder(oid_get)) {
                    cout << "Order found in the system." << endl;
                    cout << "Order details: " << endl;
                    cout << os.getOrder(oid_get) << endl;
                } else {
                    cout << "Order not found in the system." << endl;
                }
                break;
            case 5:
                cout << "Printing the data structures in the order management system..." << endl;
                os.printOrders();
                break;
            case 6:
                cout << "Enter the spicyLevel range you want to query: " << endl;
                cout << "Enter the start of the range: " << endl;
                int start, end;
                cin >> start;
                cout << "Enter the end of the range: " << endl;
                cin >> end;
                cout << "Number of mixian included in that range: " << os.getNumberMixianStat(start, end, os.getBSTSpiciness()) << endl;
                break;
            case 7:
                cout << "Enter the soup range you want to query: " << endl;
                cout << "Enter the start of the range: (Using enum value string)" << endl;
                
                cin >> start_soup;
                cout << "Enter the end of the range: (Using enum value string)" << endl;
                
                cin >> end_soup;
                cout << "Number of mixian included in that range: " << os.getNumberMixianStat(Soup {Soup::fromString(start_soup)}, Soup {Soup::fromString(end_soup) }, os.getBSTSoup()) << endl;
                break;
            case 8:
                cout << "Enter the spicyLevel range you want to query: " << endl;
                cout << "Enter the start of the range: " << endl;
                int start_price, end_price;
                cin >> start_price;
                cout << "Enter the end of the range: " << endl;
                cin >> end_price;
                cout << "Total revenue of mixian sold in that range: " << os.getPriceSumStat(start_price, end_price, os.getBSTSpiciness()) << endl;
                break;
            case 9:
                cout << "Enter the soup range you want to query: " << endl;
                cout << "Enter the start of the range: (Using enum value string)" << endl;
                
                cin >> start_soup_price;
                cout << "Enter the end of the range: (Using enum value string)" << endl;
                
                cin >> end_soup_price;
                cout << "Total revenue of mixian sold in that range: " << os.getPriceSumStat(Soup {Soup::fromString(start_soup_price)}, Soup {Soup::fromString(end_soup_price) }, os.getBSTSoup()) << endl;
                break;
            case 10:
                cout << "Exiting the system..." << endl;
                return;
        }
    }

}
