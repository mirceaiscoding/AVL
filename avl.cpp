#include <iostream>
using namespace std;

/**
 * @brief Node for a AVL tree
 * 
 */
class Node
{

private:
    // Value of the node
    int value;

    // Height of the node (max lenght from this node to a leaf node)
    int height;

    // Pointer to left child node
    Node *leftChild;

    // Pointer to right child node
    Node *rightChild;

public:
    /**
     * @brief Construct a new Node object
     * 
     * @param value 
     */
    Node(int value)
    {
        this->value = value;
        height = 0;
        leftChild = NULL;
        rightChild = NULL;
    }

    /**
     * @brief Copy constructor
     * 
     * @param node 
     */
    Node(const Node &node)
    {
        value = node.value;
        height = node.height;
        leftChild = node.leftChild;
        rightChild = node.rightChild;
    }

    /**
     * @brief Destroy the Node object
     * 
     */
    ~Node()
    {

        // TODO: add destructor
    }

    /**
     * @brief Get the value
     * 
     * @return value of node 
     */
    int getValue()
    {
        return value;
    }

    /**
     * @brief Get the height
     * 
     * @return height of node 
     */
    int getHeight()
    {
        return height;
    }

    /**
     * @brief Get the left child node
     * 
     * @return pointer to left child node
     */
    Node *getLeftChild()
    {
        return leftChild;
    }

    /**
     * @brief Get the right child node
     * 
     * @return pointer to right child node
     */
    Node *getRightChild()
    {
        return rightChild;
    }

    /**
     * @brief Set the value
     * 
     * @param value value to set
     */
    void setValue(int value)
    {
        this->value = value;
    }

    /**
     * @brief Set the height
     * 
     * @param height height to set
     */
    void setHeight(int height)
    {
        this->height = height;
    }

    /**
     * @brief Set the left child
     * 
     * @param leftChild 
     */
    void setLeftChild(Node *leftChild)
    {
        this->leftChild = leftChild;
    }

    /**
     * @brief Set the right child
     * 
     * @param rightChild 
     */
    void setRightChild(Node *rightChild)
    {
        this->rightChild = rightChild;
    }

    /**
     * @brief Get the Balance Value of the object (height of right subtree - height of left subtree).
     * The node is balanced only if |balance value| <= 1
     * 
     * @return the balance value
     */
    int getBalanceValue(){
        
        int heightOfLeftSubtree = 0;
        int heightOfRightSubtree = 0;

        if (leftChild != NULL){
            heightOfLeftSubtree = leftChild->getHeight();
        }

        if (rightChild != NULL){
            heightOfRightSubtree = rightChild->getHeight();
        }

        return heightOfRightSubtree - heightOfLeftSubtree;

    }
};

class AVL
{

private:
    // The root of the AVL tree
    Node *root;

public:
    AVL()
    {
        root = NULL;
    }

    /**
     * @brief Get the root of the AVL tree
     * 
     * @return the root node
     */
    Node *getRoot()
    {
        return root;
    }

    /**
     * @brief Set the root of the AVL tree
     * 
     * @param root new root of AVL tree
     */
    void setRoot(Node *root)
    {
        this->root = root;
    }

    /**
     * @brief Function to insert a value into the AVL tree
     * 
     * @param value valute to insert
     */
    void insert(int value)
    {

        // Check if there is no root
        if (root == NULL)
        {
            root = new Node(value);
            return;
        }

        // Node used to find the correct place to insert
        Node *nodeToCheck = root;

        // Parent of the node to check
        Node *parentOfNodeToCheck = NULL;

        // The node that could be unbalanced after the insertion
        // (if all parent nodes have a balance of 0 than after the insert |balance| can't be more than 1)
        Node* possibleUnbalancedNode = NULL;

        // Search AVL until we find an empty space
        while (nodeToCheck != NULL)
        {
            if (nodeToCheck->getBalanceValue() != 0)
            {
                possibleUnbalancedNode = nodeToCheck;
            }

            // Update parent
            parentOfNodeToCheck = nodeToCheck;

            // Find the correct direction
            if (nodeToCheck->getValue() < value)
            {
                nodeToCheck = nodeToCheck->getLeftChild();
            }
            else
            {
                nodeToCheck = nodeToCheck->getRightChild();
            }
        }
    }
};

int main()
{

    AVL avl;
    avl.insert(1);
    avl.insert(2);
    
}
