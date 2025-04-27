Collecting workspace information```markdown
# k-D Tree and k-Nearest Neighbors (kNN) Classifier

## Description

This project provides C++ implementations of a k-D Tree data structure and a k-Nearest Neighbors (kNN) classifier algorithm built upon the k-D Tree. It includes functionality for building, manipulating, and traversing k-D Trees, as well as training a kNN model and making predictions on datasets. The project also includes a [`Dataset`](init/Dataset.hpp) class for basic data handling from CSV files like the included [init/mnist.csv](init/mnist.csv).

## Features

*   **k-D Tree Implementation ([`kDTree`](init/kDTree.hpp))**:
    *   Construction from point lists ([`kDTree::buildTree`](init/kDTree.hpp)).
    *   Insertion of individual points ([`kDTree::insert`](init/kDTree.hpp)).
    *   Removal of points ([`kDTree::remove`](init/kDTree.hpp)).
    *   Searching for points ([`kDTree::search`](init/kDTree.hpp)).
    *   Tree traversals: Inorder ([`kDTree::inorderTraversal`](init/kDTree.hpp)), Preorder ([`kDTree::preorderTraversal`](init/kDTree.hpp)), Postorder ([`kDTree::postorderTraversal`](init/kDTree.hpp)).
    *   Calculation of tree height ([`kDTree::height`](init/kDTree.hpp)), node count ([`kDTree::nodeCount`](init/kDTree.hpp)), and leaf count ([`kDTree::leafCount`](init/kDTree.hpp)).
    *   Nearest neighbor search ([`kDTree::nearestNeighbour`](init/kDTree.hpp)).
    *   k-Nearest neighbor search ([`kDTree::kNearestNeighbour`](init/kDTree.hpp)).
*   **kNN Classifier Implementation ([`kNN`](init/kDTree.hpp))**:
    *   Training the classifier with training data ([`kNN::fit`](init/kDTree.hpp)).
    *   Predicting labels for test data ([`kNN::predict`](init/kDTree.hpp)).
    *   Evaluating prediction accuracy ([`kNN::score`](init/kDTree.hpp)).
*   **Dataset Handling ([`Dataset`](init/Dataset.hpp))**:
    *   Loading data from CSV files ([`Dataset::loadFromCSV`](init/Dataset.hpp)).
    *   Basic data inspection (`printHead`, `printTail`, `getShape`, `columns`).
    *   Data extraction ([`Dataset::extract`](init/Dataset.hpp)).
    *   Splitting data into training and testing sets ([`train_test_split`](init/Dataset.hpp)).

## Data Structures

*   [`kDTreeNode`](init/kDTree.hpp): Represents a node in the k-D Tree, storing data point coordinates and an optional label.
*   [`kDTree`](init/kDTree.hpp): The main class for the k-D Tree, managing nodes and providing tree operations.
*   [`Dataset`](init/Dataset.hpp): A class to load and manage datasets, represented as a list of lists of integers.
*   [`kNN`](init/kDTree.hpp): The k-Nearest Neighbors classifier class.

## Files

*   [init/kDTree.hpp](init/kDTree.hpp): Header file containing declarations for `kDTreeNode`, `kDTree`, and `kNN` classes, along with helper function prototypes like [`copyNode`](init/kDTree.hpp).
*   [init/kDTree.cpp](init/kDTree.cpp): Implementation file for the methods of `kDTree` and `kNN`, and helper functions like [`mergeSort`](init/kDTree.hpp).
*   [init/Dataset.hpp](init/Dataset.hpp): Header file for the `Dataset` class and `train_test_split` function.
*   `init/Dataset.cpp` (Not provided): Assumed implementation file for the `Dataset` class methods.
*   [init/main.hpp](init/main.hpp): Common header file including standard libraries.
*   [init/main.cpp](init/main.cpp): Contains example usage and test cases (`tc1` through `tc9`) for the implemented classes.
*   [init/mnist.csv](init/mnist.csv): Sample dataset (MNIST handwritten digits).

## Usage Examples

The [init/main.cpp](init/main.cpp) file contains several test cases demonstrating how to use the `kDTree` and `kNN` classes.

**Example: Building and traversing a k-D Tree (`tc3` in [init/main.cpp](init/main.cpp))**
````cpp
// filepath: init/main.cpp
// ...existing code...
void tc3()
{
    kDTree tree(2); // Create a 2-dimensional k-D Tree
    vector<vector<int>> pointList = {{5, 6}, {2, 2}, {7, 3}, {2, 8}, {8, 7}, {8, 1}, {9, 4}, {3, 5}};
    tree.buildTree(pointList); // Build the tree from points
    tree.preorderTraversal(); // Print the tree using preorder traversal
}
// ...existing code...
````

**Example: Using the kNN classifier (`tc9` in [init/main.cpp](init/main.cpp))**
````cpp
// filepath: init/main.cpp
// ...existing code...
void tc9()
{
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv"); // Load data

    kNN knn; // Create a kNN classifier (default k=5)
    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, -1, 1, -1); // Extract features
    Dataset label = dataset.extract(0, -1, 0, 0); // Extract labels

    // Split data into training and testing sets
    train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);

    knn.fit(X_train, y_train); // Train the model
    Dataset y_pred = knn.predict(X_test); // Predict on the test set
    double accuracy = knn.score(y_test, y_pred); // Calculate accuracy
    std::cout << "Accuracy: " << accuracy << endl;
}
// ...existing code...
````

## Building and Running

You can compile the source files using a C++ compiler (like g++). Ensure all necessary `.cpp` files ([init/kDTree.cpp](init/kDTree.cpp), `Dataset.cpp`, [init/main.cpp](init/main.cpp)) are included in the compilation command.

Example compilation command (assuming `Dataset.cpp` exists):
```sh
g++ init/kDTree.cpp init/Dataset.cpp init/main.cpp -o main -std=c++11
```

Then, run the executable:
```sh
./main
```
*(Note: The `main` function in main.cpp currently calls `tc3()`. Modify it to run other test cases.)*
