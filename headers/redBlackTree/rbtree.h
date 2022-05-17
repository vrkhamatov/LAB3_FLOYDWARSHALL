#ifndef LAB_3_RBTREE_H
#define LAB_3_RBTREE_H


#include "../stack/stack.h"
#include "../iterator/iterator.h"
#include "../list/list.h"
#include "../pair/pair.h"

using namespace std;

enum class coloring { RED = 0, BLACK = 1 };

template <class T1, class T2>
class RBTree
{
private:

    class Node
    {
    private:
        Node* parent;
        Node* left;
        Node* right;

        T1* key;
        T2 data;

        coloring color;
    public:
        friend class RBTree;

        friend class RBTreeIterator;


        Node(const T1& key, const T2& data) : Node()
        {
            this->key = new T1[1];
            *this->key = key;
            this->data = data;
        }

        Node()
        {
            left = nullptr;
            right = nullptr;
            parent = nullptr;
            key = nullptr;
            color = coloring::RED;
        }

        ~Node()
        {
            if (key != nullptr)
                delete [] key;
        }
    };

    Node* root;

    Node* Nil;
public:
    int size;

    RBTree()
    {
        size = 0;
        Nil = new Node();
        Nil->color = coloring::BLACK;
        root = nullptr;
    }

    void LeftSwitch(Node* X)
    {
        Node* Y = X->right;

        Node* B = Y->left;

        X->right = B;

        if (B != Nil)
        {
            B->parent = X;
        }

        Node* P = X->parent;
        Y->parent = P;

        if (P == nullptr)
        {
            this->root = Y;
        }
        else if (X == P->left)
        {
            P->left = Y;
        }
        else
        {
            P->right = Y;
        }

        Y->left = X;
        X->parent = Y;
    }

    void RightSwitch(Node* X)
    {
        Node* Y = X->left;

        Node* B = Y->right;

        X->left = B;

        if (B != Nil)
        {
            B->parent = X;
        }

        Node* P = X->parent;
        Y->parent = P;

        if (P == nullptr)
        {
            this->root = Y;
        }
        else if (X == P->right)
        {
            P->right = Y;
        }
        else
        {
            P->left = Y;
        }

        Y->right = X;
        X->parent = Y;
    }

    Node* ParentNodeToInsert(T1 key)
    {
        Node* currNode = root;

        if (key == *currNode->key)
        {
            return Nil;
        }


        while (true)
        {
            if (key > *currNode->key)
            {
                if (currNode->right != Nil)
                {
                    if (*currNode->right->key == key)
                        return currNode;
                    currNode = currNode->right;
                }
                else
                    return currNode;
            }
            else
            {
                if (currNode->left != Nil)
                {
                    if (*currNode->left->key == key)
                        return currNode;
                    currNode = currNode->left;
                }
                else return currNode;
            }
        }
    }

    void Add(const T1& key, const T2& data)
    {
        if (root == nullptr)
        {
            size++;
            Node* newNode = new Node(key, data);

            root = newNode;
            root->color = coloring::BLACK;

            newNode->left = Nil;
            newNode->right = Nil;
        }
        else
        {
            Node* parentNode = ParentNodeToInsert(key);

            if (parentNode == Nil)
            {
                /*if (root->key == key)
                {
                    throw invalid_argument("Node does not exist.");
                } */
                root->data += data;
                return;
            }


            if (parentNode->left != Nil && *parentNode->left->key == key)
            {
                parentNode->left->data += data;
                return;

            }
            else if (parentNode->right != Nil && *parentNode->right->key == key)
            {
                parentNode->right->data += data;
                return;
            }

            Node* newNode = new Node(key, data);
            size++;

            if (key < *parentNode->key)
                parentNode->left = newNode;
            else
                parentNode->right = newNode;

            newNode->parent = parentNode;
            newNode->left = Nil;
            newNode->right = Nil;

            newNode->color = coloring::RED;

            FixInsert(newNode);
        }
    }



