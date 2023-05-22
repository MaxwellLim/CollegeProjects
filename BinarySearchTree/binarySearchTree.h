//
// Created by Maxwell Lim on 11/18/2019.
//

#ifndef BINARYSEARCHTREE_BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_BINARYSEARCHTREE_H

#include <vector>
#include <iostream>
#include <iomanip>
// forward declaration of the template class binarySearchTree
template<class DataType>
class binarySearchTree;

// treeNode class
template <class DataType>
class treeNode
    {
        DataType data;
        treeNode* parent;
        treeNode* left;
        treeNode* right;
    public:
        friend class binarySearchTree<DataType>;
        //constructor
        treeNode(DataType data);
        //class getters
        DataType& getData()
            { return data;}
        treeNode* getLeft()
            { return left;}
        treeNode* getRight()
            {return right;}
        treeNode* getParent()
            { return parent;}
        //class setters
        void setData(DataType &other)
            {data=other;}
        void setLeft(treeNode* other)
            {left=other;}
        void setRight(treeNode* other)
            {right=other;}
        void setParent(treeNode* other)
            {parent=other;}
        //make vals null
        void clearLeft()
            {left= nullptr;}
        void clearRight()
            {right= nullptr;}
        void clearParent()
            {parent= nullptr;}
        //overloaded operators
        bool operator<(treeNode &other) const
            {return this->data<other.data;}
        bool operator>(treeNode &other) const
            {return this->data>other.data;}
        bool operator<=(treeNode &other) const
            {return this->data<=other.data;}
        bool operator>=(treeNode &other) const
            {return this->data>=other.data;}
        bool operator==(treeNode &other) const
            {return this->data==other.data;}
        bool operator!=(treeNode &other) const
            {return this->data!=other.data;}
    };

// binarySearchTree class
template <class DataType>
class binarySearchTree
    {
        treeNode<DataType>* root;
        unsigned long int count;
        
        void deleteAll()
            {
                deleteAll(root);
                root= nullptr;
            }
        void deleteAll(treeNode<DataType>* node);
        void copy(treeNode<DataType>* node);
    public:
        //constructors
        binarySearchTree()
            {count=0;}
        binarySearchTree(const binarySearchTree &other)
            {
                this->deleteAll();
                this->copy(other.root);
            }
        //assignment operator
        binarySearchTree<DataType> & operator=(const binarySearchTree &other);
        
        //destructor
        virtual ~binarySearchTree()
            {deleteAll();}
        bool empty() const
            { return count==0;}
        std::size_t size() const
            { return count;}
        void print() const
            {print(root);}
        void print(treeNode<DataType>* node) const;
        void debug(std::ostream &out) const
            {debug(root,out);}
        void debug(treeNode<DataType>* node,std::ostream &out) const;
        bool find(const DataType &searchItem, void (*foundNode)(const DataType&));
        bool erase(const DataType &deleteItem);
        void insert(const DataType &newItem);
        void insert(const DataType &newItem, void (*duplicateItemFound)(DataType &existingItem, const DataType &newItem));
        void update(DataType &exsitingItem, const DataType &newItem);
        void traverse(void (*itemFound)(const DataType& foundItem)) const;
        void traverse(treeNode<DataType>* node, void (*itemFound)(const DataType& foundItem)) const;
        // Your binarySearchTree goes here
        // print to ostream
        void print(std::ostream &out) const;
        void print(treeNode<DataType>* node,std::ostream &out) const;
        // traverse preorder
        void traversePreOrder(void (*itemFound)(const DataType& foundItem)) const;
        void traversePreOrder(treeNode<DataType>* node,void (*itemFound)(const DataType& foundItem)) const;
        // traverse outorder
        void traverseOutOrder(void (*itemFound)(const DataType& foundItem)) const;
        void traverseOutOrder(treeNode<DataType>* node,void (*itemFound)(const DataType& foundItem)) const;
    };

template <class DataType>
treeNode<DataType>::treeNode(DataType data)
        :data(data), parent(nullptr), left(nullptr), right(nullptr)
    {}

template <class DataType>
void binarySearchTree<DataType>::deleteAll(treeNode<DataType>* node)
    {
        if (node != nullptr)
            {
                // delete all nodes to the left
                deleteAll(node->getLeft());
                node->clearLeft();
                
                // delete all nodes to the right
                deleteAll(node->getRight());
                node->clearRight();
                
                // delete the node now
                delete node;
                count--;
            }
    
    }
    
