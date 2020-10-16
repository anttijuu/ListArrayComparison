//
//  TestClass.hpp
//  ListArrayComparison
//
//  Created by Antti Juustila on 14.9.2020.
//

#pragma once

#include <string>

/**
 Instances of TestClass are put into arrays and lists.
 */
class TestClass {
public:
   /*! Constans used in defining member data. */
   enum Consts {
      NameLength = 40, /*!< Max length of the name member. */
      DataLength = 500 /*!< Max length of the data member. */
   };

   TestClass();
   TestClass(int newId, const char * n, const char * d);
   TestClass(const TestClass & another);
   const TestClass & operator = (const TestClass & another);

   int getId() const;
   const char * getName() const;
   const char * getData() const;

   virtual ~TestClass();
   
private:

   /** An id identifies an object. */
   int id;
   /** A name for the test object. */
   char name[Consts::NameLength];
   /** Some random binary data for the test object. */
   char data[Consts::DataLength];
};

/** an operator for streaming the contents of the test object to any output stream. */
std::ostream & operator << (std::ostream & os, const TestClass & object);
