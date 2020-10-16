# Comparing Linked Lists and Arrays

This simple app creates a continuous array and a linked list. Both containers add the elements in *sorted order*. Creation of the containers are timed.

Then the app accesses  elements from both data structures in a simple linear way. Search starts from the beginning and compares if the item to search is found. Searches are timed. 

You can change the number of elements to generate using a command line argument when  you launch the app:

```
./SwiftListArrayComparison 1000 5 swift-data.tsv
```

This will run the comparison five times, first with 1000 numbers, then 2000, 4000, 8000 and finally 16000 numbers. Output will be saved to `swift-data.tsv` file you can open with any spreadsheet app to see the comparison data.

See the attached image of sample search numbers on my laptop. Compare those to yours.

The point of this exercise is to ponder why the different execution times with the different data structures. Note that the containers are not fully implemented, the focus is on 1) adding elements to container and 2) accessing elements from the container.

A binary search is also perfomed both on the array and the list. This enables you to compare the performance of the binary search with these two data structures.

![Sample image of execution times](SwiftListArrayComparison.png)


## How to build and run

You'll need a Mac, Swift compiler (Xcode) to get things running.

1. Install [Xcode](https://developer.apple.com/xcode/) if not yet installed.
1. git clone the repo to your local computer.
1. Build the app from command line: `xcodebuild -configuration Release`, run the binary providing the parameters from there.
1. Run the app from `./build/Release` subdirectory and see the results.

You can alternatively configure and build from Xcode:

1. Open the project file in Xcode 
1. Select Product > Scheme > Edit Scheme, Run scheme
1. Make sure to select **Release** and **disable any debugging** options from the scheme. Debug configuration make the app run slower and the performance numbers are not realistic!
1. Add Arguments in the scheme editor to change the number of objects generated.
1. Run the app and see the results.

## Who did this

(c) Antti Juustila 2020
INTERACT Research Group, University of Oulu, Finland

## License

License is MIT. See LICENSE for details.

