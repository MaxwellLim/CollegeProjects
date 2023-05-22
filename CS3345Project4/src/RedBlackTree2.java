public class RedBlackTree2<E extends Comparable<E>>
    {
        static class Node<E extends Comparable<E>>
            {
                E element;
                Node<E> leftChild;
                Node<E> rightChild;
                Node<E> parent;
                boolean color;
            }

        public boolean insert(E element) throws NullPointerException
            {
                if (element == null)
                    {
                        throw new NullPointerException("The element passed in was null");
                    }

                //If the element already exists, return false.
                if (contains(element))
                    {
                        return false;
                    }

                //Create the node
                Node<E> node = new Node<E>();
                node.element = element;
                node.leftChild = null;
                node.rightChild = null;
                node.color = BLACK;

                //Insert recursively and rotate if necessary
                recursiveInsert(root, node);
                rotateTree(node);

                //Update the root location
                root = node;
                while (root.parent != null)
                    {
                        root = root.parent;
                    }

                return true;
            }

        private void recursiveInsert(Node<E> curNode, Node<E> node)
            {
                if (curNode == null)
                    {
                        curNode = node;
                        return;
                    }

                else if (curNode != null && node.element.compareTo(curNode.element) < 0)
                    {
                        if (curNode.leftChild != null)
                            {
                                recursiveInsert(curNode.leftChild, node);
                                return;
                            }
                        else
                            {
                                curNode.leftChild = node;
                            }
                    }
                else if (curNode != null)
                        {
                            if (curNode.rightChild != null)
                                {
                                    recursiveInsert(curNode.rightChild, node);
                                    return;
                                }
                            else
                                {
                                    curNode.rightChild = node;
                                }
                        }

                node.parent = curNode;
                node.color = RED;
            }

        private void rotateLeft(Node<E> node)
            {
                Node<E> newNode = node.rightChild;
                if (newNode != null)
                    {
                        node.rightChild = newNode.leftChild;
                        newNode.leftChild = node;
                        newNode.parent = node.parent;
                        node.parent = newNode;
                        if (newNode.parent != null && newNode.parent.leftChild == node)
                            {
                                newNode.parent.leftChild = newNode;
                            }
                        else if (newNode.parent != null)
                            {
                                newNode.parent.rightChild = newNode;
                            }
                    }
            }

        private void rotateRight(Node<E> node)
            {
                Node<E> newNode = node.leftChild;
                if (newNode != null)
                    {
                        node.leftChild = newNode.rightChild;
                        newNode.rightChild = node;
                        newNode.parent = node.parent;
                        node.parent = newNode;
                        if (newNode.parent != null && newNode.parent.leftChild == node)
                            {
                                newNode.parent.leftChild = newNode;
                            }
                        else if (newNode.parent != null)
                            {
                                newNode.parent.rightChild = newNode;
                            }
                    }
            }

        private void rotateTree(Node<E> node)
            {
                //If the node has no parent, it's the root
                if (node.parent == null)
                    {
                        node.color = BLACK;
                        return;
                    }

                Node<E> grandparent = node.parent.parent;
                Node<E> parent = node.parent;

                if (node.parent.color == BLACK)
                    {
                        //If the parent is black, red is valid
                        return;
                    }
                else if (grandparent != null)
                    {
                        if (grandparent.rightChild != node.parent)
                            {
                                //We have an uncle on the right
                                if (grandparent.rightChild != null && grandparent.rightChild.color == RED)
                                    {
                                        //The uncle is red
                                        node.parent.color = BLACK;
                                        grandparent.rightChild.color = BLACK;
                                        grandparent.color = RED;
                                        rotateTree(grandparent);
                                    }
                                else
                                    {
                                        //The uncle is black
                                        if (grandparent.leftChild != null && node == grandparent.leftChild.rightChild)
                                            {
                                                //Left-Right case
                                                rotateLeft(node.parent);
                                                rotateRight(grandparent);

                                                boolean temp = parent.color;
                                                parent.color = grandparent.color;
                                                grandparent.color = temp;
                                            }
                                        else if (grandparent.rightChild != null && node == grandparent.rightChild.leftChild)
                                            {
                                                //Right-Left case
                                                rotateRight(node.parent);
                                                rotateLeft(grandparent);

                                                boolean temp = parent.color;
                                                parent.color = grandparent.color;
                                                grandparent.color = temp;
                                            }
                                        else if (grandparent.leftChild != null && node == grandparent.leftChild.leftChild)
                                                {
                                                    //Left-Left case
                                                    rotateRight(grandparent);

                                                    boolean temp = parent.color;
                                                    parent.color = grandparent.color;
                                                    grandparent.color = temp;
                                                }
                                            else
                                                {
                                                    //Right-Right case
                                                    rotateLeft(grandparent);

                                                    boolean temp = parent.color;
                                                    parent.color = grandparent.color;
                                                    grandparent.color = temp;
                                                }
                                    }
                            }
                        else if (grandparent.leftChild != node.parent)
                            {
                                //We have an uncle on the left
                                if (grandparent.leftChild != null && grandparent.leftChild.color == RED)
                                    {
                                        node.parent.color = BLACK;
                                        grandparent.leftChild.color = BLACK;
                                        grandparent.color = RED;
                                        rotateTree(grandparent);
                                    }
                                else
                                    {
                                        //The uncle is black
                                        if (grandparent.leftChild != null && node == grandparent.leftChild.rightChild)
                                            {
                                                //Left-Right case
                                                rotateLeft(node.parent);
                                                rotateRight(grandparent);

                                                boolean temp = parent.color;
                                                parent.color = grandparent.color;
                                                grandparent.color = temp;
                                            }
                                        else if (grandparent.rightChild != null && node == grandparent.rightChild.leftChild)
                                            {
                                                //Right-Left case
                                                rotateRight(node.parent);
                                                rotateLeft(grandparent);

                                                boolean temp = parent.color;
                                                parent.color = grandparent.color;
                                                grandparent.color = temp;
                                            }
                                        else if (grandparent.leftChild != null && node == grandparent.leftChild.leftChild)
                                                {
                                                    //Left-Left case
                                                    rotateRight(grandparent);

                                                    boolean temp = parent.color;
                                                    parent.color = grandparent.color;
                                                    grandparent.color = temp;
                                                }
                                            else
                                                {
                                                    //Right-Right case
                                                    rotateLeft(grandparent);

                                                    boolean temp = parent.color;
                                                    parent.color = grandparent.color;
                                                    grandparent.color = temp;
                                                }
                                    }
                            }
                    }
            }

        public boolean contains(Comparable<E> object)
            {
                if (object == null)
                    {
                        return false;
                    }

                Node<E> curNode = root;
                while (curNode != null)
                    {
                        if (object.compareTo(curNode.element) < 0)
                            {
                                curNode = curNode.leftChild;
                            }
                        else if (object.compareTo(curNode.element) > 0)
                            {
                                curNode = curNode.rightChild;
                            }
                        else
                            {
                                return true;
                            }
                    }

                return false;
            }

        public String toString()
            {
                return preOrderTraversal(root);
            }

        private String preOrderTraversal(Node<E> curNode)
            {
                if (curNode == null)
                    {
                        return "";
                    }

                if (curNode.color == RED)
                    {
                        return "*" + curNode.element + " " + preOrderTraversal(curNode.leftChild) + preOrderTraversal(curNode.rightChild);
                    }

                return curNode.element + " " + preOrderTraversal(curNode.leftChild) + preOrderTraversal(curNode.rightChild);
            }

        private static boolean RED = false;
        private static boolean BLACK = true;
        private Node<E> root;
    }