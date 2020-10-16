//
//  main.swift
//  SwiftListArrayComparison
//
//  Created by Antti Juustila on 15.9.2020.
//

import Foundation

SwiftListArrayComparisonApp.run()

class SwiftListArrayComparisonApp {

   static var fileName: String?
   static var file: FileHandle?
   static var idArray = [Int] ()

   static func run() -> Void {
      var numberCount = 1000
      var timesToMultiply = 1

      if CommandLine.arguments.count == 4 {
         if let count  = Int(CommandLine.arguments[1]) {
            numberCount = count
         }
         if let times = Int(CommandLine.arguments[2]) {
            timesToMultiply = times
         }
         fileName = CommandLine.arguments[3]
      } else {
         print("Give count of numbers to generate and how many times it is doubled with file to save results.")
         print("Example: ./SwiftListArrayComparison 1000 5 datafile.tsv")
         print("Exexutes the test with counts 1000, 2000, 4000, 8000, 16000")
         return
      }

      do {
         try? FileManager.default.removeItem(atPath: fileName!)
         FileManager.default.createFile(atPath: fileName!, contents: nil, attributes: nil)
         file = FileHandle(forWritingAtPath: fileName!)
         let data = "# of objects\tGenerate array ms\tGenerate list ms\tSpeed diff\t[Generate <Array>]\tAccess array ms\tAccess list ms\tSpeed diff\tBS Array\tBS List\tBS diff\t[Access <Array>]\n".data(using: .utf8)
         file!.write(data!)
         for _ in 1...timesToMultiply {
            try doTest(with: numberCount)
            numberCount = numberCount * 2
         }
         try file!.close()
      } catch {
         print("** Error in doing test: \(error)")
      }
      return
   }

   static private func doTest(with numberCount: Int) throws -> Void {
      idArray.removeAll()
      idArray.reserveCapacity(numberCount)
      for number in 0..<numberCount {
         idArray.append(number)
      }
      idArray.shuffle()

      var array: TestContainer = SortedArray()
      var list: TestContainer = SortedList()

      print("~ Filling container tests with \(numberCount) objects ~~")
      print("~~ Filling array ...")
      let fillArrayDuration = fillContainer(container: &array)
      print("~~ Filling list ...")
      let fillListDuration = fillContainer(container: &list)
      print("~~ Filling native array...")
      var nativeArray = [TestClass] ()
      let fillSwiftArrayDuration = fillNativeArray(array: &nativeArray)

      // To make access comparisons fair, sort this array too
      nativeArray.sort {
         $0.id < $1.id
      }

      assert(idArray.count == array.count)
      assert(idArray.count == list.count)
      assert(idArray.count == nativeArray.count)

      print("~ Accessing container tests ~~")
      print("~~ Accessing array...")
      let accessArrayDuration = accessContainer(container: array)
      print("~~ Accessing list...")
      let accessListDuration = accessContainer(container: list)
      print("~~ Accessing native array...")
      let accessSwiftArrayDuration = accessNativeArray(array: nativeArray)
      var diff1: String = "n/a\t"
      if fillListDuration > 0 && fillArrayDuration > 0 {
         diff1 = String(format: "%.1f\t", fillArrayDuration/fillListDuration)
      }
      var diff2: String = "n/a\t"
      if accessArrayDuration > 0 && accessListDuration > 0 {
         diff2 = String(format: "%.1f\t", accessListDuration/accessArrayDuration)
      }
      print("~~ Binary searching array...")
      let binarySearchArrayDuration = accessContainerBinarySearch(container: array)
      print("~~ Binary searching list...")
      let binarySearchListDuration = accessContainerBinarySearch(container: list)
      var diff3: String = "n/a\t"
      if binarySearchListDuration > 0 {
         diff3 = String(format: "%.1f\t", binarySearchListDuration / binarySearchArrayDuration)
      }
      let row: String = "\(numberCount)\t"
                        + String(format: "%.0f\t", fillArrayDuration)
                        + String(format: "%.0f\t", fillListDuration)
                        + diff1
                        + String(format: "%.0f\t", fillSwiftArrayDuration)
                        + String(format: "%.0f\t", accessArrayDuration)
                        + String(format: "%.0f\t", accessListDuration)
                        + diff2
                        + String(format: "%.0f\t", binarySearchArrayDuration)
                        + String(format: "%.0f\t", binarySearchListDuration)
                        + diff3
                        + String(format: "%.0f\n", accessSwiftArrayDuration)
      file?.write(row.data(using: .utf8)!)
   }

   static private func fillContainer(container: inout TestContainer) -> TimeInterval {
      let now = Date()

      for counter in 0..<idArray.count {
         let id = idArray[counter]
         var name = "Object "
         name += String(id)
         let object = TestClass(id: id, name: name, data: "data")
         container.add(object: object)
      }
      let duration = Date().timeIntervalSince(now)
      print("      Data generation finished, container has \(container.count) items.")
      print("      Generation took \(String(format: "%.3f", duration*1000)) ms")
      return duration * 1000
   }

   static private func accessContainer(container: TestContainer) -> TimeInterval {
      let now = Date()

      var sum = 0
      for id in idArray {
         let index = container.getIndex(of: id)
         assert(id == index)
         sum += index
      }
      print("      Sum of indexes: \(sum)")
      let duration = Date().timeIntervalSince(now)
      print("      Data access finished, container has \(container.count) items.")
      print("      Access took \(String(format: "%.3f", duration*1000)) ms")
      return duration * 1000
   }

   static private func accessContainerBinarySearch(container: TestContainer) -> TimeInterval {
      let now = Date()

      var sum = 0
      for id in idArray {
         let index = binarySearch(value: id, from: container, in: nil)
         assert(id == index)
         sum += index!
      }
      print("      Sum of indexes: \(sum)")
      let duration = Date().timeIntervalSince(now)
      print("      Binary search finished, container has \(container.count) items.")
      print("      Binary search \(String(format: "%.3f", duration*1000)) ms")
      return duration * 1000
   }

   static private func binarySearch(value: Int, from container: TestContainer, in range: Range<Int>? = nil) -> Int? {
      let range = range ?? 0..<container.count
      guard range.lowerBound < range.upperBound else {
         return nil
      }
      let size = range.upperBound - range.lowerBound
      let middle = range.lowerBound + size / 2
      let id = container.get(index: middle).id
      if id == value {
         return middle
      } else if id > value {
         return binarySearch(value: value, from: container, in: range.lowerBound..<middle)
      } else {
         return binarySearch(value: value, from: container, in: middle+1..<range.upperBound)
      }
   }

   static private func fillNativeArray(array: inout [TestClass]) -> TimeInterval {
      let now = Date()

      for counter in 0..<idArray.count {
         let id = idArray[counter]
         var name = "Object "
         name += String(id)
         let object = TestClass(id: id, name: name, data: "data")
         array.append(object)
      }
      let duration = Date().timeIntervalSince(now)
      print("      Data generation finished, array has \(array.count) items.")
      print("      Generation took \(String(format: "%.3f", duration*1000)) ms")
      return duration * 1000
   }

   static private func accessNativeArray(array: [TestClass]) -> TimeInterval {
      let now = Date()

      var sum = 0
      for id in idArray {
         let index = array.firstIndex(where: { $0.id == id } )
         assert(id == index)
         sum += index!
      }
      print("      Sum of indexes: \(sum)")
      let duration = Date().timeIntervalSince(now)
      print("      Data access finished, container has \(array.count) items.")
      print("      Access took \(String(format: "%.3f", duration*1000)) ms")
      return duration * 1000
   }

} // class
