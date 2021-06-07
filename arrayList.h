#ifndef arraylist_
#define arraylist_

#include "linearList.h"
#include "myexceptions.h"
#include "changeLength1D.h"

#include <sstream>

template<class T>
class arrayList : public linearList<T> {
  public:
    // 构造函数，复制构造函数和析构函数
    arrayList(int initialCapacity = 10);
    arrayList(const arrayList&);
    ~arrayList() { delete [] element; }

  // ADT methods
  bool empty() const { return listSize == 0; }
  int size() const { return listSize; }
  T& get(int theIndex) const;
  int indexOf(const T& theElement) const;
  void insert(int theIndex, const T& theElement);
  void erase(int theIndex);
  void output(ostream& out) const;

  // others
  int capacity() const { return arrayLength; }

  protected:
    void checkIndex(int theIndex) const;

    T* element;
    int arrayLength;
    int listSize;
};

template<class T>
arrayList<T>::arrayList(int initialCapacity)
{  // 构造函数
  if (initialCapacity < 1) {
    throw illegalParameterValue();
  }

  arrayLength = initialCapacity;
  element = new T[arrayLength];
  listSize = 0;
}

template<class T>
arrayList<T>::arrayList(const arrayList& theList)
{ // 复制构造函数
  arrayLength = theList.arrayLength;
  listSize = theList.listSize;
  element = new T[arrayLength];
  
  copy(theList.element, theList.element + listSize, element);
}

template<class T>
void arrayList<T>::checkIndex(int theIndex) const {
  if (theIndex < 0 || theIndex >= listSize)
    throw illegalIndex(); 
}

template<class T>
T& arrayList<T>::get(int theIndex) const {
  checkIndex(theIndex);
  return element[theIndex];
}

template<class T>
int arrayList<T>::indexOf(const T& theElement) const {
  int theIndex = find(element, element + listSize, theElement) - element;
  if (theIndex == listSize)
    return -1;

  return theIndex;
}

template<class T>
void arrayList<T>::insert(int theIndex, const T& theElement) {
  if (theIndex < 0 || theIndex > listSize) {
    // invalid index
    ostringstream s;
    s << "index = " << theIndex << " size = " << listSize;
    throw illegalIndex(s.str());
  }
  // 空间满，扩容
  if (listSize == arrayLength) {
    changeLength1D(element, arrayLength, arrayLength << 1);
    arrayLength <<= 1; 
  }

  copy_backward(element + theIndex, element + listSize, element + listSize + 1);
  element[theIndex] = theElement;
  ++listSize;
}

template<class T>
void arrayList<T>::erase(int theIndex) {
  checkIndex(theIndex);
  copy(element + theIndex + 1, element + listSize, element + theIndex);
  element[--listSize].~T();
}

template<class T>
void arrayList<T>::output(ostream& out) const {
  for (T* p = element; p != element + listSize; ++p)
    out << *p << ' ';
}

// 重载 <<
template<class T>
ostream& operator<<(ostream& out, const arrayList<T>& x) {
  x.output(out); return out;
}
#endif