#include <Arduino.h>
#include <List.h>

void insertion()
{
    // on create insertion
    char charArr[] = "hello world";
    list<char> charlist(charArr, arrsize(charArr));

    // normal insertion
    list<int> intlist;
    int *trackData = intlist.insertBack(new int(1)); // use can accept address of data for tracking data or another use.
    intlist.insertFront(new int(2));
    intlist.insertAt(new int(3), 1);

    // multiple insertion
    int arr[] = {1, 2, 3, 4, 5};
    intlist.fromArray(arr, arrsize(arr)); // intlist = 2 3 1 1 2 3 4 5
    // !fromArray will create copy inside list arr[] will not take any effect
}