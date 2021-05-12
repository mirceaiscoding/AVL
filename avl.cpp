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
     * @brief Get the Updated Height of a node
     * 
     * @param node node we check heigh for
     * @return updated height of the node
     */
    int getUpdatedHeight(Node node)
    {
        int heightOfLeftSubtree = getHeight(node.getLeftChild());
        int heightOfRightSubtree = getHeight(node.getRightChild());
        return max(heightOfLeftSubtree, heightOfRightSubtree) + 1;
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

        cout << "DEBUG: getBalanceValue returns " << heightOfLeftSubtree - heightOfRightSubtree << "\n";
        return heightOfLeftSubtree - heightOfRightSubtree;
    }

    /**
     * @brief Left rotate the subtree
     * 
     *  A
     *   \
     *    B         - >         B
     *     \                   / \    
     *      C                 A   C       
     * 
     * @param root root of subtree
     * @return pointer to new root of subtree
     */
    Node *leftRotate(Node *root)
    {
        cout << "DEBUG: leftRotation function called\n";

        // check for null
        if (root == NULL)
        {
            return NULL;
        }

        Node *A = root;
        Node *B = A->getRightChild();

        // left rotate
        A->setRightChild(B->getLeftChild());
        B->setLeftChild(A);

        // update heights (lower levels first)
        if (B->getRightChild())
        {
            Node *C = B->getRightChild();
            C->setHeight(getUpdatedHeight(*C));
        }
        A->setHeight(getUpdatedHeight(*A));
        B->setHeight(getUpdatedHeight(*B));

        // B is now the new root of the subtree
        return B;
    }

    /**
     * @brief Right rotate the subtree
     * 
     *      C
     *     /
     *    B         - >       B
     *   /                   / \    
     *  A                   A   C       
     * 
     * @param root root of subtree
     * @return pointer to new root of subtree
     */
    Node *rightRotate(Node *root)
    {
        cout << "DEBUG: rightRotation function called\n";

        // check for null
        if (root == NULL)
        {
            return NULL;
        }

        Node *C = root;
        Node *B = C->getLeftChild();

        // right rotate
        C->setLeftChild(B->getRightChild());
        B->setRightChild(C);

        // update heights (lower levels first)
        if (B->getLeftChild())
        {
            Node *A = B->getLeftChild();
            A->setHeight(getUpdatedHeight(*A));
        }
        C->setHeight(getUpdatedHeight(*C));
        B->setHeight(getUpdatedHeight(*B));

        // B is now the new root of the subtree
        return B;
    }

    /**
     * @brief Right Left rotation
     * 
     * 1. Right rotation for C
     * 2. Left rotaion for A
     * 
     *  A
     *   \
     *    C 
     *   /         
     *  B
     * 
     * @param root root of subtree
     * @return pointer to new root of subtree
     */
    Node *rightLeftRotation(Node *root)
    {
        cout << "DEBUG: rightLeftRotation function called\n";

        Node *A = root;
        Node *C = A->getRightChild();
        Node *B = C->getLeftChild();

        C = rightRotate(C);
        A->setRightChild(C);
        return leftRotate(A);
    }

    /**
     * @brief Left Right rotation
     * 
     * 1. Left rotation for A
     * 2. Right rotation for C
     * 
     *    C
     *   /
     *  A 
     *   \        
     *    B
     * 
     * @param root root of subtree
     * @return pointer to new root of subtree
     */
    Node *leftRightRotation(Node *root)
    {
        cout << "DEBUG: leftRightRotation function called\n";
        Node *C = root;
        Node *A = C->getLeftChild();
        Node *B = A->getRightChild();

        A = leftRotate(A);
        C->setLeftChild(A);
        return rightRotate(C);
    }

    /**
     * @brief Find a value in the AVL tree
     * 
     * @param value the value we search
     * @return pointer to the node (null if it is not found)
     */
    Node *find(int value)
    {
        return applyFind(root, value);
    }

    /**
     * @brief Recursive function to find a value in the AVL tree
     * 
     * @param currentNode the root of the subtree into which we search
     * @param value the value we search
     * @return pointer to the node (null if it is not found)
     */
    Node *applyFind(Node *currentNode, int value)
    {
        if (currentNode == NULL)
        {
            return NULL;
        }

        if (value == currentNode->getValue())
        {
            return currentNode;
        }

        if (value < currentNode->getValue())
        {
            return applyFind(currentNode->getLeftChild(), value);
        }
        else
        {
            return applyFind(currentNode->getRightChild(), value);
        }
    }

    /**
     * @brief Print the values in the avl tree in ascending order
     * 
     */
    void print()
    {
        applyPrint(root);
        cout << "\n";
    }

    /**
     * @brief Recursive function to print values from the subtree of root currentNode
     * 
     * @param currentNode the root of the subtree we are printing
     */
    void applyPrint(Node *currentNode)
    {
        if (currentNode != NULL)
        {

            applyPrint(currentNode->getLeftChild()); // print lesser numbers

            cout << currentNode->getValue() << " "; // print this number

            applyPrint(currentNode->getRightChild()); // print greater numbers
        }
    }

    /**
     * @brief Function to insert a value into the AVL tree
     * 
     * @param value valute to insert
     */
    void insert(int value)
    {
        if (!find(value))
        {
            // Call the recursive funcion for root
            root = applyInsert(root, value);
        }
        else
        {
            cout << "ERROR: Duplicate value inserted \n";
        }
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
            cout << "DEBUG: insert node here\n";
            return (new Node(value));
        }

        // Explanation of rotaions: https://cppsecrets.com/users/1039649505048495348575464115971151161149746979946105110/C00-AVL-Rotations.php

        if (value < currentNode->getValue())
        {
            // insert into left subtree
            cout << "DEBUG: insert into left subtree\n";
            currentNode->setLeftChild(applyInsert(currentNode->getLeftChild(), value));

            // check if the node is out of balance after the insert
            cout << "DEBUG: Checking node with value " << currentNode->getValue() << "\n";
            int currentNodeBalanceValue = getBalanceValue(*currentNode);

            if (max(currentNodeBalanceValue, -currentNodeBalanceValue) > 1)
            {
                cout << "DEBUG: Left imbalance\n";
                if (value < currentNode->getLeftChild()->getValue())
                {
                    /**
                     *      C
                     *     /
                     *    B
                     *   /
                     *  A
                     */

                    // Right rotation
                    currentNode = rightRotate(currentNode);
                }
                else
                {
                    /**
                     *      C
                     *     /
                     *    B
                     *     \
                     *      A
                     */

                    // Left-Right rotation
                    currentNode = leftRightRotation(currentNode);
                }
            }
        }
        else
        {
            // insert into right subtree
            cout << "DEBUG: insert into right subtree\n";
            currentNode->setRightChild(applyInsert(currentNode->getRightChild(), value));

            // check if the node is out of balance after the insert
            cout << "DEBUG: Checking node with value " << currentNode->getValue() << "\n";
            int currentNodeBalanceValue = getBalanceValue(*currentNode);

            if (max(currentNodeBalanceValue, -currentNodeBalanceValue) > 1)
            {
                cout << "DEBUG: Right imbalance for node with value " << currentNode->getValue() << "\n";
                if (value > currentNode->getRightChild()->getValue())
                {
                    /**
                     *  A
                     *   \
                     *    B
                     *     \
                     *      C
                     */

                    // Left rotation
                    currentNode = leftRotate(currentNode);
                }
                else
                {
                    /**
                     *  A
                     *   \
                     *    B
                     *   /
                     *  C
                     */

                    // Right-Left rotation
                    currentNode = rightLeftRotation(currentNode);
                }
            }
        }

        // Update the height of the node
        currentNode->setHeight(getUpdatedHeight(*currentNode));

        return currentNode;
    }
};

