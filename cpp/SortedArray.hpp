//
//  TestArray.hpp
//  ListArrayComparison
//
//  Created by Antti Juustila on 14.9.2020.
//

#pragma once

#include "TestClass.hpp"
#include "TestContainer.hpp"

/**
 Implements an array of test objects in a continuous area in memory.
 */
class SortedArray : public TestContainer {

public:
   SortedArray();
   SortedArray(const SortedArray &) = delete;
   SortedArray(const SortedArray &&) = delete;
   const SortedArray & operator = (const SortedArray &) = delete;

   // Implements TestContainer.
   int getCount() const override;
   void add(const TestClass & object) override;
   int getIndex(int id) const override;
   const TestClass * get(int index) const override;
   const TestClass * find(int id) const override;
   TestClass * find(int id) override;

   virtual ~SortedArray();

private:
   /** Count of elements in the array. */
   int count;
   /** A pointer to the array of test objects. */
   TestClass * array;
};

/** Implements the print operator to print out elements in the array to output stream. */
std::ostream & operator << (std::ostream & os, const SortedArray & array);
