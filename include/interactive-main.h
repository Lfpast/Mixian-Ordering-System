#ifndef __INTERACTIVE_MAIN_H__
#define __INTERACTIVE_MAIN_H__

#include <string>
#include <vector>
#include "SmartPtr.h"
#include "Order.h"
#include "OrderSystem.h"

class InteractiveMain {
    public:
        InteractiveMain(std::string path);
        void run();
    private:
        std::string path;
        std::vector<SmartPtr<Order>> orders;
};

void printAction();

#endif // __INTERACTIVE_MAIN_H__
