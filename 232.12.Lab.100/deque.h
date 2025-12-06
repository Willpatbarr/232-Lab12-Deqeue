/***********************************************************************
 * Header:
 *    DEQUE
 * Summary:
 *    Our custom implementation of a deque
 *      __       ____       ____         __
 *     /  |    .'    '.   .'    '.   _  / /
 *     `| |   |  .--.  | |  .--.  | (_)/ /
 *      | |   | |    | | | |    | |   / / _
 *     _| |_  |  `--'  | |  `--'  |  / / (_)
 *    |_____|  '.____.'   '.____.'  /_/
 *
 *    This will contain the class definition of:
 *        deque                 : A class that represents a deque
 *        deque::iterator       : An iterator through a deque
 * Author
 *    Sara Fisk, Willaim Patrick-Barr
 ************************************************************************/

#pragma once

// Debug stuff
#include <cassert>
#include <memory>

class TestDeque;    // forward declaration for TestDeque unit test class

namespace custom
{

/******************************************************
 * DEQUE
 *         iaFront
 * ia =   0   1   2   3   4
 *      +---+---+---+---+---+
 *      |   | A | B | C |   |
 *      +---+---+---+---+---+
 * id =       0   1   2
 * iaFront = 1
 * numElements = 3
 * numCapacity = 5
 *****************************************************/
template <class T>
class deque
{
   friend class ::TestDeque; // give unit tests access to the privates
public:

   // 
   // Construct
   //
   deque() : data(nullptr),
             numCapacity(0),
             numElements(0),
             iaFront(0)
   {
   }
   deque(int newCapacity);
   deque(const deque <T> & rhs);
   ~deque()
   {
      if (numCapacity > 0)
      {
         assert(data != nullptr);
         delete [] data;
      }
      
      // not strictly required, but keeps things in a known state
      data        = nullptr;
      numCapacity = 0;
      numElements = 0;
      iaFront     = 0;
   }

   //
   // Assign
   //
   deque<T> & operator = (const deque <T> & rhs);

   //
   // Iterator
   //
   class iterator;
   iterator begin()
   {
      return iterator();
   }
   iterator end()
   {
      return iterator();
   }

   //
   // Access
   //
   T& front();
   T& back();
   const T & front() const;
   const T & back()  const;
   const T & operator[](size_t index) const;
   T& operator[](size_t index);

   // 
   // Insert
   //
   void push_front(const T& t);
   void push_back(const T& t);

   //
   // Remove
   //
   void clear()
   { 
   }
   void pop_front();
   void pop_back();

   // 
   // Status
   //
   size_t size() const 
   { 
      return 99; 
   }
   bool empty() const 
   { 
      return false; 
   }

   
private:
   
   // fetch array index from the deque index
   int iaFromID(int id) const
   {
      return -99;
   }
   void resize(int newCapacity = 0);

   // member variables
   T * data;           // dynamically allocated data for the deque
   size_t numCapacity; // the size of the data array
   size_t numElements; // number of elements in the deque
   int iaFront;        // the index of the first item in the array
};



/**********************************************************
 * DEQUE ITERATOR
 * Forward and reverse iterator through a deque, just call
 *********************************************************/
template <typename T>
class deque <T> ::iterator
{
   friend class ::TestDeque; // give unit tests access to the privates
public:
   //
   // Construct
   //
   iterator()
   {
   }
   iterator(custom::deque<T> *pDeque, int id)
   {
   }
   iterator(const iterator& rhs)
   {
   }

   //
   // Assign
   //
   iterator& operator = (const iterator& rhs)
   {
      return *this;
   }

   //
   // Compare
   //
   bool operator == (const iterator& rhs) const { return true; }
   bool operator != (const iterator& rhs) const { return true; }

   // 
   // Access
   //
   const T & operator * () const
   {
      return *(new T);
   }
   T& operator * () 
   {
      return *(new T);
   }

   // 
   // Arithmetic
   //
   int operator - (iterator it) const
   {
      return 99;
   }
   iterator& operator += (int offset)
   {
      return *this;
   }
   iterator& operator ++ ()
   {
      return *this;
   }
   iterator operator ++ (int postfix)
   {
      return *this;
   }
   iterator& operator -- ()
   {
      return *this;
   }
   iterator  operator -- (int postfix)
   {
      return *this;
   }

private:

