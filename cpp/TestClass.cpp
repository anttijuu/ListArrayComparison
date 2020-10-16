//
//  TestClass.cpp
//  ListArrayComparison
//
//  Created by Antti Juustila on 14.9.2020.
//

#include <utility>
#include <iostream>

#include "TestClass.hpp"

TestClass::TestClass()
: id(0)
{
   memset(name, 0, sizeof name);
   memset(data, 0, sizeof data);
}

TestClass::TestClass(const TestClass & another)
: id(another.id)
{
   memset(name, 0, sizeof name);
   memset(data, 0, sizeof data);
   strncat(name, another.name, sizeof name);
   memcpy(data, another.data, sizeof data);
}

const TestClass & TestClass::operator = (const TestClass & another) {
   id = another.id;
   memset(name, 0, sizeof name);
   memset(data, 0, sizeof data);
   strncat(name, another.name, sizeof name);
   memcpy(data, another.data, sizeof data);
   return *this;
}

TestClass::TestClass(int newId, const char * n, const char * d)
: id(newId)
{
   memset(name, 0, sizeof name);
   memset(data, 0, sizeof data);
   strncat(name, n, sizeof name);
   memcpy(data, d, sizeof data);
}

int TestClass::getId() const {
   return id;
}

const char * TestClass::getName() const {
   return name;
}

const char * TestClass::getData() const {
   return data;
}

TestClass::~TestClass() {
}

std::ostream & operator << (std::ostream & os, const TestClass & object) {
   os << "id: " << object.getId() << " name: " << std::string(object.getName()) << " data: " << std::string(object.getData());
   return os;
}
