#include <Arduino.h>
#include <List.h>

void setup()
{
    { // basic instance
        list<int> intlist;
        list<char> intlist;
        list<float> intlist;
        list<double> intlist;
        list<String> intlist;
    }

    { // array instance
        int arr[] = {0, 1, 2, 3, 4, 5, 6, 7};
        list<int> intlist(arr);
    }

    { // insertion
        list<int> intlist;
        intlist.insertBack(new int(99));

        list<char> charlist;
        charlist.insertFront(new char('c'));

        list<String> stringlist;
        stringlist.insertAt(new String("hello world"), 0);

        float floatArr[] = {1.1f, 1.2f, 1.3f, 1.4f};
        list<float> floatlist;
        floatlist.fromArray(floatArr, arrsize(floatArr));
    }

    { // accessing
        list<int> intlist;
        intlist.insertBack(new int(1));
        intlist.insertBack(new int(2));
        intlist.insertBack(new int(3));

        int x = intlist.get(0); // x = copy of 1
        int ax = intlist[0];    // same as above

        int &y = intlist.get(0); // y = 1
        int &ay = intlist[0];    // same as above
    }

    { // export
        list<int> intlist;
        intlist.insertBack(new int(1));
        intlist.insertBack(new int(2));
        intlist.insertBack(new int(3));
        intlist.insertBack(new int(4));

        // static
        int intArr[intlist.size()];
        intlist.toStaticArray(intArr);
        intArr[0] = intArr[1] + 1;

        // dynamic
        int *intDyArr = intlist.toDynamicArray();
        intDyArr[0] = intArr[1] + 1;
        delete[] intDyArr;
    }
}

void loop() {}