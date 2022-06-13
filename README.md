# List

Simple general linked list library that's easy to use and have built-in helper function for Arduino-Framework.

## Features

1. Built-in helper function with helper macros.
2. Multiple type of insertion/accessing/removing/export.
3. Auto garbage collector.

---

### 1. Instantiation
To instance list use `list<...type...>` to create empty list type can be anything
```cpp
list<int> intlist;
list<char> charlist;
list<String> stringlist;
```
Or you can put some option when create list
```cpp
int arr[] = {1, 2, 3, 4, 5};
// copy and insert each of arr[] to intlist 
list<int> intlist(arr, arrsize(arr))
```
---
### 2. Insertion
- use `.insertBack` to insert element at the end of list.
```cpp
intlist.insertBack(new int(100));
intlist.insertBack(new int(101));
```
- use `.insertFront` to insert element at the begining of list.
```cpp
intlist.insertFront(new int(100));
intlist.insertFront(new int(101));
```
- use `.insertAt` to insert element at specific position.
```cpp
intlist.insertAt(new int(100), 0); // insert to position 0
intlist.insertAt(new int(101), 1);
```
- use `.fromArray` to load elements from array to list.
- use `arrsize` built-in macro for get size of array.
```cpp
int arr[] = {1, 2, 3, 4};
intlist.fromArray(arr, arrsize(arr));
```
---
### 3. Accessing and Removing
data or node-list and access by multiple methods
- use `.get` or `[]` to access data element at specific position.
- use `&` before destination variable for directly reference to data element.
```cpp
int *addr = intlist.insert(new int(10));

// copy
int copy = intlist.get(0); // or intlist[0]
copy++; // *addr == 10

// reference
int &ref = intlist.get(0); // or intlist[0]
ref++; // *addr == 11
```
- use `.getNode` to access node element at specific position.
- use `.getNodeAddr` to address of node at specific position.
```cpp
listnode<int> node = intlist.getNode(0);
listnode<int> *nodeAddr = intlist.getNodeAddr(0);
```
- use `.remove` to remove specific index from list
```cpp
int *track = intlist.insertBack(new int(99));

// remove only node
intlist.remove(0); // remove node from list
int x = *track;// x = 99;

// remove node + data
intlist.remove(0, true) // remove node and data
int x = *track; // x != 99;
```
---
### 4. Exporting to Array
To export to array
- use `.toStaticArray` to copy data to passed static array, but list still the same.
- use `.toDynamicArray` to create and return dynamic array from list, need to manual free after use by using `delete[]`.
```cpp
// static
int arr[intlist.size()];
intlist.toStaticArray(arr);

// dynamic
int *arr = intlist.toDynamicArray();
delete[] arr; //after used

```
---
### 5. Sorting
Sorting will seamlessly create new sort list then destroy old one.
- use `.sort` with `sortexpr` built-in macro for assign sorting logic.
```cpp
intlist.sort(sortexpr(int, el1, el2){});
charlist.sort(sortexpr(char, charElement1, charElement2){});
foolist.sort(sortexpr(foo, f1, f2))
```
```cpp
intlist.sort(sortexpr(int, el1, el2){
    if(el1 > el2)
        return 1; // return more than 0
    else if(el1 < el2)
        return -1; // return less than 0
    else 
        return 0; // return only 0
});

intlist.sort(sortexpr(int, el1, el2){
    // for int we can do
    return el2 - el2; // to ascending sort
});

timelist.sort(sortexpr(time, t1, t2){
    return (t2.totalSec()) - (t1.totalSec());
});
```

### 6. Finding
To find element in list.
- use `.find` with `findexpr` built-in macro function and target index in list, -1 if can't found.
`findexpr(<type>, <target>, <name1>, <name2>){/*how to check if it equal*/}`
```cpp
int resultIndex = intlist.find(findexpr(int, 99, el1, el2){
    return el1 == el2;
});

int resultIndex = timelist.find(findexpr(time, {6, 0}, t1, t2){
    return (t1.hour == t2.hour && t1.minute == t2.minute);
});
```

### 7. Iteration
To make an interation through a list
- use `.each` with `eachexpr` built-in macro function.
`
eachexpr(<type>,<itemName>,<indexName>){apply algorithm}
`
```cpp
intlist.each(eachexpr(int, el, i){
    el += 10;
});

// limitation
int sum = 0;
intlist.each(eachexpr(int, el, i){
    // can't access sum here
    // need to make sum be global variable
});

// solution
int sum = 0; // global
void setup () {
    list<int> intlist;
    intlist.insertBack(new int(10));
    intlist.insertBack(new int(10));
    intlist.insertBack(new int(10));
    intlist.each(eachexpr(int, el, i){
        sum += el;
    })
    Serial.println(sum); //30
}

```

### 8. Others
- use `.setEnd` to specific how to free memory after scoped `{}` was reached.
```cpp
intlist.setEnd(true, true); // free node and data this is default

intlist.setEnd(true, false); // free only node
intlist.setEnd(false, true); // free only data
intlist.setEnd(false, false); // free nothing, use carefully
```