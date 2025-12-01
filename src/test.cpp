// The following content was copied from the canonical root test.cpp
#include "SmartPtr.h"
#include "test.h"
#include "Order.h"
#include "BST.h"
#include "LinkedList.h"
#include "HashTable.h"
#include "OrderSystem.h"
#include <iostream>

using namespace std;

// Replace `TestClass` with the following:
class TestClass; // Forward declaration needed.
class TestClass {
    public:
        SmartPtr<TestClass> child{};
        TestClass() { std::cout << "TestClass constructor" << std::endl; }
        ~TestClass() { std::cout << "TestClass destructor" << std::endl; }
        TestClass(const TestClass& tc) { std::cout << "TestClass copy constructor" << std::endl; }
};

vector<SmartPtr<Order>> getOrders() {
    vector<SmartPtr<Order>> orders;
    orders.push_back(SmartPtr<Order>{new Order(7, 70.2, 5, Soup::CLEAR_SOUP, vector<string>({"egg", "tomato"}), true)});
    orders.push_back(SmartPtr<Order>{new Order(1, 10.3, 3, Soup::HOT_AND_SOUR_SOUP, vector<string>({"beef", "tomato"}), false)});
    orders.push_back(SmartPtr<Order>{new Order(2, 20.0, 4, Soup::HOT_AND_NUMBING_SOUP, vector<string>({"beef", "tomato"}), true)});
    orders.push_back(SmartPtr<Order>{new Order(3, 30.4, 5, Soup::PEPPER_AND_SPICY_SOUP, vector<string>({"beef", "egg"}), false)});
    orders.push_back(SmartPtr<Order>{new Order(10, 100.5, 5, Soup::VEGGIE_SOUP, vector<string>({"egg", "pork"}), true)});
    orders.push_back(SmartPtr<Order>{new Order(4, 40.7, 5, Soup::SHASHA_SOUP, vector<string>({"beef", "tomato"}), false)});
    orders.push_back(SmartPtr<Order>{new Order(6, 60.1, 5, Soup::TOMATO_SOUP, vector<string>({"pork", "tomato"}), true)});
    orders.push_back(SmartPtr<Order>{new Order(8, 80.3, 5, Soup::HOT_AND_SOUR_SOUP, vector<string>({"lettuce", "tomato"}), false)});
    orders.push_back(SmartPtr<Order>{new Order(9, 90.4, 5, Soup::HOT_AND_NUMBING_SOUP, vector<string>({"chicken", "pork liver"}), true)});
    orders.push_back(SmartPtr<Order>{new Order(11, 100.5, 5, Soup::PEPPER_AND_SPICY_SOUP, vector<string>({"beef", "tomato"}), false)});
    orders.push_back(SmartPtr<Order>{new Order(12, 100.5, 5, Soup::SHASHA_SOUP, vector<string>({"beef", "tomato"}), true)});
    orders.push_back(SmartPtr<Order>{new Order(13, 100.5, 5, Soup::CLEAR_SOUP, vector<string>({"beef", "tomato"}), false)});
    orders.push_back(SmartPtr<Order>{new Order(5, 50.0, 5, Soup::VEGGIE_SOUP, vector<string>({"beef", "tomato"}), true)});
    orders.push_back(SmartPtr<Order>{new Order(104, 100.5, 5, Soup::HOT_AND_SOUR_SOUP, vector<string>({"beef", "tomato"}), false)});
    orders.push_back(SmartPtr<Order>{new Order(1000000, 100.5, 5, Soup::HOT_AND_SOUR_SOUP, vector<string>({"beef", "tomato"}), false)});
    return orders;
}

ostream& operator<<(ostream& os, const TestClass& tz) {
    os << "TestClass";
    return os;
}

void run_test_1() {
        std::cout << "Test 1: SmartPointer: Constructor & Destructor" << std::endl;
        // Test constructors
        SmartPtr<int> sp1;
        sp1.printDetails();

        SmartPtr<int> sp2(new int{5});
        sp2.printDetails();

        int x = 10;
        SmartPtr<int> sp3(x);
        sp3.printDetails();

        SmartPtr<int> sp4(sp2);
        sp4.printDetails();
}

