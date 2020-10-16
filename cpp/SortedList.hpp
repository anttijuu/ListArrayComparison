//
//  TestList.hpp
//  ListArrayComparison
//
//  Created by Antti Juustila on 14.9.2020.
//

#pragma once

#include "TestContainer.hpp"
#include "TestClass.hpp"


/**
 A container implementing a sorted linked list. When items are added to the
 container, they are always in a sorted order (by the id of the objects).
 @todo Add the usual list things + sort + addInOrder/addInSequence
 */
class SortedList : public TestContainer {
public:
   SortedList();
   SortedList(const SortedList &) = delete;
   SortedList(const SortedList &&) = delete;
   const SortedList & operator = (const SortedList &) = delete;

   // Implements TestContainer.
   int getCount() const override;
   void add(const TestClass &object) override;
   int getIndex(int id) const override;
   const TestClass * get(int index) const override;
   const TestClass * find(int id) const override;
   TestClass * find(int id) override;

   virtual ~SortedList();

   /** Implements the print operator for the SortedList. */
   friend std::ostream & operator << (std::ostream & os, const SortedList & list);
   
private:
   /**
    Private implementation struct to implement the linked list.
    */
   struct TestListNode {
      TestClass object;
      TestListNode * nextNode;
   };
   /** Number of elements in the list. */
   int count;
   /** Pointer to the first node in the list, the head. */
   TestListNode * firstNode;
};


