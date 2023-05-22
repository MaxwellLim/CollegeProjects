public class RedBlackTree<E extends Comparable<E>>
    {
        private static boolean RED = false;
        private static boolean BLACK = true;

        static class Node<E extends Comparable<E>>
            {
                E element;
                Node<E> leftChild;
                Node<E> rightChild;
                Node<E> parent;
                boolean color;

                public Node(E e)
                    {
                        element = e;
                        rightChild = null;
                        leftChild = null;
                        parent = null;
                        color = RED;
                    }

                private int compareTo(Node<E> rhs)
                    {
                        return element.compareTo(rhs.element);
                    }
            }

        private Node<E> root;

        public RedBlackTree()
            {
                root = null;
            }

        boolean insert(E element)
            {
                //if element is null throw exception
                if (element == null)
                    {
                        throw new NullPointerException();
                    }
                //if empty insert at root and color black
                if (root == null)
                    {
                        root = new Node<>(element);
                        root.color = BLACK;
                        return true;
                    }

                Node<E> current = root;
                Node<E> newNode = new Node<>(element);
                //traversing the tree
                while (true)
                    {
                        //element already exists
                        if (current.element.equals(element))
                            {
                                return false;
                            }
                        //key is less than current
                        if (newNode.compareTo(current) < 0)
                            {
                                //item can be inserted
                                if (current.leftChild == null)
                                    {
                                        current.leftChild = newNode;
                                        newNode.parent = current;

                                        //rebalancing
                                        fixTree(current.leftChild);

                                        //updating the root
                                        root = newNode;
                                        while (root.parent != null)
                                            {
                                                root = root.parent;
                                            }
                                        return true;
                                    }
                                //need to go deeper
                                current = current.leftChild;
                            }
                        //key is greater than current
                        if (newNode.compareTo(current) > 0)
                            {
                                //item can be inserted
                                if (current.rightChild == null)
                                    {
                                        current.rightChild = newNode;
                                        newNode.parent = current;

                                        //rebalancing
                                        fixTree(current.rightChild);

                                        //updating the root
                                        root = newNode;
                                        while (root.parent != null)
                                            {
                                                root = root.parent;
                                            }
                                        return true;
                                    }
                                //we need to go deeper
                                current = current.rightChild;
                            }
                    }
            }

        private void fixTree(Node<E> origin)
            {
                //if root make sure it is black and update
                if (origin.parent == null)
                    {
                        origin.color = BLACK;
                        return;
                    }

                //ease of access variables
                Node<E> par = origin.parent;
                Node<E> grandpar = par.parent;
                Node<E> unc;

                //it the parent tis black no need to do anything
                if (par.color == BLACK)
                    {
                        return;
                    }

                //getting the uncle node
                if (grandpar.leftChild != null && grandpar.leftChild.equals(par))
                    {
                        unc = grandpar.rightChild;
                    }
                else
                    {
                        unc = grandpar.leftChild;
                    }

                //if uncle is red do recolor and rebalance around the grandparent node
                if (unc != null && unc.color == RED)
                    {
                        grandpar.color = RED;
                        unc.color = BLACK;
                        par.color = BLACK;
                        fixTree(grandpar);
                    }
                else
                    {
                        //node is right of grandparent
                        if (grandpar.rightChild == par)
                            {
                                //node is right of parent
                                if (par.rightChild == origin)
                                    {
                                        rotateLeft(grandpar);

                                        boolean temp = par.color;
                                        par.color = grandpar.color;
                                        grandpar.color = temp;

                                    }
                                else//node is left of parent
                                    {
                                        rotateRight(par);
                                        rotateLeft(grandpar);

                                        boolean temp = origin.color;
                                        origin.color = grandpar.color;
                                        grandpar.color = temp;
                                    }

                            }
                        else//node is left of grandparent
                            {
                                //node is left of parent
                                if (par.leftChild == origin)
                                    {
                                        rotateRight(grandpar);

                                        boolean temp = par.color;
                                        par.color = grandpar.color;
                                        grandpar.color = temp;
                                    }
                                else//node is right of parent
                                    {
                                        rotateLeft(par);
                                        rotateRight(grandpar);

                                        boolean temp = origin.color;
                                        origin.color = grandpar.color;
                                        grandpar.color = temp;
                                    }
                            }
                    }
            }

        private void rotateLeft(Node<E> origin)
            {
                //new origin
                Node<E> newOrigin = origin.rightChild;

                //changing pointers
                origin.rightChild = newOrigin.leftChild;
                newOrigin.leftChild = origin;
                newOrigin.parent = origin.parent;
                origin.parent = newOrigin;

                if (newOrigin.parent != null && newOrigin.parent.leftChild == origin)
                    {
                        newOrigin.parent.leftChild = newOrigin;
                    }
                else
                    {
                        if (newOrigin.parent != null)
                            {
                                newOrigin.parent.rightChild = newOrigin;
                            }
                    }

            }

        private void rotateRight(Node<E> origin)
            {
                //new origin
                Node<E> newOrigin = origin.leftChild;

                //changing pointers
                origin.leftChild = newOrigin.rightChild;
                newOrigin.rightChild = origin;
                newOrigin.parent = origin.parent;
                origin.parent = newOrigin;

                if (newOrigin.parent != null && newOrigin.parent.leftChild == origin)
                    {
                        newOrigin.parent.leftChild = newOrigin;
                    }
                else
                    {
                        if (newOrigin.parent != null)
                            {
                                newOrigin.parent.rightChild = newOrigin;
                            }
                    }

            }

        boolean contains(Comparable<E> object)
            {
                //tree is empty or check for null object
                if (root == null || object == null)
                    {
                        return false;
                    }

                //traversing the tree
                Node<E> current = root;
                while (current != null)
                    {
                        //element exists
                        if (object.compareTo(current.element) == 0)
                            {
                                return true;
                            }
                        //key is less than current
                        if (object.compareTo(current.element) < 0)
                            {
                                //need to go deeper
                                current = current.leftChild;
                            }
                        //key is greater than current
                        if (object.compareTo(current.element) > 0)
                            {
                                //we need to go deeper
                                current = current.rightChild;
                            }
                    }
                return false;
            }

        public String toString()
            {
                //calling recursive toString
                return toString(root);
            }

        private String toString(Node<E> object)
            {
                //base case
                if (object == null)
                    {
                        return "";
                    }

                //main case
                return (object.color == RED ? "*" : "") + object.element.toString() + " "
                        + toString(object.leftChild)
                        + toString(object.rightChild);
            }


    }