    void Insert(const T1& key, const T2& data)
    {
        if (root == nullptr)
        {
            size++;
            Node* newNode = new Node(key, data);

            root = newNode;
            root->color = coloring::BLACK;

            newNode->left = Nil;
            newNode->right = Nil;
        }
        else
        {
            Node* parentNode = ParentNodeToInsert(key);

            if (parentNode == Nil)
            {
                throw invalid_argument("Key already exists");
            }

            if (parentNode->left != Nil && *parentNode->left->key == key)
            {
                throw invalid_argument("Key already exists");

            }
            else if (parentNode->right != Nil && *parentNode->right->key == key)
            {
                throw invalid_argument("Key already exists");
            }

            size++;
            Node* newNode = new Node(key, data);

            if (key < *parentNode->key)
                parentNode->left = newNode;
            else
                parentNode->right = newNode;

            newNode->parent = parentNode;
            newNode->left = Nil;
            newNode->right = Nil;

            newNode->color = coloring::RED;

            FixInsert(newNode);
        }
    }

    void FixInsert(Node* newNode)
    {
        while (newNode->parent->color == coloring::RED)
        {
            Node* p = newNode->parent;
            Node* Gp = p->parent;

            if (p == Gp->left)
            {
                // Case I
                if (Gp->right->color == coloring::RED)
                {
                    Gp->left->color = coloring::BLACK;
                    Gp->right->color = coloring::BLACK;
                    Gp->color = coloring::RED;
                }
                else // Case II
                {
                    if (newNode == p->right)
                    {
                        newNode = p;
                        LeftSwitch(newNode);
                        p = newNode->parent;
                        Gp = p->parent;
                    }
                    // Case III
                    p->color = coloring::BLACK;
                    Gp->color = coloring::RED;
                    RightSwitch(Gp);
                }
            }
            else
            {
                // Case I
                if (Gp->left->color == coloring::RED)
                {
                    Gp->left->color = coloring::BLACK;
                    Gp->right->color = coloring::BLACK;
                    Gp->color = coloring::RED;
                    newNode = Gp;
                }
                else // Case II
                {
                    if (newNode == p->left)
                    {
                        newNode = p;
                        RightSwitch(newNode);
                        p = newNode->parent;
                        Gp = p->parent;
                    }

                    // Case III
                    p->color = coloring::BLACK;
                    Gp->color = coloring::RED;
                    LeftSwitch(Gp);
                }
            }

            if (newNode == root)
                break;
        }
        // Case IV
        root->color = coloring::BLACK;
    }

    void Delete(const T1& key)
    {
        Node* nodeToDelete = FindNode(key);

        if (nodeToDelete != Nil)
        {
            size--;
            coloring originalColor = nodeToDelete->color;

            Node* X = nullptr;

            if (nodeToDelete->left == Nil)
            {
                X = nodeToDelete->right;
                NodeTransplant(nodeToDelete, X);
            }
            else if (nodeToDelete->right == Nil)
            {
                X = nodeToDelete->left;
                NodeTransplant(nodeToDelete, X);
            }
            else
            {
                Node* Y = FindMinimum(nodeToDelete->right);

                originalColor = Y->color;
                X = Y->right;

                if (Y->parent == nodeToDelete)
                {
                    X->parent = Y;
                }
                else
                {
                    NodeTransplant(Y, Y->right);
                    Y->right = nodeToDelete->right;
                    Y->right->parent = Y;
                }

                NodeTransplant(nodeToDelete, Y);

                Y->color = originalColor;
                Y->left = nodeToDelete->left;
                Y->left->parent = Y;
                Y->color = nodeToDelete->color;
            }

            delete nodeToDelete;

            if (originalColor == coloring::BLACK)
            {
                FixDelete(X);
            }
        }
        else
        {
            throw invalid_argument("Node does not exist.");
        }
    }

