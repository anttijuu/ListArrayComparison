//
//  main.cpp
//  ListArrayComparison
//
//  Created by Antti Juustila on 14.9.2020.
//

#include <iostream>
#include <cstdlib>
#include <numeric>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>

#include "SortedArray.hpp"
#include "SortedList.hpp"

void doTestWith(int maxNumber, std::ofstream & file);
std::chrono::milliseconds fillContainer(const std::vector<int> & ids, TestContainer & container);
std::chrono::milliseconds accessContainer(const std::vector<int> & ids, const TestContainer & container);
std::chrono::milliseconds binarySearchContainer(const std::vector<int> &ids, const TestContainer & container);
int binarySearch(int value, const TestContainer & container, std::pair<int,int> range);
std::chrono::milliseconds fillVector(const std::vector<int> &ids, std::vector<TestClass> & container);
std::chrono::milliseconds accessVector(const std::vector<int> & ids, const std::vector<TestClass> & container);

// For sorting a std::vector
struct SortTestObjects {
   bool operator() (const TestClass & left, const TestClass & right) {
      return left.getId() < right.getId();
   }
};

int main(int argc, const char * argv[]) {
   // The count of numbers to generate. Each number is also accessed (searched) from
   // The container.
   int maxNumberValue = 1000;
   int timesToMultiply = 1;
   std::string fileName;
   // Initialization
   // Check for the command line parameter.
   try {
      if (argc == 4) {
         std::string arg1(argv[1]);
         maxNumberValue = std::stoi(arg1);
         if (maxNumberValue <= 2) {
            maxNumberValue = 1000;
         }
         std::string arg2(argv[2]);
         timesToMultiply = std::stoi(arg2);
         if (timesToMultiply < 1) {
            timesToMultiply = 1;
         }
         if (timesToMultiply > 5) {
            timesToMultiply = 5;
         }
         fileName = argv[3];
      }
   } catch (std::exception e) {
      std::cout << "Give count of numbers to generate and how many times it is doubled with file to save results." << std::endl;
      std::cout << "Example: ./ListArrayComparison 1000 5 datafile.tsv" << std::endl;
      std::cout << "Exexutes the test with counts 1000, 2000, 4000, 8000, 16000" << std::endl;
      return EXIT_FAILURE;
   }

   std::ofstream datafile(fileName, std::ios::trunc);

   datafile << "# of objects\tGenerate array ms\tGenerate list ms\tSpeed diff\t[Generate vector]\tAccess array ms\tAccess list ms\tSpeed diff\tBS Array\tBS List\tBS diff\t[Access vector]" << std::endl;
   for (int counter = 1; counter <= timesToMultiply; counter++) {
      doTestWith(maxNumberValue, datafile);
      maxNumberValue *= 2;
   }
   datafile.close();

   std::cout << " ~ Bye!" << std::endl;
   return EXIT_SUCCESS;
}

void doTestWith(int maxNumber, std::ofstream & file) {
   // Fill the id vector with object id's.
   std::vector<int> idVector(maxNumber);
   std::iota(idVector.begin(), idVector.end(), 0);
   std::random_device rd;
   std::mt19937 g(rd());
   // And put them to random order.
   std::shuffle(idVector.begin(), idVector.end(), g);

   // Here are the containers to test.
   SortedArray array;
   SortedList list;
   std::vector<TestClass> vectorContainer;

   std::cout << "~ Filling container tests with " << maxNumber << " objects"  << std::endl;
   file << maxNumber << "\t";

   std::cout << "~~ Filling array ..." << std::endl;
   std::chrono::milliseconds value1 = fillContainer(idVector, array);
   file << value1.count() << "\t";
   std::cout << "~~ Filling list ..." << std::endl;
   std::chrono::milliseconds value2 = fillContainer(idVector, list);
   file << value2.count() << "\t";
   if (value2.count() > 0) {
      file << value1.count() / value2.count() << "\t";
   } else {
      file << "n/a" << "\t";
   }
   std::cout << "~~ Filling vector ..." << std::endl;
   file << fillVector(idVector, vectorContainer).count() << "\t";
   // Sort vector since array and list are also sorted
   SortTestObjects sorter;
   std::sort(vectorContainer.begin(), vectorContainer.end(), sorter);

   std::cout << "~ Accessing container tests ~~" << std::endl;
   std::cout << "~~ Accessing array..." << std::endl;
   value1 = accessContainer(idVector, array);
   file << value1.count() << "\t";
   std::cout << "~~ Accessing list..." << std::endl;
   value2 = accessContainer(idVector, list);
   file << value2.count() << "\t";
   if (value1.count() > 0) {
      file << value2.count() / value1.count() << "\t";
   } else {
      file << "n/a" << "\t";
   }
   std::cout << "~~ Binary search array..." << std::endl;
   value1 = binarySearchContainer(idVector, array);
   file << value1.count() << "\t";
   std::cout << "~~ Binary search list..." << std::endl;
   value2 = binarySearchContainer(idVector, list);
   file << value2.count() << "\t";
   if (value1.count() > 0) {
      file << value2.count() / value1.count() << "\t";
   } else {
      file << "n/a" << "\t";
   }
   std::cout << "~~ Accessing vector..." << std::endl;
   file << accessVector(idVector, vectorContainer).count() << std::endl;
}