void run_test_2() {
        std::cout << "Test 2: SmartPointer: Assignment Operator" << std::endl;
        // Test assignment operator
        SmartPtr<int> sp1;
        SmartPtr<int> sp2(new int{5});
        SmartPtr<int> sp3(new int{10});
        sp1 = sp2;
        std::cout <<"sp1: ";
        sp1.printDetails();
        std::cout << "sp2: ";
        sp2.printDetails();
        std::cout <<"sp3: ";
        sp3.printDetails();
        sp1 = sp3;
        std::cout <<"sp1: ";
        sp1.printDetails();
        std::cout << "sp2: ";
        sp2.printDetails();
        std::cout <<"sp3: ";
        sp3.printDetails();

        SmartPtr<int> sp4{new int{}};
        sp4 = sp4;
        std::cout << "sp4: ";
        sp4.printDetails();
        SmartPtr<int> sp5{};
        sp5 = sp5;
        std::cout << "sp5: ";
        sp5.printDetails();
}

void run_test_3() {
    std::cout << "Test 3: SmartPointer: Dereference Operator" << std::endl;
    // Test dereference operator
    SmartPtr<int> sp1;
    SmartPtr<int> sp2(new int{5});
    SmartPtr<int> sp3(new int{10});
    sp1 = sp2;
    std::cout <<"sp1 dereference: "<< *sp1 << std::endl;
    std::cout <<"sp2 dereference: "<< *sp2 << std::endl;
    std::cout <<"sp3 dereference: "<< *sp3 << std::endl;
}

void run_test_4() {
    // Test arrow operator
    std::cout << "Test 4: SmartPointer: Arrow Operator" << std::endl;
    SmartPtr<std::string> sp4(new std::string{"Hello"});
    std::cout <<"sp4 arrow: "<< sp4->size() << std::endl;
}

void run_test_5() {
    std::cout << "Test 5: SmartPointer: Comparison Opearators" << std::endl;
    SmartPtr<int> sp1;
    SmartPtr<int> sp2(new int{5});
    SmartPtr<int> sp3(new int{10});
    sp1 = sp2;
    SmartPtr<std::string> sp4(new std::string{"Hello"});
    // Test comparison operators
    std::cout << "sp1 == sp2: " << (sp1 == sp2) << std::endl;
    std::cout << "sp1 == sp3: " << (sp1 == sp3) << std::endl;
    std::cout << "sp1 != sp2: " << (sp1 != sp2) << std::endl;
    std::cout << "sp1 != sp3: " << (sp1 != sp3) << std::endl;

    SmartPtr<int> sp5{}, sp6{};
    std::cout << "sp5 == sp6: " << (sp5 == sp6) << std::endl;
    std::cout << "sp1 == sp5: " << (sp1 == sp5) << std::endl;
    std::cout << "sp5 != sp6: " << (sp5 != sp6) << std::endl;
    std::cout << "sp1 != sp5: " << (sp1 != sp5) << std::endl;
}

void run_test_6() {
    std::cout << "Test 6: Operator Bool & isNull" << std::endl;
    SmartPtr<int> sp1;
    SmartPtr<int> sp2(new int{5});
    SmartPtr<int> sp3(new int{10});
    // Test bool operator
    std::cout << "sp1 bool: " << static_cast<bool>(sp1) << std::endl;
    std::cout << "sp2 bool: " << static_cast<bool>(sp2) << std::endl;
    std::cout << "sp3 bool: " << static_cast<bool>(sp3) << std::endl;
    // Test isNull method
    std::cout << "sp1 isNull: " << sp1.isNull() << std::endl;
    std::cout << "sp2 isNull: " << sp2.isNull() << std::endl;
    std::cout << "sp3 isNull: " << sp3.isNull() << std::endl;
}

