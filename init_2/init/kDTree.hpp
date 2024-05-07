#include "main.hpp"
#include "Dataset.hpp"
/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */
struct kDTreeNode
{
    int label;
    vector<int> data;
    kDTreeNode *left;
    kDTreeNode *right;
    kDTreeNode(vector<int> data, int label = 0, kDTreeNode *left = nullptr, kDTreeNode *right = nullptr)
    {
        this->label = label;
        this->data = data;
        this->left = left;
        this->right = right;
    }
    bool operator==(const kDTreeNode &b);
};
struct NodeDist
{
    kDTreeNode *node;
    double dist;
};
void merge(vector<vector<int>> &vec, vector<int> &label, int l, int m, int r, int axis);
void mergeSort(vector<vector<int>> &vec, vector<int> &label, int l, int r, int axis);
void insertionSort(vector<NodeDist> &distList);
void print_vector(vector<int> arr, int size);
kDTreeNode *copyNode(kDTreeNode *node);

class kDTree
{
private:
    int k;
    kDTreeNode *root;

public:
    kDTree(int k = 2) : k(k), root(nullptr) {}
    ~kDTree() { clear(); }
    const kDTree &operator=(const kDTree &other);
    kDTree(const kDTree &other) : k(other.k), root(copyNode(other.root)) {}

    void inorderTraversal() const;
    void preorderTraversal() const;
    void postorderTraversal() const;
    int height() const;
    int nodeCount() const;
    int leafCount() const;

    void insert(const vector<int> &point);
    void remove(const vector<int> &point);
    bool search(const vector<int> &point);
    void buildTree(const vector<vector<int>> &pointList);
    void buildTree(const vector<vector<int>> &pointList, vector<int> &label);
    void nearestNeighbour(const vector<int> &target, kDTreeNode *best);
    void kNearestNeighbour(const vector<int> &target, int k, vector<kDTreeNode *> &bestList);

    /// Support functions
    bool operator==(const kDTree &other) const;
    void inorderTraversalRec(kDTreeNode *node) const;
    void preorderTraversalRec(kDTreeNode *node) const;
    void postorderTraversalRec(kDTreeNode *node) const;
    void clear();
    void clearRec(kDTreeNode *node);
    int getHeight(kDTreeNode *node) const;
    int leafCountRec(kDTreeNode *node) const;
    int nodeCountRec(kDTreeNode *node) const;
    kDTreeNode *insertRec(kDTreeNode *node, const vector<int> &point, int depth);
    kDTreeNode *buildTreeRec(vector<vector<int>> &points, int start, int end, int depth);
    kDTreeNode *buildTreeRec(vector<vector<int>> &points, vector<int> &label, int start, int end, int depth);

    bool searchRec(kDTreeNode *node, const vector<int> &point, int depth);
    kDTreeNode *findMin(kDTreeNode *node, int axis, int depth);
    kDTreeNode *removeRec(kDTreeNode *node, const vector<int> &point, int depth);
    double distance(const vector<int> &a, const vector<int> &b);
    kDTreeNode *nearest(const vector<int> &data, kDTreeNode *cp1, kDTreeNode *cp2);
    kDTreeNode *NNRec(const vector<int> &target, kDTreeNode *node, int depth); // shitty recursion (I hate this)s
};

class kNN
{
private:
    int k;
    Dataset *X_train;
    Dataset *y_train;
    int numClasses;
    kDTree *tree;

public:
    kNN(int k = 5);
    ~kNN();
    void fit(Dataset &X_train, Dataset &y_train);
    Dataset predict(Dataset &X_test);
    double score(const Dataset &y_test, const Dataset &y_pred);
};

// Please add more or modify as needed