template <class DataType>
void binarySearchTree<DataType>::print(treeNode<DataType>* node) const
    {
        //inorder traversal print
        if(node != nullptr)
            {
                print(node->getLeft());
                std::cout << node->getData() << std::endl;
                print(node->getRight());
            }
    }
    
template <class DataType>
bool binarySearchTree<DataType>::find(const DataType &searchItem, void (*foundNode)(const DataType&))
    {
        bool found= false;
        treeNode<DataType>* current=root;
        //traversal
        while(current!= nullptr)
            {
                //found the object
                if(current->getData()==searchItem)
                    {
                        foundNode(current->getData());
                        found=true;
                        break;
                    }
                    //if object is less than current node go left
                if(searchItem<current->getData())
                    {
                        current=current->getLeft();
                        continue;
                    }
                    //if object is greater go right
                if(searchItem>current->getData())
                    {
                        current=current->getRight();
                        continue;
                    }
            }
        return found;
    }
    
template <class DataType>
bool binarySearchTree<DataType>::erase(const DataType &deleteItem)
    {
        bool found= false;
        treeNode<DataType>* current=root;
        //find element to be erased
        while(current!= nullptr)
            {
                //found the element to be erased
                if(current->getData()==deleteItem)
                    {
                        found=true;
                        break;
                    }
                    //if less than current go left
                if(deleteItem<current->getData())
                    {
                        current=current->getLeft();
                        continue;
                    }
                    //if greater than current go right
                if(deleteItem>current->getData())
                    {
                        current=current->getRight();
                        continue;
                    }
            }
        if(found)
            {
                treeNode<DataType>* parent=current->parent;
                //for leaf node
                if(current->getRight()== nullptr&&current->getLeft()== nullptr)
                    {
                        if(*(parent->getLeft())==*current)
                            {parent->clearLeft();}
                        else
                            {parent->clearRight();}
                        delete current;
                        count--;
                    }
                else//for non leaf node
                        {
                            
                            treeNode<DataType>* successor;
                            //for only left children
                            if(current->getRight()== nullptr)
                                {successor=current->getLeft();}
                            else
                                {//for having to find the successor
                                    successor=current->getRight();
                                    while(successor->getLeft()!= nullptr)
                                        {
                                            successor=successor->getLeft();
                                        }
                                }
                            successor->getParent()->setLeft(successor->getLeft());
                            successor->setRight(current->getRight());
                            successor->setLeft(current->getLeft());
                            if(parent->getLeft()==current)
                                {parent->setLeft(successor);}
                            else
                                {parent->setRight(successor);}
                            delete current;
                            count--;
                        }
            }
        return found;
    }

template <class DataType>
void binarySearchTree<DataType>::insert(const DataType &newItem)
    {
        treeNode<DataType>* temp=new treeNode<DataType>(newItem);
        treeNode<DataType>* current=root;
        if(count==0)
            {
                root=temp;
                count++;
            }
        while(current!= nullptr)
            {
                //for item already exists
                if(current->getData()==temp->getData())
                    {
                        current->setData(temp->getData());
                        return;
                    }
                    //if less than current
                if(newItem<current->getData())
                    {
                        //found the deepest part
                        if(current->getLeft()==nullptr)
                            {
                                current->setLeft(temp);
                                temp->setParent(current);
                                count++;
                                break;
                            }
                            //still need to go deeper
                        current=current->getLeft();
                        continue;
                    }
                    //if greater than current
                if(newItem>current->getData())
                    {
                        //found deepest
                        if(current->getRight()==nullptr)
                            {
                                current->setRight(temp);
                                temp->setParent(current);
                                count++;
                                break;
                            }
                            //still need to go deeper
                        current=current->getRight();
                        continue;
                    }
            }
    }

