#include <Arduino.h>
#include <List.h>

void helper()
{
    list<int> intlist;

    intlist.setEnd(true, true); // specify how to free memory when out of scope of

    // export to static array.
    int intArr[intlist.size()];
    intlist.toStaticArray(intArr);

    // export to dynami array.
    int *intArr = intlist.toDynamicArray(); // need to free after use.
    delete[] intArr;                        // after use.

    // build-in iteration
    intlist.each(eachexpr(int, el, i) {
        // el(you can name it) : are reference of data
        // i(you can name it) : index of data
        el += i;
        Serial.println(el);
    });

    // build-in finding
    int findingResult = intlist.find(findexpr(int, 10, el1, el2) {
        return el1 == el2;
    });

    // build-in sorting
    intlist.sort(sortexpr(int, el1, el2) {
        if (el1 > el2)
            return 1; // return more than 0
        else if (el1 < el2)
            return -1; // return less than 0
        else
            return 0; // return 0
        // or just, 'return el2-el1' for ascending
    });
}