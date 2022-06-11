#ifndef __LIST_H__
#define __LIST_H__

typedef unsigned int index_t;
typedef unsigned int size_t;

template <typename T>
struct ListNode
{
  T *data;
  ListNode<T> *next;
};

template <typename T>
class List
{
private:
  // data
  size_t size;
  ListNode<T> *head, *tail;
  // helper methods
  void free(ListNode<T> *node)
  {
    Serial.println("deleted!");
    delete node->data;
    delete node;
  }

public:
  List()
  {
    size = 0;
    head = nullptr;
    tail = nullptr;
  }
  ~List() {}
  // basic methods
  ListNode<T> *getNode(index_t index)
  {
    index %= size;
    if (index > size - 1)
    {
      return nullptr;
    }

    ListNode<T> *target = head;
    for (size_t i = 0; i < index; i++)
    {
      target = target->next;
    }
    return target;
  }

  T *insert(T *data, index_t index = 0)
  {
    ListNode<T> *newNode = new ListNode<T>({data, nullptr});
    if (size == 0)
    { // empty insert
      head = newNode;
      tail = newNode;
      size = 1;
    }
    else
    {
      index %= size;
      if (index == 0)
      { // insert at head
        newNode->next = head;
        head = newNode;
      }
      else if (index == size - 1)
      { // insert at tail
        tail->next = newNode;
        tail = newNode;
      }
      else
      {
        ListNode<T> *befTarget = getNode(index - 1);
        newNode->next = befTarget->next;
        befTarget->next = newNode;
      }
      size++;
    }
    return data;
  }

  T *insertHead(T *data)
  {
    ListNode<T> *newNode = new ListNode<T>({data, nullptr});
    newNode->next = head;
    head = newNode;
    if (size == 0)
    {
      tail = head;
    }
    size++;
    return data;
  }

  T *insertBack(T *data)
  {
    ListNode<T> *newNode = new ListNode<T>({data, nullptr});
    tail->next = newNode;
    tail = newNode;
    if (size == 0)
    {
      head = tail;
    }
    size++;
    return data;
  }

  T &get(index_t index)
  {
    return *getNode(index)->data;
  }

  void remove(index_t index, bool freeSpace = true)
  {
    index %= size;
    if (size == 0 || index > size - 1)
    {
      return;
    }
    ListNode<T> *target = head;
    if (index == 0)
    { // remove head
      target = head;
      head = head->next;
    }
    else if (index == size - 1)
    { // remove tail
      target = tail;
      ListNode<T> *befTail = getNode(index - 1);
      befTail->next = tail->next;
      tail = befTail;
    }
    else
    {
      ListNode<T> *befTarget = getNode(index - 1);
      target = befTarget->next;
      befTarget->next = target->next;
    }
    if (freeSpace)
      free(target);
    size--;
  }

  bool isEmpty()
  {
    return (size == 0);
  }

  size_t getSize()
  {
    return size;
  }

  void clear(bool freeSpace = true)
  {
    ListNode<T> *tmp = head;
    ListNode<T> *target;
    for (size_t i = 0; i < size; i++)
    {
      target = tmp;
      tmp = tmp->next;
      if (freeSpace)
        free(target);
    }
    size = 0;
  }

  T *toDynamicArray()
  {
    T *arr = new T[size];
    ListNode<T> *tmp = head;
    for (size_t i = 0; i < size; i++)
    {
      arr[i] = *tmp->data;
      tmp = tmp->next;
    }

    return arr;
  }

  void toStaticArray(T arr[])
  {
    ListNode<T> *tmp = head;
    for (size_t i = 0; i < size; i++)
    {
      arr[i] = *tmp->data;
      tmp = tmp->next;
    }
  }

  // advance methods
#define sortfn(type, itemName1, itemName2) [](type & itemName1, type & itemName2) -> int
#define morethan 1
#define lessthan -1
#define equal 0
  void sort(int (*comparefn)(T &a, T &b), bool ascending = true)
  {
    List<T> newList;

    int decisionRule = (ascending) ? morethan : lessthan;
    ListNode<T> *beftmp, *tmp, *cand, *befcand;
    for (size_t i = 0; i < size; i++)
    {
      beftmp = nullptr;
      cand = head;
      tmp = head;
      while (tmp != nullptr)
      {
        if (comparefn(*cand->data, *tmp->data) == decisionRule)
        {
          cand = tmp;
          befcand = beftmp;
        }
        beftmp = tmp;
        tmp = tmp->next;
      }
      befcand->next = cand->next;
      // insert to new list
      newList.insertBack(cand->data);
      delete cand;
    }
    head = newList.getNode(0);
    tail = newList.getNode(newList.getSize());
    size = newList.getSize();
    // free newList
    newList.clear();
  }

#define eachfn(type, itemName, indexName) [](type & itemName, index_t indexName)
  void each(void (*apply)(T &, index_t index))
  {
    ListNode<T> *tmp = head;
    for (size_t i = 0; i < size; i++)
    {
      apply(*tmp->data, i);
      tmp = tmp->next;
    }
  }

#define findfn(type, itemName1, itemName2) [](type & itemName1, type & itemName2) -> bool
  int find(T a, bool (*isEqual)(T &a, T &b))
  {
    ListNode<T> *tmp = head;
    for (size_t i = 0; i < size; i++)
    {
      if (isEqual(a, *tmp->data))
        return i;
      tmp = tmp->next;
    }
    return -1;
  }

  size_t count();

  // operator
  T &operator[](index_t index)
  {
    return get(index);
  }
};

#endif