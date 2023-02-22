#include <iostream>
#include <utility>

#include "doubly_linked_list.h"

int main()
{
    using std::cout;
    using std::cin;
    using std::endl;

    // empty list
    DLL list;
    cout << "\nEmpty list's size: " << list.size() << endl;
    list.print(); // nothing to print

    // initializing list, push some elements
    DLL l(999);
    l.push(DLL::BACK, 3);
    l.push(DLL::BACK, 5);

    // checking assignment operator
    list = l;
    cout << "\nAssignment operator check, list size: "
         << list.size() << endl;
    list.print();

    //pushing elements in different ways
    list.push(DLL::BACK, 7);
    list.push(DLL::BACK, 9);
    list.push(DLL::BACK, 12);
    list.push(DLL::FRONT, 222);
    list.push(DLL::FRONT, 555);
    list.push(DLL::MID, 777);
    cout << "\nList, after multiple pushing, size: " << list.size() << endl;
    list.print();

    //checking move semantics
    DLL robber = std::move(list);
    cout << "\nList created by move semantics, its size: "
         << robber.size() << endl;
    robber.print();
    cout << "\nPrevios robbed list's size: " << list.size() << endl;
    list.print(); //won't print anything
    list = std::move(robber); //restoring list's content back

    //checking merge effect
    DLL add;
    add.push(DLL::BACK, 888);
    add.push(DLL::BACK, 444);
    add.push(DLL::BACK, 333);
    list.merge(add);
    cout << "\nList, after being merged with another list, size: "
         << list.size() << endl;
    list.print();

    //checking addition, combined with move semantics
    DLL sum = std::move(list + add);
    cout << "\nAddition operator, new list's size: "
         << sum.size() << endl;
    sum.print();

    //popping elements from list
    sum.pop(DLL::FRONT);
    sum.pop(DLL::FRONT);
    sum.pop(DLL::BACK);
    sum.pop(DLL::BACK);
    sum.pop(DLL::MID);
    sum.pop(DLL::MID);
    cout << "\nSum list, after multiple popping, size: "
         << sum.size() << endl;
    sum.print();

    //insertion to custom position
    sum.insert(0, 235);  //emulating front
    sum.insert(10, 238); //emulating back
    sum.insert(6, 82);   //emulating mid

    cout << "\nSum, list after multiple custom insertion, size: "
         << sum.size() << endl;
    sum.print();

    //removing from custom position
    sum.remove(0);  //won't work
    sum.remove(1);  //front
    sum.remove(14); //back
    sum.remove(5);  //mid
    sum.remove(3);
    sum.remove(10);
    cout << "\nSum, list after multiple custom removing, size: "
         << sum.size() << endl;
    sum.print();

    //reverse method
    sum.reverse();
    cout << "\nReversed sum, size: " << sum.size() << endl;
    sum.print();

    //testing slice method
    int p1 = 4;
    int p2 = 5;

    DLL sliced = sum.slice(p1, p2);
    cout << "\nNew white sliced list at pos " << p1 << " and " << p2
         << ", size: " << sliced.size() << endl;
    sliced.print();

    sliced = sum.slice(p1, p2, DLL::BLACKLIST);
    cout << "\nNew black sliced list at pos " << p1 << " and " << p2
         << ", size: " << sliced.size() << endl;
    sliced.print();

    //resize and refresh
    sum.resize(10);
    sum.refresh(8, 848);
    sum.refresh(9, 723);
    sum.refresh(10, 344);
    sum.refresh(1, 10);
    sum.refresh(20, 77);

    sum.refresh(6, 545); //mid
    cout << "\nResized and refreshed sum list, size: "
         << sum.size() << endl;
    sum.print();

    //sorting list
    sum.sort();
    cout << "\nSorted list, size : " << sum.size() << endl;
    sum.print();

    return 0;
}
