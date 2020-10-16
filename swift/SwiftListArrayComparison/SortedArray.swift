//
//  SortedArray.swift
//  SwiftListArrayComparison
//
//  Created by Antti Juustila on 15.9.2020.
//

import Foundation

class SortedArray: TestContainer {
   private var array: [TestClass] = []

   var count: Int

   init() {
      count = 0
   }
   
   func add(object: TestClass) -> Void {
      var added = false
      var tempArray = [TestClass] ()
      tempArray.reserveCapacity(array.count + 1)
      var addIndex = 0
      for index in 0..<array.count {
         if !added && object.id < array[index].id {
            tempArray.insert(object, at: addIndex)
            added = true
            addIndex += 1
         }
         tempArray.insert(array[index], at: addIndex)
         addIndex += 1
      }
      if !added {
         tempArray.append(object)
      }
      array = tempArray
      count += 1
   }

   func getIndex(of id: Int) -> Int {
      for index in 0..<count {
         if array[index].id == id {
            return index
         }
      }
      return -1
   }

   func get(index: Int) -> TestClass {
      assert(index >= 0 && index < array.count)
      return array[index]
   }

   func find(id: Int) -> TestClass? {
      for object in array {
         if object.id == id {
            return object
         }
      }
      return nil
   }

   func print() -> Void {
      for object in array {
         Swift.print("\(object)")
      }
   }

}