    void FixDelete(Node* X)
    {
        Node* W;
        while (X != root && X->color == coloring::BLACK)
        {
            if (X == X->parent->left)
            {
                W = X->parent->right;
                if (W->color == coloring::RED)
                {
                    W->color = coloring::BLACK;
                    X->parent->color = coloring::RED;
                    LeftSwitch(X->parent);
                    W = X->parent->right;
                }

                if (W->left->color == coloring::BLACK && W->right->color == coloring::BLACK)
                {
                    W->color = coloring::RED;
                    X = X->parent;
                }
                else
                {
                    if (W->right->color == coloring::BLACK) {
                        W->left->color = coloring::BLACK;
                        W->color = coloring::RED;
                        RightSwitch(W);
                        W = X->parent->right;
                    }

                    W->color = X->parent->color;
                    X->parent->color = coloring::BLACK;
                    W->right->color = coloring::BLACK;
                    LeftSwitch(X->parent);
                    X = this->root;
                }
            }
            else
            {
                W = X->parent->left;
                if (W->color == coloring::RED) {
                    W->color = coloring::BLACK;
                    X->parent->color = coloring::RED;
                    RightSwitch(X->parent);
                    W = X->parent->left;
                }

                if (W->left->color == coloring::BLACK && W->right->color == coloring::BLACK)
                {
                    W->color = coloring::RED;
                    X = X->parent;
                }
                else
                {
                    if (W->left->color == coloring::BLACK)
                    {
                        W->right->color = coloring::BLACK;
                        W->color = coloring::RED;
                        LeftSwitch(W);
                        W = X->parent->left;
                    }

                    W->color = X->parent->color;
                    X->parent->color = coloring::BLACK;
                    W->left->color = coloring::BLACK;
                    RightSwitch(X->parent);
                    X = this->root;
                }
            }
        }
        X->color = coloring::BLACK;
    }

    Node* FindNode(const T1& key)
    {
        Node* currNode = root;

        while (currNode != Nil)
        {
            if (*currNode->key == key)
                return currNode;

            if (*currNode->key < key)
            {
                currNode = currNode->right;
            }
            else if (*currNode->key > key)
            {
                currNode = currNode->left;
            }
        }
        return Nil;
    }

    void NodeTransplant(Node* X, Node* Y)
    {
        if (X->parent == nullptr)
        {
            root = Y;
        }
        else if (X == X->parent->left)
        {
            X->parent->left = Y;
        }
        else
        {
            X->parent->right = Y;
        }
        Y->parent = X->parent;
    }

    Node* FindMinimum(Node* node)
    {
        while (node->left != Nil)
        {
            node = node->left;
        }
        return node;
    }

    T2 FindData(const T1& key)
    {
        Node* node = FindNode(key);
        if (node == Nil)
        {
            throw invalid_argument("Node does not exist.");
        }
        else
        {
            return node->data;
        }
    }

    T1 GetKey(Node* node)
    {
        return *node->key;
    }

    T2 GetData(Node* node)
    {
        return node->data;
    }

    ~RBTree()
    {
        size = 0;
        auto itr = create_iterator();

        while (itr->has_next())
        {
            Node* temp = itr->current;
            itr->next();
            delete temp;
        }
        delete itr;

        delete Nil;
    }

    class RBTreeIterator : public Iterator<Pair<T1, T2>>
    {
    public:
        friend class RBTree;

        Stack<Node*>* stack;

        Node* current;

        RBTreeIterator(Node* root)
        {
            current = root;
            stack = new Stack<Node*>();
        }

        ~RBTreeIterator()
        {
            delete stack;
        }

        bool has_next()
        {
            return current != nullptr;
        }

        Pair<T1, T2> next()
        {
            Node* temp = current;

            Pair<T1, T2> pair = makepair(*temp->key, temp->data);

            if (current->right->key != nullptr)
            {
                stack->push(current->right);
            }

            if (current->left->key != nullptr)
            {
                current = current->left;
            }
            else
            {
                if (!stack->empty())
                {
                    current = stack->top();
                    stack->pop();
                }
                else
                {
                    current = nullptr;
                }
            }

            return pair;
        }

    };

    RBTreeIterator* create_iterator()
    {
        return new RBTreeIterator(root);
    }

};

#endif //LAB_3_RBTREE_H