/**
 Fills the container with objects, using the ids as object ids.
 Operation is timed, time is printed out to see how long it took to put the objects
 into the container.
 Arrays take a long time since for each object, the array is reallocated and replaced
 by the new array. There is no granulanity here, so every time an object is added, the
 array is copied, data is moved and the new object is inserted (in order) to the array.
 @param ids The ids to use when generating test objects.
 @param container The container to put the objects into.
 */
std::chrono::milliseconds fillContainer(const std::vector<int> & ids, TestContainer & container) {
   std::chrono::system_clock::time_point started = std::chrono::system_clock::now();

   for (int counter = 0; counter < ids.size(); counter++) {
      int id = ids[counter];
      std::string name("Object ");
      name.append(std::to_string(id));
      TestClass object = TestClass(id, name.c_str(), "data");
      container.add(object);
   }
   std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
   std::cout << "      Data generation finished for " << container.getCount() << " elements" << std::endl;
   std::chrono::milliseconds timeValue = std::chrono::duration_cast<std::chrono::milliseconds>(now-started);
   std::cout << "      Generation took " << timeValue.count() << " ms" << std::endl;
   return timeValue;
}

/**
 The container is accessed. Basically for each id (which are unsorted) is searched for
 from the container.
 @param ids The object ids to search for from the container.
 @param container The container searched.
 */
std::chrono::milliseconds accessContainer(const std::vector<int> & ids, const TestContainer & container) {
   std::chrono::system_clock::time_point started = std::chrono::system_clock::now();

   int sum = 0;
   for (int counter = 0; counter < ids.size(); counter++) {
      int id = ids[counter];
      int index = container.getIndex(id);
      assert(id == index);
      sum += index;
   }
   std::cout << "      Sum of indexes: " << sum << std::endl;
   std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
   std::cout << "      Data access finished for " << container.getCount() << " elements" << std::endl;
   std::chrono::milliseconds timeValue = std::chrono::duration_cast<std::chrono::milliseconds>(now-started);
   std::cout << "      Access took " << timeValue.count() << " ms" << std::endl;
   return timeValue;
}

std::chrono::milliseconds binarySearchContainer(const std::vector<int> &ids, const TestContainer & container) {
   std::chrono::system_clock::time_point started = std::chrono::system_clock::now();

   int sum = 0;
   std::pair<int,int> range(-1,-1);
   for (int counter = 0; counter < ids.size(); counter++) {
      int id = ids[counter];
      int index = binarySearch(id, container, range);
      assert(id == index);
      sum += index;
   }
   std::cout << "      Sum of indexes: " << sum << std::endl;
   std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
   std::cout << "      Binary search finished for " << container.getCount() << " elements" << std::endl;
   std::chrono::milliseconds timeValue = std::chrono::duration_cast<std::chrono::milliseconds>(now-started);
   std::cout << "      Binary search took " << timeValue.count() << " ms" << std::endl;
   return timeValue;
}

int binarySearch(int value, const TestContainer & container, std::pair<int,int> range) {
   if (range.first < 0) {
      range.first = 0;
      range.second = container.getCount() - 1;
   }
   if (range.first > range.second) {
      return -1;
   }
   int size = range.second - range.first;
   int middle = range.first + size / 2;
   int id = container.get(middle)->getId();
   if (id == value) {
      return middle;
   } else if (id > value) {
      return binarySearch(value, container, std::pair<int,int>(range.first, middle-1));
   } else {
      return binarySearch(value, container, std::pair<int,int>(middle+1, range.second));
   }
}

std::chrono::milliseconds fillVector(const std::vector<int> &ids, std::vector<TestClass> & container) {
   std::chrono::system_clock::time_point started = std::chrono::system_clock::now();

   for (int counter = 0; counter < ids.size(); counter++) {
      int id = ids[counter];
      std::string name("Object ");
      name.append(std::to_string(id));
      TestClass object = TestClass(id, name.c_str(), "data");
      container.push_back(object);
   }
   std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
   std::cout << "      Data generation finished for " << container.size() << " elements" << std::endl;
   std::chrono::milliseconds timeValue = std::chrono::duration_cast<std::chrono::milliseconds>(now-started);
   std::cout << "      Generation took " << timeValue.count() << " ms" << std::endl;
   return timeValue;
}

struct SearchPredicate {
   int idToSearch;

   SearchPredicate(int id) {
      idToSearch = id;
   }

   bool operator () (const TestClass & toCompare) {
      return idToSearch == toCompare.getId();
   }
};

std::chrono::milliseconds accessVector(const std::vector<int> & ids, const std::vector<TestClass> & container) {
   std::chrono::system_clock::time_point started = std::chrono::system_clock::now();

   int sum = 0;
   for (int counter = 0; counter < ids.size(); counter++) {
      int id = ids[counter];
      auto location = std::find_if(container.begin(), container.end(), SearchPredicate(id));
      if (location != container.end()) {
         int index = std::distance(container.begin(), location);
         assert(id == index);
         sum += index;
      }
   }
   std::cout << "      Sum of indexes: " << sum << std::endl;
   std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
   std::cout << "      Data access finished for " << container.size() << " elements" << std::endl;
   std::chrono::milliseconds timeValue = std::chrono::duration_cast<std::chrono::milliseconds>(now-started);
   std::cout << "      Access took " << timeValue.count() << " ms" << std::endl;
   return timeValue;
}
