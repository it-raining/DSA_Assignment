#include "kDTree.hpp"

/////////////////////////////kD-tree///////////////////////////////////
/* TODO: You can implement methods, functions that support your data structures here.
 * */
void merge(vector<vector<int>> &vec, int l, int m, int r, int axis)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<vector<int>> L(n1, vector<int>(vec[0].size()));
    vector<vector<int>> R(n2, vector<int>(vec[0].size()));

    for (i = 0; i < n1; i++)
        L[i] = vec[l + i];
    for (j = 0; j < n2; j++)
        R[j] = vec[m + 1 + j];
    i = 0; // Initial index of first subvector
    j = 0; // Initial index of second subvector
    k = l; // Initial index of middle subvector
    while (i < n1 && j < n2)
    {
        if (L[i][axis] <= R[j][axis])
        {
            vec[k] = L[i];
            i++;
        }
        else
        {
            vec[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        vec[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        vec[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<vector<int>> &vec, int l, int r, int axis)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(vec, l, m, axis);
        mergeSort(vec, m + 1, r, axis);

        merge(vec, l, m, r, axis);
    }
}

void insertionSort(vector<NodeDist> &distList)
{
    int i, j;
    NodeDist key;
    for (i = 1; i < distList.size(); i++)
    {
        key = distList[i];
        j = i - 1;
        while (j >= 0 && distList[j].dist > key.dist)
        {
            distList[j + 1] = distList[j];
            j = j - 1;
        }
        distList[j + 1] = key;
    }
}

/// @brief Prints the tree
/// @param
/// @param size
void print_vector(vector<int> arr, uint32_t size)
{
    cout << "(";
    for (int i = 0; i < size; ++i)
    {
        cout << (static_cast<int16_t>(i) ? "," : "") << arr[i];
    }
    cout << ")";
}
void kDTree::inorderTraversal() const
{
    inorderTraversalRec(this->root);
}
void kDTree::inorderTraversalRec(kDTreeNode *node) const
{
    static bool flag = true;
    if (!node)
        return;
    inorderTraversalRec(node->left);
    cout << (flag ? "" : " ");
    print_vector(node->data, k);
    flag = false;
    inorderTraversalRec(node->right);
}
void kDTree::preorderTraversal() const
{
    preorderTraversalRec(this->root);
}
void kDTree::preorderTraversalRec(kDTreeNode *node) const
{
    if (!node)
        return;
    cout << ((node->data == this->root->data) ? "" : " ");
    print_vector(node->data, k);
    preorderTraversalRec(node->left);
    preorderTraversalRec(node->right);
}
void kDTree::postorderTraversal() const
{
    postorderTraversalRec(this->root);
}
void kDTree::postorderTraversalRec(kDTreeNode *node) const
{
    if (!node)
        return;
    postorderTraversalRec(node->left);
    postorderTraversalRec(node->right);
    print_vector(node->data, k);
    cout << ((node->data == this->root->data) ? "" : " ");
}

/// @brief Operator for tree
/// @param other
/// @return
kDTreeNode *copyNode(kDTreeNode *node)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    kDTreeNode *newNode = new kDTreeNode(node->data, copyNode(node->left), copyNode(node->right));
    return newNode;
}
bool kDTreeNode::operator==(const kDTreeNode &b)
{
    if (this->data != b.data)
        return false;

    if ((this->left == nullptr && b.left != nullptr) || (this->left != nullptr && b.left == nullptr))
        return false;
    if (this->left != nullptr && !(*(this->left) == *(b.left)))
        return false;

    if ((this->right == nullptr && b.right != nullptr) || (this->right != nullptr && b.right == nullptr))
        return false;
    if (this->right != nullptr && !(*(this->right) == *(b.right)))
        return false;
    return true;
}

bool kDTree::operator==(const kDTree &other) const
{
    return *this->root == *other.root;
}
const kDTree &kDTree::operator=(const kDTree &other)
{
    if (!(this == &other))
    {
        clear();
        root = copyNode(other.root);
    }
    return *this;
}

/// @brief Clear the tree
/// @param node
void kDTree::clearRec(kDTreeNode *node)
{
    if (!node)
        return;
    clearRec(node->left);
    clearRec(node->right);
    node->data.clear();
    delete node;
}
void kDTree::clear()
{
    clearRec(root);
    root = nullptr;
}

int kDTree::nodeCount() const
{
    return nodeCountRec(this->root);
}
int kDTree::nodeCountRec(kDTreeNode *node) const
{
    if (!node)
    {
        return 0;
    }
    return 1 + nodeCountRec(node->left) + nodeCountRec(node->right);
}
int kDTree::leafCount() const
{
    return leafCountRec(this->root);
}
int kDTree::leafCountRec(kDTreeNode *node) const
{
    if (!node)
    {
        return 0;
    }
    if (!node->left && !node->right)
    {
        return 1;
    }
    return leafCountRec(node->left) + leafCountRec(node->right);
}
int kDTree::getHeight(kDTreeNode *node) const
{
    if (!node)
    {
        return 0;
    }
    return 1 + max(getHeight(node->left), getHeight(node->right));
}
int kDTree::height() const
{
    return getHeight(this->root);
}

void kDTree::insert(const vector<int> &point)
{
    if (point.size() != k)
    {
        return;
    }
    this->root = insertRec(this->root, point, 0);
}
kDTreeNode *kDTree::insertRec(kDTreeNode *node, const vector<int> &point, int depth)
{
    if (node == nullptr)
    {
        return new kDTreeNode(point);
    }
    int axis = depth % k;
    if (point[axis] < (node->data)[axis])
    {
        node->left = insertRec(node->left, point, depth + 1);
    }
    else
    {
        node->right = insertRec(node->right, point, depth + 1);
    }
    return node;
}
kDTreeNode *kDTree::buildTreeRec(vector<vector<int>> &points, int start, int end, int depth)
{
    if (start > end)
    {
        return nullptr;
    }
    int axis = depth % k;
    mergeSort(points, start, end, axis);

    int mid = start + (end - start) / 2;

    kDTreeNode *node = new kDTreeNode(points[mid]);

    node->left = buildTreeRec(points, start, mid - 1, depth + 1);
    node->right = buildTreeRec(points, mid + 1, end, depth + 1);
    return node;
}
void kDTree::buildTree(const vector<vector<int>> &pointList)
{
    vector<vector<int>> points = pointList;
    root = buildTreeRec(points, 0, points.size() - 1, 0);
}
bool kDTree::searchRec(kDTreeNode *node, const vector<int> &point, int depth)
{
    if (node == nullptr)
    {
        return false;
    }
    if (node->data == point)
    {
        return true;
    }

    int axis = depth % k;
    if (point[axis] == (node->data)[axis])
        return searchRec(node->left, point, depth + 1) || searchRec(node->right, point, depth + 1);
    if (point[axis] < (node->data)[axis])
    {
        return searchRec(node->left, point, depth + 1);
    }
    return searchRec(node->right, point, depth + 1);
}
bool kDTree::search(const vector<int> &point)
{
    if (point.size() != k)
    {
        return false;
    }
    return searchRec(root, point, 0);
}
void kDTree::remove(const vector<int> &point)
{
    removeRec(root, point, 0);
}
kDTreeNode *kDTree::removeRec(kDTreeNode *node, const vector<int> &point, int depth)
{
    if (!node)
        return nullptr;
    int axis = depth % k;
    if (node->data == point)
    {
        if (!node->right && !node->left)
        { // leaf node
            node->data.clear();
            delete node;
            return nullptr;
        }
        else
        {
            if (node->right)
            { // node has right child
                kDTreeNode *tmp = findMin(node->right, axis, depth);
                node->data = tmp->data;
                node->right = removeRec(node->right, tmp->data, depth + 1);
            }
            else
            { // node has only left child
                kDTreeNode *tmp = findMin(node->left, axis, depth);
                node->data = tmp->data;
                node->left = removeRec(node->left, tmp->data, depth + 1);
            }
        }
    }
    else
    {
        // Need to handle the case where the finding node is iddiot
        if (point[axis] < node->data[axis])
            node->left = removeRec(node->left, point, depth + 1);
        else
            node->right = removeRec(node->right, point, depth + 1);
    }

    return node;
}

kDTreeNode *kDTree::findMin(kDTreeNode *node, int axis, int depth)
{
    if (!node)
        return nullptr;
    if (axis == depth % k)
    {
        if (node->left)
            return findMin(node->left, axis, depth + 1);
        else
            return node;
    }
    kDTreeNode *leftMin = findMin(node->left, axis, depth + 1);
    kDTreeNode *rightMin = findMin(node->right, axis, depth + 1);
    if (rightMin && leftMin)
    {
        if (leftMin->data[axis] <= rightMin->data[axis])
        {
            return (node->data[axis] <= leftMin->data[axis]) ? node : leftMin;
        }
        else
            return (node->data[axis] <= rightMin->data[axis]) ? node : rightMin;
    }
    else if (leftMin)
    {
        return (node->data[axis] <= leftMin->data[axis]) ? node : leftMin;
    }
    else
        return (node->data[axis] <= rightMin->data[axis]) ? node : rightMin;
}

double kDTree::distance(const vector<int> &a, const vector<int> &b)
{
    double dist = 0;
    for (int i = 0; i < a.size(); i++)
    {
        dist += (a[i] - b[i]) * (a[i] - b[i]);
    }
    return (dist);
}
kDTreeNode *kDTree::nearest(kDTreeNode *node, kDTreeNode *cp1, kDTreeNode *cp2)
{
    if (!node)
        return nullptr;
    return (distance(node->data, cp1->data) <= distance(node->data, cp2->data))
               ? cp1
               : cp2;
}

kDTreeNode *kDTree::NNRec(const vector<int> &target, kDTreeNode *node, int depth)
{
    if (!node)
        return nullptr;

    kDTreeNode *next_node = nullptr;
    kDTreeNode *other_node = nullptr;
    int axis = depth % k;

    if (target[axis] < node->data[axis])
    {
        next_node = node->left;
        other_node = node->right;
    }
    else
    {
        next_node = node->right;
        other_node = node->left;
    }

    kDTreeNode *best = nearest(next_node, NNRec(target, next_node, depth + 1), node);
    if (this->distance(target, best->data) > (target[axis] - node->data[axis]) * (target[axis] - node->data[axis]))
    {
        best = nearest(other_node, NNRec(target, other_node, depth + 1), best);
    }
    return best;
}
void kDTree::nearestNeighbour(const vector<int> &target, kDTreeNode *best)
{
    best = NNRec(target, root, 0);
}

void kDTree::kNearestNeighbour(const vector<int> &target, int k, vector<kDTreeNode *> &bestList)
{
    kDTree *tmpTree = new kDTree(*this); // copy constructor
    for (int i = 0; tmpTree->root && i < k; i++)
    {
        kDTreeNode *best = tmpTree->NNRec(target, tmpTree->root, 0);
        if (best)
        {
            bestList.push_back(best);
            tmpTree->root = tmpTree->removeRec(tmpTree->root, best->data, 0);
        }
    }
    tmpTree->clear();
}

//////////////////////////kNN Classes//////////////////////////////////////

kNN::kNN(int k)
{
    this->k = k;
    X_train = 0;
    y_train = 0;
}

*/ Start research from 03.05.2024. Please work */
void kNN::fit(Dataset &X_train, Dataset &y_train) {
    
}