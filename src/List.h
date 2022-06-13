#ifndef __SIMPLE_LIST_H__
#define __SIMPLE_LIST_H__

template <typename T>
struct listnode
{
  T *data;
  listnode<T> *next;
};

template <typename T>
class list
{
public:
  // insertion
  /**
   * @brief "back insertion" : insert data attached node to last position.
   *
   * @param data address of data needs to be attached.
   * @return T* loopback address of data
   */
  T *insertBack(T *data)
  {
    listnode<T> *node = new listnode<T>({data, nullptr});
    if (listsize == 0)
    {
      firstInsert(node);
    }
    else
    {
      tail->next = node;
      tail = node;
      listsize++;
    }
    return data;
  }
  /**
   * @brief "front insertion" : insert data attached node to first position.
   *
   * @param data address of data needs to be attached.
   * @return T* loopback address of data
   */
  T *insertFront(T *data)
  {
    listnode<T> *node = new listnode<T>({data, nullptr});
    if (listsize == 0)
    {
      firstInsert(node);
    }
    else
    {
      node->next = head;
      head = node;
      listsize++;
    }
    return data;
  }
  /**
   * @brief "specific position insertion" : insert data attached node to specific position.
   *
   * @param data address of data needs to be attached.
   * @param index specific position, start at 0.
   * @return T* loopback address of data.
   */
  T *insertAt(T *data, unsigned int index)
  {
    listnode<T> *node = new listnode<T>({data, nullptr});
    if (listsize == 0)
    {
      firstInsert(node);
    }
    else
    {
      index = indexCorrector(index);
      if (index == 0)
        insertFront(data);
      else if (index == listsize)
        insertBack(data);
      else
      {
        listnode<T> *bt = getNodeAddr(index - 1);
        listnode<T> *t = bt->next;
        node->next = t;
        bt->next = node;
        listsize++;
      }
    }
    return data;
  }
#define arrsize(arr) sizeof(arr) / sizeof(arr[0])
  /**
   * @brief "load from array" : insert new copied created data from array to list.
   *
   * @param arr prototype array.
   * @param arrSize array size.
   * @return T* loopback array address.
   */
  T *fromArray(T arr[], unsigned int arrSize)
  {
    for (unsigned int i = 0; i < arrSize; i++)
    {
      insertBack(new T(arr[i]));
    }
    return arr;
  }

  // get
  /**
   * @brief "get node adress" : get node address at specific position.
   *
   * @param index position, start at 0.
   * @return listnode<T>* address of node.
   */
  listnode<T> *getNodeAddr(unsigned int index)
  {
    index = indexCorrector(index);
    listnode<T> *target = head;
    for (unsigned int i = 0; i < index; i++)
    {
      target = target->next;
    }
    return target;
  }
  /**
   * @brief "get node" : get node or reference of node at specific position.
   *
   * @param index position, start at 0.
   * @return listnode<T>& copy(no-&) or reference(&) of node.
   */
  listnode<T> &getNode(unsigned int index)
  {
    return *getNodeAddr(index);
  }
  /**
   * @brief "get data": get copy or reference of data at specific position.
   *
   * @param index position, start at 0.
   * @return T& copy(no-&) or reference(&) of data.
   */
  T &get(unsigned int index)
  {
    return *getNodeAddr(index)->data;
  }
  /**
   * @brief "get data": get copy or reference of data at specific position.
   *
   * @param index position, start at 0.
   * @return T& copy(no-&) or reference(&) of data.
   */
  T &operator[](unsigned int index)
  {
    return get(index);
  }

