//
//  TestArray.cpp
//  ListArrayComparison
//
//  Created by Antti Juustila on 14.9.2020.
//

#include <iostream>

#include "SortedArray.hpp"

SortedArray::SortedArray()
: count(0), array(nullptr)
{
}

void SortedArray::add(const TestClass & object) {
   bool added = false;
   TestClass * tempArray = new TestClass[count + 1];
   int addIndex = 0;
   for (int index = 0; index < count; index++, addIndex++) {
      if (!added && object.getId() < array[index].getId()) {
         tempArray[addIndex] = object;
         added = true;
         addIndex++;
      }
      tempArray[addIndex] = array[index];
   }
   if (!added) {
      tempArray[addIndex] = object;
   }
   delete [] array;
   array = tempArray;
   count += 1;
}

int SortedArray::getCount() const {
   return count;
}

int SortedArray::getIndex(int id) const {
   for (int index = 0; index < count; index++) {
      if (array[index].getId() == id) {
         return index;
      }
   }
   return -1;
}

const TestClass * SortedArray::get(int index) const {
   assert(index >= 0 && index < count);
   return &array[index];
}

const TestClass * SortedArray::find(int id) const {
   for (int index = 0; index < count; index++) {
      if (array[index].getId() == id) {
         return &array[index];
      }
   }
   return nullptr;
}

TestClass * SortedArray::find(int id) {
   for (int index = 0; index < count; index++) {
      if (array[index].getId() == id) {
         return &array[index];
      }
   }
   return nullptr;
}

std::ostream & operator << (std::ostream & os, const SortedArray & array) {
   for (int index = 0; index < array.getCount(); index++) {
      std::cout << array.get(index) << std::endl;
   }
   return os;
}

SortedArray::~SortedArray() {
   delete [] array;
}

