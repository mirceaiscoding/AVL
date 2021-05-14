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

    /**
     * @brief Get the number of children of this node
     * 
     * @return number of children of this node
     */
    int getNumberOfChildren()
    {
        int nr = 0;
        if (rightChild != NULL)
        {
            nr++;
        }

        if (leftChild != NULL)
        {
            nr++;
        }

        return nr;
    }
};

class AVL
{

private:
    // The root of the AVL tree
    Node *root;

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

        // cout << "DEBUG: getBalanceValue returns " << heightOfLeftSubtree - heightOfRightSubtree << "\n";
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
        // cout << "DEBUG: leftRotation function called\n";

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
        // cout << "DEBUG: rightRotation function called\n";

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
        // cout << "DEBUG: rightLeftRotation function called\n";

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
        // cout << "DEBUG: leftRightRotation function called\n";
        Node *C = root;
        Node *A = C->getLeftChild();
        Node *B = A->getRightChild();

        A = leftRotate(A);
        C->setLeftChild(A);
        return rightRotate(C);
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
            // cout << "DEBUG: insert node here\n";
            return (new Node(value));
        }

        // Explanation of rotaions: https://cppsecrets.com/users/1039649505048495348575464115971151161149746979946105110/C00-AVL-Rotations.php

        if (value < currentNode->getValue())
        {
            // insert into left subtree
            // cout << "DEBUG: insert into left subtree\n";
            currentNode->setLeftChild(applyInsert(currentNode->getLeftChild(), value));

            // check if the node is out of balance after the insert
            // cout << "DEBUG: Checking node with value " << currentNode->getValue() << "\n";
            int currentNodeBalanceValue = getBalanceValue(*currentNode);

            if (max(currentNodeBalanceValue, -currentNodeBalanceValue) > 1)
            {
                // cout << "DEBUG: Left imbalance\n";
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
            // cout << "DEBUG: insert into right subtree\n";
            currentNode->setRightChild(applyInsert(currentNode->getRightChild(), value));

            // check if the node is out of balance after the insert
            // cout << "DEBUG: Checking node with value " << currentNode->getValue() << "\n";
            int currentNodeBalanceValue = getBalanceValue(*currentNode);

            if (max(currentNodeBalanceValue, -currentNodeBalanceValue) > 1)
            {
                // cout << "DEBUG: Right imbalance for node with value " << currentNode->getValue() << "\n";
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

    /**
     * @brief Recursive function to delete value from the subtree of root currentNode
     * 
     * @param currentNode the root of the subtree from which we are deleting
     * @param value the value we are deleting
     * @return new root of subtree
     */
    Node *applyDelete(Node *currentNode, int value)
    {

        // if the current node is null return it
        // end the recursion
        if (currentNode == NULL)
        {
            return currentNode;
        }

        if (value < currentNode->getValue())
        {
            // delete into left subtree
            // cout << "DEBUG: delete into left subtree\n";
            currentNode->setLeftChild(applyDelete(currentNode->getLeftChild(), value));
        }
        else
        {
            if (value > currentNode->getValue())
            {
                // delete into right subtree
                // cout << "DEBUG: delete into right subtree\n";
                currentNode->setRightChild(applyDelete(currentNode->getRightChild(), value));
            }
            else
            {
                // this node is the one to delete
                // cout << "DEBUG: Found the node to delete!\n";

                int numberOfChildrenCurrentNode = currentNode->getNumberOfChildren();

                if (numberOfChildrenCurrentNode == 0)
                {
                    // the node is a leaf so we can just delete it and stop the recursion
                    return NULL;
                }

                if (numberOfChildrenCurrentNode == 1)
                {
                    // the node has one child
                    Node *notNullChild;
                    if (currentNode->getLeftChild())
                    {
                        notNullChild = currentNode->getLeftChild();
                    }
                    if (currentNode->getRightChild())
                    {
                        notNullChild = currentNode->getRightChild();
                    }

                    // replace the node with the not null child
                    *currentNode = *notNullChild;
                }

                if (numberOfChildrenCurrentNode == 2)
                {
                    // the node has two children
                    // replace the node with its successor
                    int successorValue = successor(currentNode->getValue());
                    currentNode->setValue(successorValue);
                    Node *rightChildCurrentNode = currentNode->getRightChild();

                    // delete the successor from the subtree
                    // cout << "DEBUG: Delete successor" << successorValue << "\n";
                    currentNode->setRightChild(applyDelete(currentNode->getRightChild(), successorValue));
                }
            }
        }

        // Update the height of the node
        currentNode->setHeight(getUpdatedHeight(*currentNode));

        // Check if the node is out of balance
        // cout << "DEBUG: Checking node with value " << currentNode->getValue() << "\n";
        int currentNodeBalanceValue = getBalanceValue(*currentNode);
        if (max(currentNodeBalanceValue, -currentNodeBalanceValue) > 1)
        {
            // imbalance
            if (currentNodeBalanceValue > 1)
            {
                // left imbalance
                int leftNodeBalanceValue = getBalanceValue(*(currentNode->getLeftChild()));
                if (leftNodeBalanceValue >= 0)
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
            else
            {
                // right imbalance

                int rightNodeBalanceValue = getBalanceValue(*(currentNode->getRightChild()));
                if (rightNodeBalanceValue <= 0)
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

        return currentNode;
    }

public:
    /**
     * @brief Construct a new AVL object
     * 
     */
    AVL()
    {
        root = NULL;
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
     * @brief Function to insert a value into the AVL tree
     * 
     * @param value valute to insert
     */
    void insert(int value)
    {
        cout << "ACTION: inserting " << value << "\n";
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
     * @brief Function to delete a value from the AVL tree
     * 
     * @param value valute to delete
     */
    void deleteValue(int value)
    {
        cout << "ACTION: deleting " << value << "\n";
        if (find(value))
        {
            // Call the recursive funcion for root
            root = applyDelete(root, value);
        }
        else
        {
            cout << "ERROR: Value to delete is not in the AVL\n";
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
     * @brief Get the successor of a value
     * 
     * @param value value we search the successor for
     * @return the successor of value
     */
    int successor(int value)
    {
        try
        {
            Node *nodeToGetSuccessorFor = find(value);
            if (nodeToGetSuccessorFor == NULL)
            {
                throw 1;
            }
            Node *currentNode = nodeToGetSuccessorFor->getRightChild();
            if (currentNode == NULL)
            {
                throw 2;
            }
            while (currentNode->getLeftChild() != NULL)
            {
                currentNode = currentNode->getLeftChild();
            }
            return currentNode->getValue();
        }
        catch (int error)
        {
            if (error == 1)
            {
                cout << "ERROR 1: The value is not in the AVL!\n";
            }
            if (error == 2)
            {
                cout << "ERROR 2: The value has no right subtree!\n";
            }
            return -1;
        }
    }

    /**
     * @brief Get the predecessor of a value
     * 
     * @param value value we search the predecessor for
     * @return the predecessor of value
     */
    int predecessor(int value)
    {
        try
        {
            Node *nodeToGetPredecessorFor = find(value);
            if (nodeToGetPredecessorFor == NULL)
            {
                throw 1;
            }
            Node *currentNode = nodeToGetPredecessorFor->getLeftChild();
            if (currentNode == NULL)
            {
                throw 2;
            }
            while (currentNode->getRightChild() != NULL)
            {
                currentNode = currentNode->getRightChild();
            }
            return currentNode->getValue();
        }
        catch (int error)
        {
            if (error == 1)
            {
                cout << "ERROR 1: The value is not in the AVL!\n";
            }
            if (error == 2)
            {
                cout << "ERROR 2: The value has no left subtree!\n";
            }
            return -1;
        }
    }
};

int main()
{

    AVL avl;

    // test 1 - tests left rotation and find - works
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
    if (false)
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

    // test 7 - tests successor - works
    if (false)
    {
        cout << "--------------- test 7 ---------------\n";
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
        cout << "The successor of 3: " << avl.successor(3) << "\n";
        cout << "The successor of 4: " << avl.successor(4) << "\n";
        cout << "The successor of 5: " << avl.successor(5) << "\n";
        cout << "The successor of 6: " << avl.successor(6) << "\n";
        cout << "The successor of 12: " << avl.successor(12) << "\n";
    }

    // test 8 - tests predecessor - works
    if (false)
    {
        cout << "--------------- test 8 ---------------\n";
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
        cout << "The predecessor of 3: " << avl.predecessor(3) << "\n";
        cout << "The predecessor of 4: " << avl.predecessor(4) << "\n";
        cout << "The predecessor of 5: " << avl.predecessor(5) << "\n";
        cout << "The predecessor of 6: " << avl.predecessor(6) << "\n";
        cout << "The predecessor of 12: " << avl.predecessor(12) << "\n";
    }

    // test 9 - tests simple delete - works
    if (false)
    {
        cout << "--------------- test 9 ---------------\n";
        avl.insert(4);
        avl.insert(1);
        avl.insert(2);
        avl.deleteValue(2);
        avl.print();
    }

    // test 10 - tests delete - works
    if (true)
    {
        cout << "--------------- test 10 ---------------\n";
        avl.insert(4);
        avl.insert(1);
        avl.insert(12);
        avl.insert(13);
        avl.print();

        avl.deleteValue(12); // delete
        avl.print();

        avl.insert(3);
        avl.print();

        avl.deleteValue(13); // delete
        avl.print();

        avl.insert(2);
        avl.print();

        avl.deleteValue(4); // delete
        avl.print();

        avl.insert(5);
        avl.print();
    }
}