  // remove
  /**
   * @brief "remove node and data": remove node and data(if necessary) from list.
   *
   * @param index position, start at 0.
   * @param freeData true: free data, false: free only node.
   */
  void remove(unsigned int index, bool freeData = true)
  {
    if (listsize == 0)
      return;
    index = indexCorrector(index);
    listnode<T> *target;
    if (index == 0)
    {
      target = head;
      head = head->next;
    }
    else if (index == listsize - 1)
    {
      listnode<T> *bt = getNodeAddr(index - 1);
      target = bt->next;
      bt->next = nullptr;
      tail = bt;
    }
    else
    {
      listnode<T> *bt = getNodeAddr(index - 1);
      target = bt->next;
      bt->next = target->next;
    }
    freeup(target, freeData);
    listsize--;
  }
  /**
   * @brief "clear list nodes": remove all node and data(if necessary) in list.
   *
   * @param freeData  true: free data, false: remove only node.
   */
  void clearList(bool freeData)
  {
    listnode<T> *target;
    for (unsigned int i = 0; i < listsize; i++)
    {
      target = head;
      freeup(target, freeData);
      head = head->next;
    }
    head = nullptr;
    tail = nullptr;
    listsize = 0;
  }

// helper
#define findexpr(type, target, itemName1, itemName2) target, [](type & itemName1, type & itemName2) -> bool
  /**
   * @brief "find index" : find index that equal to target following desire check algorithm.
   *
   * @param target thing to find.
   * @param checkequal check algorithm of two items.
   * @return int index of target, -1 if not found.
   */
  int find(T target, bool checkequal(T &a, T &b))
  {
    listnode<T> *tmp = head;
    for (unsigned int i = 0; i < listsize; i++)
    {
      if (checkequal(target, *tmp->data))
        return i;
      tmp = tmp->next;
    }
    return -1;
  }
#define sortexpr(type, itemName1, itemName2) [](type & itemName1, type & itemName2) -> int
  /**
   * @brief "sort list" : sort all nodes following desire algorithm.
   *
   * @param compare compare algorithm of two items.
   */
  void sort(int (*compare)(T &a, T &b))
  {
    list<T> newlist;
    newlist.setEnd(false, false);
    listnode<T> *tmp, *btmp, *cand;
    unsigned int candIndex, tmpIndex;
    unsigned int len = listsize;
    for (unsigned int i = 0; i < len; i++)
    {
      btmp = head;
      cand = head;
      candIndex = 0;
      tmp = btmp->next;
      tmpIndex = 1;
      while (tmp != nullptr)
      {
        if (compare(*cand->data, *tmp->data) > 0)
        {
          cand = tmp;
          candIndex = tmpIndex;
        }
        btmp = tmp;
        tmp = tmp->next;
        tmpIndex++;
      }
      newlist.insertBack(cand->data);
      remove(candIndex, false);
    }
    head = newlist.getNodeAddr(0);
    tail = newlist.getNodeAddr(listsize - 1);
    listsize = newlist.size();
  }
#define eachexpr(type, itemName, indexName) [](type & itemName, unsigned int indexName)
  /**
   * @brief "for each" : apply desire algorithm to every nodes in list.
   *
   * @param apply apply algorithm.
   */
  void each(void (*apply)(T &a, unsigned int index))
  {
    listnode<T> *tmp = head;
    for (unsigned int i = 0; i < listsize; i++)
    {
      apply(*tmp->data, i);
      tmp = tmp->next;
    }
  }
  /**
   * @brief "export to static array" : copy to pre-create static array.
   *
   * @param arr pre-create static array.
   */
  void toStaticArray(T arr[])
  {
    listnode<T> *tmp = head;
    for (unsigned int i = 0; i < listsize; i++)
    {
      arr[i] = *tmp->data;
      tmp = tmp->next;
    }
  }
  /**
   * @brief "export to dynamic array" : create dynamic(heap) array from list.
   *
   * @return T* dynamic array, !!!need delete[] after use ex: delete[] arr.
   */
  T *toDynamicArray()
  {
    int *arr = new int[listsize];
    listnode<T> *tmp = head;
    for (unsigned int i = 0; i < listsize; i++)
    {
      arr[i] = *tmp->data;
      tmp = tmp->next;
    }
    return arr;
  }
  /**
   * @brief "size of list" : return size of list.
   *
   * @return unsigned int size of list.
   */
  unsigned int size()
  {
    return listsize;
  }
  void setEnd(bool destroyNode, bool destroyData)
  {
    this->destroyNode = destroyNode;
    this->destroyData = destroyData;
  }

private:
  T *firstInsert(listnode<T> *node)
  {
    head = node;
    tail = node;
    listsize = 1;
    return node->data;
  }
  unsigned int indexCorrector(unsigned int index)
  {
    return (index > listsize - 1) ? listsize - 1 : index;
  }
  void freeup(listnode<T> *node, bool freeData)
  {
    if (freeData)
      delete node->data;
    delete node;
  }

private:
  unsigned int listsize;
  listnode<T> *head, *tail;
  // out of scope procedure
  bool destroyNode = true;
  bool destroyData = true;

public:
  list(T arr[], unsigned arrSize)
  {
    listsize = 0;
    head = nullptr;
    tail = nullptr;
    fromArray(arr, arrSize);
  }
  list()
  {
    listsize = 0;
    head = nullptr;
    tail = nullptr;
  }
  ~list()
  {
    if (destroyNode)
      clearList(destroyData);
  }
};

#endif