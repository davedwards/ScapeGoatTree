## Documentation

### ScapeGoatTree

This code implements a **Scapegoat Tree**, which is a type of self-balancing binary search tree (BST). Scapegoat trees maintain balance by occasionally rebuilding subtrees when they become too unbalanced. The balancing is controlled by a parameter `alpha`, which defines the maximum allowable ratio of the size of a node's subtree to the size of the whole tree. 

Let's break down the components of the code:

### 1. Class Definition

```cpp
template <typename T>
class ScapegoatTree {
```
- This defines a template class `ScapegoatTree`, which allows it to work with any data type `T`.

### 2. Private Members

```cpp
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        int size; // size of the subtree
        Node(T value) : data(value), left(nullptr), right(nullptr), size(1) {}
    };
```
- `Node`: A structure representing a node in the tree with data, pointers to left and right children, and size of the subtree rooted at this node.
- `root`: A pointer to the root node of the tree.
- `alpha`: A balance factor that determines how unbalanced a subtree can become before it needs to be rebuilt.
- `maxNodes`: The maximum number of nodes in the tree, which tracks the total number of insertions.

### 3. Helper Functions

- **Size Functions**:
  - `size(Node* node)`: Returns the size of the subtree rooted at `node`.
  - `updateSize(Node* node)`: Updates the size of a node based on its children.

- **Rotations**:
  - `rightRotate(Node* y)` and `leftRotate(Node* x)`: Perform right and left rotations on the nodes, respectively. These are common operations in self-balancing trees to maintain balance.

### 4. Insert Function

```cpp
Node* insert(Node* node, T value) {
```
- Standard binary search tree insertion is performed.
- After insertion, it checks if the size of the subtree exceeds `maxNodes * alpha`. If it does, it calls `rebuild(node)` to rebuild the subtree.

### 5. Rebuilding the Tree

```cpp
Node* rebuild(Node* node) {
```
- This function rebuilds the subtree rooted at `node` by:
  - Collecting the elements in sorted order using `storeInOrder(node, elements)`.
  - Building a balanced tree from these sorted elements using `buildTree(elements, 0, elements.size() - 1)`.

### 6. Deletion Function

```cpp
Node* deleteNode(Node* node, T value) {
```
- Standard BST deletion logic is used.
- After deletion, it checks if the size of the subtree falls below `maxNodes * alpha`. If it does, it also calls `rebuild(node)`.

### 7. Memory Management

```cpp
void clear(Node* node) {
```
- A recursive function to free the memory allocated for the nodes in the tree.

### 8. Public Interface

```cpp
public:
    ScapegoatTree(double alpha = 0.57) : root(nullptr), alpha(alpha), maxNodes(0) {}
```
- Constructor initializes the tree with a default `alpha` value of 0.57.

- **Public Methods**:
  - `insert(T value)`: Inserts a value into the tree.
  - `remove(T value)`: Removes a value from the tree.
  - `search(T value)`: Searches for a value in the tree.
  - `inOrder()`: Prints the elements of the tree in sorted order.

### 9. Main Function

```cpp
int main() {
```
- Creates an instance of `ScapegoatTree<int>`.
- Inserts several integers and performs operations such as searching and deleting nodes.
- Displays the in-order traversal of the tree to show the elements in sorted order.

### Summary
The Scapegoat Tree is a self-balancing binary search tree that maintains balance through the use of a rebuilding strategy based on a balance factor. This implementation allows for efficient insertions, deletions, and searches while ensuring that the tree remains balanced, thus maintaining an average time complexity of O(log n) for these operations.

