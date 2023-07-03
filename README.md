"# task-05---stl-israeljacob" 


# Container Selection in C++

## Explanation of Map and Vector Usage

In my C++ program, I utilized two different container types: `map` and `vector`. Here's why I chose each of them:

### Map Usage

At first, I opted to use a `map` container. The reason behind this choice is that I needed a container that could be efficiently searched multiple times. With a `map`, the search operation has a time complexity of logarithmic order, O(log(n)). This is because `map` is implemented using a binary tree, providing efficient search capabilities.

### Vector Usage

Afterwards, I decided to use a `vector` container. In this scenario, the search operation is performed only once, and the primary goal is to iterate over the entire container to print its contents. The decision to use a `vector` was based on its excellent performance in terms of running time and memory efficiency. As of today, `vector` is considered one of the most efficient container types in terms of both time and space complexity.

By utilizing a combination of `map` and `vector` containers, I was able to optimize the program's search and print operations, ensuring both efficiency and effectiveness.

