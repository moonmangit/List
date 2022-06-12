#include <Arduino.h>
#include <List.h>

void setup()
{

    { // sorting/finding/each
        list<int> intlist;
        intlist.insertBack(new int(3));
        intlist.insertBack(new int(1));
        intlist.insertBack(new int(6));
        intlist.insertBack(new int(4));

        intlist.sort(sortexpr(int, el1, el2) {
            // how to compare two things
            if (el1 > el2)
                return 1;
            else if (el1 < el2)
                return -1;
            else
                return 0;
        });

        int indexOf6 = intlist.find(findexpr(int, 6, e1, e2) {
            // how to check if two things are equal
            return e1 == e2;
        });

        intlist.each(eachexpr(int, el, i) {
            // how to do with each element
            el = el * i;
            Serial.print("\n[");
            Serial.print(i);
            Serial.print("] -> ");
            Serial.print(el);
        });
    }
}

void loop() {}