void run_test_7() {
    // Test nullptr related methods
    std::cout << "Test 7: nullptr survival test" << std::endl;
    SmartPtr<int> sp1;
    SmartPtr<int> sp2(new int{5});
    std::cout << "Assign sp2 to sp1" << std::endl;
    sp1 = sp2;
    std::cout << "sp1: ";
    sp1.printDetails();
    std::cout << "sp2: ";
    sp2.printDetails();

    std::cout << "Unset sp1" << std::endl;
    sp1.unset();

    std::cout << "sp1: ";
    sp1.printDetails();
    std::cout << "sp2: ";
    sp2.printDetails();
    std::cout << "Constructor sp3 explicitly using nullptr" << std::endl;
    SmartPtr<int> sp3 {nullptr};
    std::cout << "sp3: ";
    sp3.printDetails();

    std::cout << "Assign sp2 to sp3" << std::endl;
    sp3 = sp2;
    std::cout << "sp2: ";
    sp2.printDetails();
    std::cout << "sp3: ";
    sp3.printDetails();

    std::cout << "Unset sp3" << std::endl;
    sp3.unset();
    std::cout << "sp3: ";
    sp3.printDetails();

    std::cout << "Constructor sp4 using default constructor, and copy sp4 to sp5" << std::endl;
    SmartPtr<int> sp4;
    SmartPtr<int> sp5 {sp4};

    std::cout << "sp4: ";
    sp4.printDetails();
    std::cout << "sp5: ";
    sp5.printDetails();

    std::cout << "Set sp4 to sp2 using set()" << std::endl;
    sp4.set(*sp2);
    std::cout << "sp4: ";
    sp4.printDetails();
    std::cout << "sp5: ";
    sp5.printDetails();

    std::cout << "Unset sp4" << std::endl;
    sp4.unset();
    std::cout << "sp4: ";
    sp4.printDetails();
    std::cout << "sp2: ";
    sp2.printDetails();
}

void run_test_8() {
    // Test destructor
    std::cout << "Test 8: See whether the constructor / desctuctor time is correct" << std::endl;
    SmartPtr<TestClass> sp1(new TestClass());
    std::cout << "sp1: ";
    sp1.printDetails();
    SmartPtr<TestClass> sp2(sp1);
    std::cout << "sp2: ";
    sp2.printDetails();
    SmartPtr<TestClass> sp3;
    sp3 = sp2;
    std::cout << "sp3: ";
    sp3.printDetails();
    sp1.unset();
    std::cout << "sp1: ";
    sp1.printDetails();
    std::cout << "sp2: ";
    sp2.printDetails();
    std::cout << "sp3: ";
    sp3.printDetails();
    sp2.unset();
    std::cout << "sp1: ";
    sp1.printDetails();
    std::cout << "sp2: ";
    sp2.printDetails();
    std::cout << "sp3: ";
    sp3.printDetails();
    sp3.unset();
    std::cout << "sp1: ";
    sp1.printDetails();
    std::cout << "sp2: ";
    sp2.printDetails();
    std::cout << "sp3: ";
    sp3.printDetails();

    SmartPtr<TestClass> sp4{new TestClass{}};
    std::cout << "sp4: ";
    sp4.printDetails();
    sp4 = sp4;
    std::cout << "sp4: ";
    sp4.printDetails();

    SmartPtr<TestClass> sp5{};
    std::cout << "sp5: ";
    sp5.printDetails();
    sp5 = sp5;
    std::cout << "sp5: ";
    sp5.printDetails();

    SmartPtr<TestClass> sp6{new TestClass{}};
    std::cout << "sp6: ";
    sp6.printDetails();
    sp6.set(*sp6);
    std::cout << "sp6: ";
    sp6.printDetails();
}

// Replace `run_test_9` with the following:
void run_test_9(){
    std::cout << "Test 9: Test Various Constructors / set / unset and its correctness" << std::endl;
    SmartPtr<TestClass> sp1(new TestClass());
    sp1.unset();
    SmartPtr<TestClass> sp2(new TestClass());
    SmartPtr<TestClass> sp3(sp2);
    auto t = TestClass();
    SmartPtr<TestClass> sp4 {t};
    sp4.set(t);
    sp4.unset();
    sp2.unset();
    sp2.set(t);
    sp3.unset();

    // Special case for `operator=`
    SmartPtr<TestClass> sp5{new TestClass{}};
    sp5->child = SmartPtr<TestClass>{new TestClass{}};
    sp5 = sp5->child;

    // Special case for `set`
    SmartPtr<TestClass> sp6{new TestClass{}};
    sp6->child = SmartPtr<TestClass>{new TestClass{}};
    sp6.set(*(sp6->child));
}

