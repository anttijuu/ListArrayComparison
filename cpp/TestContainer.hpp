//
//  TestContainer.hpp
//  ListArrayComparison
//
//  Created by Antti Juustila on 14.9.2020.
//

#pragma once

class TestClass;

/**
 An interface class defining a container for this test app.
 Array and List implement the TestContainer interface.
 */
class TestContainer {
public:
   /** Returns the number of elements in the container.
    @returns The number of elements in the container.
    */
   virtual int getCount() const = 0;
   /**
    Adds a TestClass object into the container, in order. Order
    is defined by the id of the TestClass object.
    @param object The object to add to the container.
    */
   virtual void add(const TestClass & object) = 0;
   /**
    Gets the index of the object in the container.
    @param id The id of the object to find.
    @returns The index of the object having the id, or -1 if not found.
    */
   virtual int getIndex(int id) const = 0;
   /**
    Retrieve an object from the container by the index number.
    If the index is invalid, app is terminated.
    @param index The index of the object in the container.
    @returns A reference to the object in the index.
    */
   virtual const TestClass * get(int index) const = 0;
   /**
    Retrieve an object in the container by the id (const version).
    @param id The id of the object to find.
    @returns The object with the id, null if not found.
    */
   virtual const TestClass * find(int id) const = 0;
   /**
    Retrieve an object in the container by the id (modifiable version).
    @param id The id of the object to find.
    @returns The object with the id, null if not found.
    */
   virtual TestClass * find(int id) = 0;

   virtual ~TestContainer() { /* empty */ };
};

