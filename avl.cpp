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
        height = 1;
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
        // Nothing
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
     * @brief Get the Height of the node
     * 
     * @param node pointer to target node
     * @return height of target node 
     */
    int getHeight(Node *node)
    {
        if (node == NULL)
        {
            return 0;
        }
        return node->getHeight();
    }

    /**
     * @brief Get the Balance Value of the object (height of left subtree - height of right subtree).
     * The node is balanced only if |balance value| <= 1
     * 
     * @return the balance value
     */

    int getBalanceValue(Node node)
    {
        int heightOfLeftSubtree = getHeight(node.getLeftChild());
        int heightOfRightSubtree = getHeight(node.getRightChild());

        return heightOfLeftSubtree - heightOfRightSubtree;
    }

    /**
     * @brief Function to insert a value into the AVL tree
     * 
     * @param value valute to insert
     */
    void insert(int value)
    {

    }

    /**
     * @brief Recursive function to insert value into the subtree of root currentNode
     * 
     * @param currentNode the root of the subtree into which we are inserting
     * @param value the value we are inserting
     * @return new root of subtree
     */
    Node *applyInsert(Node *currentNode, int value)
    {

        // if the current node is null we can insert here (the space is free)
        // end the recursion
        if (currentNode == NULL)
        {
            return (new Node(value));
        }

        // Explanation of rotaions: https://cppsecrets.com/users/1039649505048495348575464115971151161149746979946105110/C00-AVL-Rotations.php

        if (value < currentNode->getValue())
        {
            // insert into left subtree
            currentNode->setLeftChild(applyInsert(currentNode->getLeftChild(), value));

            // check if the node is out of balance after the insert
            int currentNodeBalanceValue = getBalanceValue(*currentNode);

            if (max(currentNodeBalanceValue, -currentNodeBalanceValue) > 1)
            {
                // TODO: fix balance
            }
        }
        else
        {
            // insert into right subtree
            currentNode->setRightChild(applyInsert(currentNode->getRightChild(), value));

            // check if the node is out of balance after the insert
            int currentNodeBalanceValue = getBalanceValue(*currentNode);

            if (max(currentNodeBalanceValue, -currentNodeBalanceValue) > 1)
            {
                // TODO: fix balance
            }            
        }

        // Update the height of the node (from bottom to top because of recursion)
        int heightOfLeftSubtree = getHeight(currentNode->getLeftChild());
        int heightOfRightSubtree = getHeight(currentNode->getRightChild());
        currentNode->setHeight(max(heightOfLeftSubtree, heightOfRightSubtree) + 1);

    }
};

int main()
{

    AVL avl;
}