void run_test_10() {
    std::cout << "Test 10: LinkedList: operator[]" << std::endl;
    LinkedList ll;
    auto vec = getOrders();
    for (auto order : vec) {
        ll.add(order);
    }
    for (int i = 0; i < ll.length(); ++i) {
        std::cout << ll[i]->getOid() << " " << ll[i]->getPrice() << std::endl;
    }
}

void run_test_11() {
    std::cout << "Test 11: BST: Add, PrintTree" << std::endl;
    auto vec = getOrders();
    BST<float> bst;
    for (auto order : vec) {
        bst.add(order->getPrice(), order);
    }
    bst.printTree(0);
}

void run_test_12() {
    std::cout << "Test 12: BST: Size, Operator[]" << std::endl;
    auto vec = getOrders();
    BST<float> bst;
    for (auto order : vec) {
        bst.add(order->getPrice(), order);
    }
    int size = bst.size();
    std::cout << "Size: " << size << std::endl;
    for (int i = 0; i < size; ++i) {
        auto pair = bst[i];
        std::cout << "(" << pair.first <<", " << pair.second << ")" << std::endl;
    }
}

void run_test_13() {
    std::cout << "Test 13: BST: RangeSelect" << std::endl;
    auto vec = getOrders();
    BST<float> bst;
    for (auto order : vec) {
        bst.add(order->getPrice(), order);
    }
    auto vec2 = bst.rangeSelect(5.0, 50.0);
    std::cout << "RangeSelect from 5.0 to 50.0" << std::endl;
    std::cout << "Result: " << std::endl;
    for (auto order : vec2) {
        std::cout << order->getOid() << " " << order->getPrice() << std::endl;
    }
}

void run_test_14() {
    std::cout << "Test 14: BST: Remove, Contain" << std::endl;
    auto vec = getOrders();
    BST<float> bst;
    for (auto order : vec) {
        bst.add(order->getPrice(), order);
    }
    std::cout << "Before removing the first element" << std::endl;
    bst.printTree(0);
    std::cout << boolalpha << bst.contains(vec[0]->getPrice(), vec[0]) << std::endl;
    bst.remove(vec[0]->getPrice(), vec[0]);
    std::cout << "After removing the first element" << std::endl;
    bst.printTree(0);
    std::cout << boolalpha << bst.contains(vec[0]->getPrice(), vec[0]) << std::endl;
}

void run_test_15() {
    std::cout << "Test 15: BST: Find, FindMin" << std::endl;
    auto vec = getOrders();
    BST<float> bst;
    for (auto order : vec) {
        bst.add(order->getPrice(), order);
    }
    auto bst2 = bst.find(60.1);
    std::cout << "Find 60.1" << std::endl;
    if (bst2 != nullptr) {
        bst2->printTree(0);
    } else {
        std::cout << "Not found" << std::endl;
    }
    auto bst3 = bst.findMin();
    std::cout << "FindMin" << std::endl;
    if (bst3 != nullptr) {
        bst3->printTree(0);
    } else {
        std::cout << "Not found" << std::endl;
    }
}

void run_test_16() {
    std::cout << "Test 16: HashTable: Add, PrintTable" << std::endl;
    auto vec = getOrders();
    HashTable ht {100, OrderSystem::hashFunc};
    for (auto order : vec) {
        ht.add(order);
    }
    ht.printTable();
}

void run_test_17() {
    std::cout << "Test 17: HashTable: Remove, Contains" << std::endl;
    auto vec = getOrders();
    HashTable ht {100, OrderSystem::hashFunc};
    for (auto order : vec) {
        ht.add(order);
    }
    std::cout << "Before removing the first element" << std::endl;
    ht.printTable();
    std::cout << boolalpha << ht.contains(vec[0]->getOid()) << std::endl;
    ht.remove(vec[0]);
    std::cout << "After removing the first element" << std::endl;
    ht.printTable();
    std::cout << boolalpha << ht.contains(vec[0]->getOid()) << std::endl;
}

