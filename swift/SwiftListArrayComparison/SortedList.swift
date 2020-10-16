//
//  SortedList.swift
//  SwiftListArrayComparison
//
//  Created by Antti Juustila on 15.9.2020.
//

import Foundation

// TODO: make this a struct, implement list fully, with insertInOrder (and sort, obviously).
class SortedList: TestContainer {

   private class TestListNode {
      var object: TestClass?
      var nextNode: TestListNode?
   }

   var count: Int = 0
   
   private var firstNode: TestListNode?

   func add(object: TestClass) -> Void {
      var added = false
      // List is empty, just add a new node as first.
      if (firstNode == nil) {
         firstNode = TestListNode()
         firstNode!.object = object
         firstNode!.nextNode = nil
         count += 1
         added = true
      } else {
         // List has elements, but the new one belongs to the beginning.
         if (object.id <= firstNode!.object!.id) {
            let newFirst = TestListNode()
            newFirst.nextNode = firstNode
            newFirst.object = object
            firstNode = newFirst
            count += 1
            added = true
         } else {
            // List has elements, find the place to add the element.
            var previous = firstNode
            var next = previous!.nextNode
            // If the node has a next one, check if this is smaller than it.
            while (next != nil) {
               if (object.id <= next!.object!.id) {
                  added = true
                  count += 1
                  let oldNext = previous!.nextNode
                  previous!.nextNode = TestListNode()
                  previous!.nextNode!.object = object
                  previous!.nextNode!.nextNode = oldNext
                  break
               }
               previous = next
               next = next!.nextNode
            }
            // Went ot the end and did not add a node ==> add it to the end
            if (!added) {
               added = true
               count += 1
               let oldNext = previous!.nextNode
               previous!.nextNode = TestListNode()
               previous!.nextNode!.object = object
               previous!.nextNode!.nextNode = oldNext
            }
         }
      }
      assert(added)
   }

   func getIndex(of id: Int) -> Int {
      var counter = 0
      var current = firstNode
      while (current != nil) {
         if (current!.object!.id == id) {
            return counter
         }
         counter += 1
         current = current!.nextNode
      }
      return -1;
   }

   func get(index: Int) -> TestClass {
      assert(index >= 0 && index < count)
      var counter = 0
      var current = firstNode
      while (current != nil) {
         if (counter == index) {
            break
         }
         counter += 1
         current = current!.nextNode
      }
      return current!.object!
   }

   func find(id: Int) -> TestClass? {
      var current = firstNode
      while (current != nil) {
         if (current!.object!.id == id) {
            return current!.object
         }
         current = current!.nextNode
      }
      return nil;
   }

   func print() -> Void {
      var current = firstNode
      while (current != nil) {
         Swift.print("\(current!.object!)")
         current = current!.nextNode
      }
   }

}
