#include <Arduino.h>
#include <List.h>

void setup()
{
    List<int> intList;
    intList.insertBack(new int(70));
    intList.insertBack(new int(50));
    intList.insertBack(new int(30));
    intList.insertBack(new int(20));
    intList.insertBack(new int(10));
    intList.insertBack(new int(40));
    intList.insertBack(new int(60));

    intList.get(0);                          // => return 70
    intList.get(6);                          // => return 60
    int x = intList.get(0) + intList.get(2); // x = 70+30 = 100

    int indexOf10 = intList.find(
        10, findfn(int, el1, el2) {
            return el1 == el2;
        }); //  indexOf10 = 4

    intList.each(eachfn(int, element, i) {
        element += 9;
    }); // each element will increase by 9

    intList.sort(
        sortfn(int, el1, el2) {
            if (el1 > el2)
                return morethan;
            else if (el1 < el2)
                return lessthan;
            else
                return equal;
        },
        true); // sort element ascending
}

void loop() {}