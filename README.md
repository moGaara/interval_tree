# Interval Tree

This repository contains the implementation of an Interval Tree data structure in C++. The Interval Tree is a type of binary search tree that efficiently stores intervals and supports various operations such as insertion, deletion, and searching for overlapping intervals.

## Code

The main code file is `main.cpp`, which contains the implementation of the Interval Tree and a sample usage scenario. The code defines the following classes:

### `range`

The `range` class represents an interval with a lower bound (`low`) and an upper bound (`high`).

### `Node`

The `Node` class represents a node in the Interval Tree. It contains a maximum value (`Max`), an array of ranges (`ranges`), and pointers to the left and right child nodes (`lchild` and `rchild`).

### `IntervalTree`

The `IntervalTree` class represents the Interval Tree data structure. It includes private data members and public member functions to perform operations on the tree, such as insertion, deletion, searching, and traversal. The class provides the following public member functions:

- `getNumberOfNodes()`: Returns the current number of nodes in the tree.
- `Rinsert()`: Inserts a new interval into the tree.
- `check_overlap()`: Checks if there is an overlap between two intervals.
- `interval_search()`: Searches for overlapping intervals and deletes them.
- `height()`: Returns the current height of the tree.
- `inpre()`: Returns the predecessor of a given node.
- `insucc()`: Returns the successor of a given node.
- `del()`: Deletes an interval from the tree.
- `Inorder()`: Performs an inorder traversal of the tree.
- `GetCurrentPosition()`: Returns the current position in the array of deleted nodes.
- `SetRoot()`: Sets the root node of the tree.
- `GetRoot()`: Returns the root node of the tree.

## Usage

To use the Interval Tree, you can create an instance of the `IntervalTree` class and perform various operations on it. The sample usage scenario in the `main()` function demonstrates how to create an Interval Tree, insert intervals, search for overlapping intervals, and delete them. You can modify the code to fit your specific requirements.

## Example

Here's an example of how to use the Interval Tree:

```cpp
#include <iostream>
#include "IntervalTree.h"

int main() {
    IntervalTree t;
    // Insert intervals into the tree
    t.Rinsert(t.GetRoot(), 17, 19);
    t.Rinsert(t.GetRoot(), 5, 11);
    t.Rinsert(t.GetRoot(), 22, 30);
    t.Rinsert(t.GetRoot(), 4, 8);
    t.Rinsert(t.GetRoot(), 15, 18);
    t.Rinsert(t.GetRoot(), 7, 10);
    t.Rinsert(t.GetRoot(), 3, 20);
    t.Rinsert(t.GetRoot(), 14, 21);

    // Search for overlapping intervals and delete them
    range target = {16, 25};
    t.interval_search(t.GetRoot(), target);

    // Perform other operations on the tree...

    return 0;
}
```
