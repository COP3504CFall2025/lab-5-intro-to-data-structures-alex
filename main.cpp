// #ifdef MAIN

#include "ABDQ.hpp"
#include "ABQ.hpp"
#include "ABS.hpp"
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include "LLDQ.hpp"
#include "LLQ.hpp"
#include "LLS.hpp"
#include <iostream>

/*
    - LEAVE THE IFDEF GUARDS TO KEEP YOUR MAIN WITHOUT CONFLICTING WITH GRADESCOPE!
    - Test your code in this main and run locally with the RunMain configuration in CLion, or
    through your own command line compilation. Make sure to add flag "-DMAIN" to your compilation so this
    main function can compile.

*/

int main() {
    LinkedList<int> list;

    std::cout << "Adding 10, 20, 30 to head...\n";
    list.addHead(10);
    list.addHead(20);
    list.addHead(30);
    list.printForward();   // Expected: 30 20 10
    list.printReverse();   // Expected: 10 20 30

    std::cout << "\nAdding 40, 50 to tail...\n";
    list.addTail(40);
    list.addTail(50);
    list.printForward();   // Expected: 30 20 10 40 50
    list.printReverse();   // Expected: 50 40 10 20 30

    std::cout << "\nRemoving head...\n";
    list.removeHead();
    list.printForward();   // Expected: 20 10 40 50

    std::cout << "\nRemoving tail...\n";
    list.removeTail();
    list.printForward();   // Expected: 20 10 40

    std::cout << "\nCopying list to list2...\n";
    LinkedList<int> list2 = list; // copy constructor
    list2.printForward();          // Expected: 20 10 40

    std::cout << "\nClearing original list...\n";
    list.Clear();
    list.printForward();   // Expected: (nothing)
    std::cout << "Original list count: " << list.getCount() << "\n"; // 0
    std::cout << "Copied list count: " << list2.getCount() << "\n";  // 3

    std::cout << "\nMove assigning list2 to list3...\n";
    LinkedList<int> list3;
    list3 = std::move(list2);   // move assignment
    list3.printForward();       // Expected: 20 10 40
    std::cout << "list2 count after move: " << list2.getCount() << "\n"; // 0

    return 0;
}


// #endif