   // Member variables
   int id;             // deque index
   deque<T> *pDeque;
};


/****************************************************
 * DEQUE : CONSTRUCTOR - non-default
 ***************************************************/
template <class T>
deque <T> :: deque(int newCapacity)
   : data(nullptr),
     numCapacity(0),
     numElements(0),
     iaFront(0)
{
   assert(newCapacity >= 0);

   if (newCapacity > 0)
   {
      numCapacity = static_cast<size_t>(newCapacity);
      data        = new T[numCapacity];   // default-constructed slots
      // numElements stays 0; deque is logically empty but has storage
   }
}

/****************************************************
 * DEQUE : CONSTRUCTOR - copy
 ***************************************************/
template <class T>
deque <T> :: deque(const deque <T> & rhs)
   : data(nullptr),
     numCapacity(0),
     numElements(0),
     iaFront(0)
{
   // empty source: leave this as an empty deque
   if (rhs.numCapacity == 0 || rhs.data == nullptr)
      return;

   numCapacity = rhs.numCapacity;
   numElements = rhs.numElements;
   iaFront     = rhs.iaFront;

   data = new T[numCapacity];
   for (size_t i = 0; i < numCapacity; ++i)
      data[i] = rhs.data[i];
}


/****************************************************
 * DEQUE : ASSIGNMENT OPERATOR
 ***************************************************/
template <class T>
deque <T> & deque <T> :: operator = (const deque <T> & rhs)
{
   // self-assignment guard
   if (this == &rhs)
      return *this;

   // if source is empty, just clear destination but keep capacity
   if (rhs.numElements == 0)
   {
      numElements = 0;
      iaFront     = 0;
      return *this;
   }

   // if we don't have enough capacity, reallocate
   if (rhs.numElements > numCapacity)
   {
      if (data != nullptr)
         delete [] data;

      numCapacity = rhs.numElements;
      data        = new T[numCapacity];
   }

   // copy elements in logical order so that our iaFront = 0
   numElements = rhs.numElements;
   iaFront     = 0;

   for (size_t id = 0; id < rhs.numElements; ++id)
   {
      // logical index id → rhs array index
      int iaSrc = (rhs.iaFront + static_cast<int>(id)) %
                  static_cast<int>(rhs.numCapacity);

      data[id] = rhs.data[iaSrc];
   }

   return *this;
}



/**************************************************
 * DEQUE :: FRONT
 * Fetch the item that is at the beginning of the deque
 *************************************************/
template <class T>
const T & deque <T> :: front() const 
{
   return *(new T);
}
template <class T>
T& deque <T> ::front()
{
   return *(new T);
}

/**************************************************
 * DEQUE :: BACK
 * Fetch the item that is at the end of the deque
 *************************************************/
template <class T>
const T & deque <T> :: back() const 
{
   return *(new T);
}
template <class T>
T& deque <T> ::back()
{
   return *(new T);
}

/**************************************************
 * DEQUE :: SUBSCRIPT
 * Fetch the item in the deque
 *************************************************/
template <class T>
const T& deque <T> ::operator[](size_t index) const
{
   return *(new T);
}
template <class T>
T& deque <T> ::operator[](size_t index)
{
   return *(new T);
}

/*****************************************************
 * DEQUE : POP_BACK
 *****************************************************/
template <class T>
void deque <T> :: pop_back()
{
}

/*****************************************************
 * DEQUE : POP_FRONT
 *****************************************************/
template <class T>
void deque <T> :: pop_front()
{
}

/******************************************************
 * DEQUE : PUSH_BACK
 ******************************************************/
template <class T>
void deque <T> :: push_back(const T & t) 
{
}

/******************************************************
 * DEQUE : PUSH_FRONT
 ******************************************************/
template <class T>
void deque <T> :: push_front(const T & t) 
{
}

/****************************************************
 * DEQUE :: RESIZE
 * Resize the deque so the numCapacity matches the newCapacity
 ***************************************************/
template <class T>
void deque <T> :: resize(int newCapacity) 
{
}

} // namespace custom
