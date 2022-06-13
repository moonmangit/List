#include <Arduino.h>
#include <List.h>

void removing()
{
    list<int> intlist;
    // remove
    intlist.remove(0);
    intlist.remove(0, true);  // same as abov
    intlist.remove(1, false); // data at index 1 will stayed after remove but node will be destroy, plase use carefully.
    // remove all
    intlist.clearList(true);  // destroy all datas and nodes
    intlist.clearList(false); // destroy only nodes.
}