#include <Arduino.h>
#include <List.h>

void accessing()
{
    list<int> intlist;
    int copy = intlist.get(0);
    int &ref = intlist.get(0); // change will apply to data in list
    int copy_operator = intlist[0];
    int &ref_operator = intlist[0];
    listnode<int> copy_node = intlist.getNode(0);
    listnode<int> &ref_node = intlist.getNode(0);      // change will apply to node in list
    listnode<int> *addr_node = intlist.getNodeAddr(0); // dereference will apply to node int list
}