void run_test_18() {
    std::cout << "Test 18: HashTable: Operator[]" << std::endl;
    auto vec = getOrders();
    HashTable ht {100, OrderSystem::hashFunc};
    for (auto order : vec) {
        ht.add(order);
    }
    for (auto order : vec) {
        std::cout << ht[order->getOid()]->getOid() << " " << ht[order->getOid()]->getPrice() << std::endl;
    }
}

void run_test_19() {
    std::cout << "Test 19: HashTable: Copy Constructor" << std::endl;
    auto vec = getOrders();
    HashTable ht {100, OrderSystem::hashFunc};
    for (auto order : vec) {
        ht.add(order);
    }
    HashTable ht2 {ht};
    ht2.printTable();
}

void run_test_20() {
    std::cout << "Test 20: OrderSystem: Constructor / Desctruvtor" << std::endl;
    OrderSystem os;
    os.printOrders();
}

void run_test_21() {
    std::cout << "Test 21: OrderSystem: Basic Operations" << std::endl;
    auto vec = getOrders();
    OrderSystem os {vec};
    os.printOrders();

    os.removeOrder(vec[0]);
    std::cout << "Is the first order still in the system? " << boolalpha << os.containsOrder(vec[0]->getOid()) << std::endl;
    os.printOrders();
    os.addOrder(vec[0]);
    std::cout << "Is the first order back in the system? " << boolalpha <<  os.containsOrder(vec[0]->getOid()) << std::endl;
}

void run_test_22() {
    std::cout << "Test 22: OrderSystem: getNumberMixianStat" << std::endl;
    auto vec = getOrders();
    OrderSystem os {vec};
    auto num = os.getNumberMixianStat<Soup>(Soup::HOT_AND_SOUR_SOUP, Soup::PEPPER_AND_SPICY_SOUP, os.getBSTSoup());
    std::cout << "Number of mixian from HOT_AND_SOUR_SOUP to PEPPER_AND_SPICY_SOUP: " << num << std::endl;
}

void run_test_23() {
    std::cout << "Test 23: OrderSystem: getPriceSumStat" << std::endl;
    auto vec = getOrders();
    OrderSystem os {vec};

    std::vector<SmartPtr<Order>> temp = os.getBSTSpiciness().rangeSelect(3, 5);
    cout << temp.size() << endl;
    cout << temp[0]->getPrice() << endl;
    auto sum = os.getPriceSumStat<int>(3, 5, os.getBSTSpiciness());
    std::cout << "Total revenue from 10 to 50: " << sum << std::endl;
}

void run_test_24() {
    std::cout << "Test 24: OrderSystem: Negative Test" << std::endl;
    auto vec = getOrders();
    OrderSystem os {vec};
    os.printOrders();
    auto sum = os.getPriceSumStat<int>(-10, -9, os.getBSTSpiciness());
    std::cout << "Total revenue from -10 to -9: " << sum << std::endl;
}

// ! End of given test cases

void TestSuite::run(int test) {
    switch (test) {
        case 1:
            run_test_1();
            break;
        case 2:
            run_test_2();
            break;
        case 3:
            run_test_3();
            break;
        case 4:
            run_test_4();
            break;
        case 5:
            run_test_5();
            break;
        case 6:
            run_test_6();
            break;
        case 7:
            run_test_7();
            break;
        case 8:
            run_test_8();
            break;
        case 9:
            run_test_9();
            break;
        case 10:
            run_test_10();
            break;
        case 11:
            run_test_11();
            break;
        case 12:
            run_test_12();
            break;
        case 13:
            run_test_13();
            break;
        case 14:
            run_test_14();
            break;
        case 15:
            run_test_15();
            break;
        case 16:
            run_test_16();
            break;
        case 17:
            run_test_17();
            break;
        case 18:
            run_test_18();
            break;
        case 19:
            run_test_19();
            break;
        case 20:
            run_test_20();
            break;
        case 21:
            run_test_21();
            break;
        case 22:
            run_test_22();
            break;
        case 23:    
            run_test_23();
            break;
        case 24:
            run_test_24();
            break;
        default:
            std::cout << "No such test case." << std::endl;
            break;
    }
}

