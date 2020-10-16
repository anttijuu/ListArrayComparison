# Comparing Linked Lists and Arrays

This two simple apps, implemented in both C++ and Swift, create a continuous array and a linked list. Both containers add the elements in *sorted order*. Creation of the containers are timed.

Then the app accesses  elements from both data structures in a simple linear way. Search starts from the beginning and compares if the item to search is found. Searches are timed. 

The point of this exercise is to ponder why the different execution times with the different data structures. 

Note that:

- the containers are not fully implemented, since the focus is on 1) adding elements to container and 2) accessing elements from the container.
- the array allocations both in C++ and Swift are trivial, allocating room only for *one* more data object. In a real implementation, array should have granulanity: several additional cells would be allocated so that next reallocation would happen only after inserting several new elements in the empty cells created during the previous allocation.
- Swift implementation "pretends" that the array behaves like C type arrays in C++ implementation. In reality, Swift arrays (like std::vector in C++) are able to extend the array if needed when new elements do not fit into the allocated space. This code here aims to show how "under the hood" allocation would happen as if using C type arrays. Swift does not support C style fixed size arrays so this was the only option.

See the cpp and swift subdirectories for instructions to build and run each of the apps.

Note also that for comparing execution speed, you need to build the *release* versions *without debug data* to get realistic performance metrics.

## Contributing

In case you find issues, please create an Issue in the project repository. Even better, then 

1. fork the project,
1. create a branch to your fork... 
1. where you fix the issue and ...
1. then provide a Pull request to this repo and...
1. I will review the pull request and if all is fine, merge it with the main branch.

## Who did this

(c) Antti Juustila 2020
INTERACT Research Group, University of Oulu, Finland

## License

License is MIT. See LICENSE for details.

