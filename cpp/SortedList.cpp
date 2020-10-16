//
//  TestList.cpp
//  ListArrayComparison
//
//  Created by Antti Juustila on 14.9.2020.
//
#include <iostream>

#include "SortedList.hpp"

SortedList::SortedList()
: count(0), firstNode(nullptr)
{
}

SortedList::~SortedList() {
   if (firstNode) {
      TestListNode * current = firstNode;
      TestListNode * next = current->nextNode;
      while (next) {
         delete current;
         current = next;
         next = next->nextNode;
      }
      delete current;
   }
}


int SortedList::getCount() const {
   return count;
}

void SortedList::add(const TestClass &object) {
   bool added = false;
   // List is empty, just add a new node as first.
   if (!firstNode) {
      firstNode = new TestListNode();
      firstNode->object = object;
      firstNode->nextNode = nullptr;
      count++;
      added = true;
   } else {
      // List has elements, but the new one belongs to the beginning.
      if (object.getId() <= firstNode->object.getId()) {
         TestListNode * newFirst = new TestListNode();
         newFirst->nextNode = firstNode;
         newFirst->object = object;
         firstNode = newFirst;
         count++;
         added = true;
      } else {
         // List has elements, find the place to add the element.
         TestListNode * previous = firstNode;
         TestListNode * next = previous->nextNode;
         // If the node has a next one, check if this is smaller than it.
         while (next) {
            if (object.getId() <= next->object.getId()) {
               added = true;
               count++;
               TestListNode * oldNext = previous->nextNode;
               previous->nextNode = new TestListNode();
               previous->nextNode->object = object;
               previous->nextNode->nextNode = oldNext;
               break;
            }
            previous = next;
            next = next->nextNode;
         }
         // Went ot the end and did not add a node ==> add it to the end
         if (!added) {
            added = true;
            count++;
            TestListNode * oldNext = previous->nextNode;
            previous->nextNode = new TestListNode();
            previous->nextNode->object = object;
            previous->nextNode->nextNode = oldNext;
         }
      }
   }
   assert(added);
}

int SortedList::getIndex(int id) const {
   int counter = 0;
   TestListNode * current = firstNode;
   while (current) {
      if (current->object.getId() == id) {
         return counter;
      }
      counter++;
      current = current->nextNode;
   }
   return -1;
}

const TestClass * SortedList::get(int index) const {
   assert(index >= 0 && index < count);
   int counter = 0;
   TestListNode * current = firstNode;
   while (current) {
      if (counter == index) {
         break;
      }
      counter++;
      current = current->nextNode;
   }
   if (current) {
      return &current->object;
   }
   return nullptr;

}

const TestClass * SortedList::find(int id) const {
   TestListNode * current = firstNode;
   while (current) {
      if (current->object.getId() == id) {
         return &current->object;
      }
      current = current->nextNode;
   }
   return nullptr;
}

TestClass * SortedList::find(int id) {
   TestListNode * current = firstNode;
   while (current) {
      if (current->object.getId() == id) {
         return &current->object;
      }
      current = current->nextNode;
   }
   return nullptr;
}

std::ostream & operator << (std::ostream & os, const SortedList & list) {
   if (list.firstNode) {
      SortedList::TestListNode * current = list.firstNode;
      SortedList::TestListNode * next = current->nextNode;
      os << current->object << std::endl;
      while (next) {
         current = next;
         next = next->nextNode;
         os << current->object << std::endl;
      }
   }
   return os;
}