int main()
{

    AVL avl;

    // test 1 - tests left rotation only - works
    if (false)
    {
        cout << "--------------- test 1 ---------------\n";
        avl.insert(1);
        if (avl.find(1))
        {
            cout << "1 apare in avl\n";
        }
        else
        {
            cout << "ERROR 1!\n";
        }
        avl.print();
        avl.insert(5);
        avl.print();
        if (avl.find(5))
        {
            cout << "5 apare in avl\n";
        }
        else
        {
            cout << "ERROR 5!\n";
        }
        avl.insert(7);
        if (avl.find(7))
        {
            cout << "7 apare in avl\n";
        }
        else
        {
            cout << "ERROR 7!\n";
        }
        if (avl.find(3) == NULL)
        {
            cout << "3 nu apare in avl\n";
        }
        else
        {
            cout << "ERROR 3!\n";
        }
        avl.print();
    }

    // test 2 - tests right rotation only - works
    if (false)
    {
        cout << "--------------- test 2 ---------------\n";
        avl.insert(5);

        avl.print();

        avl.insert(3);

        avl.print();

        avl.insert(1);

        avl.print();
    }

    // test 3 - tests right left rotation only - works
    if (false)
    {
        cout << "--------------- test 3 ---------------\n";
        avl.insert(1);

        avl.print();

        avl.insert(5);

        avl.print();

        avl.insert(3);

        avl.print();
    }

    // test 4 - tests left right rotation only - works
    if (false)
    {
        cout << "--------------- test 4 ---------------\n";
        avl.insert(5);

        avl.print();

        avl.insert(1);

        avl.print();

        avl.insert(3);

        avl.print();
    }

    // test 5 - tests insert (any kind of rotation) - works
    if (false)
    {
        cout << "--------------- test 5 ---------------\n";
        avl.insert(4);
        avl.insert(1);
        avl.insert(12);
        avl.insert(13);
        avl.insert(3);
        avl.insert(2);
        avl.insert(5);
        avl.print();
    }

    // test 6 - tests insert (any kind of rotation) with duplicate values - works
    if (true)
    {
        cout << "--------------- test 6 ---------------\n";
        avl.insert(4);
        avl.insert(1);
        avl.insert(12);
        avl.insert(13);
        avl.insert(12); // duplicate
        avl.insert(3);
        avl.insert(13); // duplicate
        avl.insert(2);
        avl.insert(4); // duplicate
        avl.insert(5);
        avl.print();
    }
}
