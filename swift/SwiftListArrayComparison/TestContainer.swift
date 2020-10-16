//
//  TestContainer.swift
//  SwiftListArrayComparison
//
//  Created by Antti Juustila on 15.9.2020.
//

import Foundation

protocol TestContainer {
   var count: Int { get set }
   func add(object: TestClass) -> Void
   func getIndex(of id: Int) -> Int
   func get(index: Int) -> TestClass
   func find(id: Int) -> TestClass?
   func print() -> Void 
}