template <class DataType>
void binarySearchTree<DataType>::insert(const DataType &newItem, void (*duplicateItemFound)(DataType &existingItem, const DataType &newItem))
    {
        treeNode<DataType>* temp=new treeNode<DataType>(newItem);
        treeNode<DataType>* current=root;
        if(count==0)
            {
                root=temp;
                count++;
            }
        while(current!= nullptr)
            {
                //for duplicate
                if(*current==*temp)
                    {
                        duplicateItemFound(current->getData(),temp->getData());
                        return;
                    }
                //item less than current
                if(newItem<current->getData())
                    {
                        //founnd deepest
                        if(current->getLeft()==nullptr)
                            {
                                current->setLeft(temp);
                                temp->setParent(current);
                                count++;
                                break;
                            }
                            //still need to go deeper
                        current=current->getLeft();
                        continue;
                    }
                //if item greater than current
                if(newItem>current->getData())
                    {
                        //found deepest
                        if(current->getRight()==nullptr)
                            {
                                current->setRight(temp);
                                temp->setParent(current);
                                count++;
                                break;
                            }
                        //still need to go deeper
                        current=current->getRight();
                        continue;
                    }
            }
    }

template <class DataType>
void binarySearchTree<DataType>::update(DataType &exsitingItem, const DataType &newItem)
    {
        treeNode<DataType>* current=root;
        //binary search
        while(current!= nullptr)
            {
                if(current->getData()==exsitingItem)
                    {
                        current->setData(newItem);
                        return;
                    }
                if(exsitingItem<current->getData())
                    {
                        current=current->getLeft();
                        continue;
                    }
                if(exsitingItem>current->getData())
                    {
                        current=current->getRight();
                        continue;
                    }
            }
        
    }

template <class DataType>
void binarySearchTree<DataType>::traverse(void (*itemFound)(const DataType& foundItem)) const
    {
        traverse(root,*itemFound);
    }

template <class DataType>
void binarySearchTree<DataType>::traverse(treeNode<DataType>* node, void (*itemFound)(const DataType& foundItem)) const
    {
        if(node != nullptr)
            {
                traverse(node->getLeft(),itemFound);
                itemFound(node->getData());
                traverse(node->getRight(),itemFound);
            }
    }

template <class DataType>
void binarySearchTree<DataType>::debug(treeNode<DataType>* node,std::ostream &out) const
    {
        if(node!= nullptr)
        {
            debug(node->getRight(),out);
            out<<"Node-"<<node;
            out<<"Left Child-"<<node->getLeft();
            out<<"Right Child-"<<node->getRight();
            debug(node->getLeft(),out);
        }
    }

template <class DataType>
binarySearchTree<DataType>& binarySearchTree<DataType>::operator=(const binarySearchTree &other)
    {
        if(this->root==other.root)
            {
                return *this;
            }
        this->deleteAll();
        copy(other.root);
        return *this;
        
    }

template <class DataType>
void binarySearchTree<DataType>::copy(treeNode<DataType>* node)
    {
        if(node!= nullptr)
            {
                insert(node->getData());
                copy(node->getLeft());
                copy(node->getRight());
            }
    }

template <class DataType>
void binarySearchTree<DataType>::print(std::ostream &out) const
    {
        print(root,out);
    }
    
template <class DataType>
void binarySearchTree<DataType>::print(treeNode<DataType>* node,std::ostream &out) const
    {
        //inorder traversal print
        if(node != nullptr)
            {
                print(node->getLeft(),out);
                out << node->getData() << std::endl;
                print(node->getRight(),out);
            }
        
    }

template <class DataType>
void binarySearchTree<DataType>::traversePreOrder(void (*itemFound)(const DataType& foundItem)) const
    {
        traversePreOrder(root,itemFound);
    }

template <class DataType>
void binarySearchTree<DataType>::traversePreOrder(treeNode<DataType>* node,void (*itemFound)(const DataType& foundItem)) const
    {
        if(node != nullptr)
            {
                itemFound(node->getData());
                traversePreOrder(node->getLeft(),itemFound);
                traversePreOrder(node->getRight(),itemFound);
            }
    }

template <class DataType>
void binarySearchTree<DataType>::traverseOutOrder(void (*itemFound)(const DataType& foundItem)) const
    {
        traverseOutOrder(root,itemFound);
    }

template <class DataType>
void binarySearchTree<DataType>::traverseOutOrder(treeNode<DataType>* node,void (*itemFound)(const DataType& foundItem)) const
    {
        if(node != nullptr)
            {
                traverseOutOrder(node->getLeft(),itemFound);
                traverseOutOrder(node->getRight(),itemFound);
                itemFound(node->getData());
            }
    }
#endif //BINARYSEARCHTREE_BINARYSEARCHTREE_H
