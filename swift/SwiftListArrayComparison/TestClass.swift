//
//  TestClass.swift
//  SwiftListArrayComparison
//
//  Created by Antti Juustila on 15.9.2020.
//

import Foundation

struct TestClass {
   var id: Int
   var name: String
   var data: String
}

extension TestClass: CustomStringConvertible {
   var description: String {
      "Id: " + String(id) + " Name: " + name + " Data: " + data
   }
}
