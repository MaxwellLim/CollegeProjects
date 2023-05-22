public class LazyBinarySearchTree
    {
        TreeNode root;
        int count;

        public LazyBinarySearchTree()
            {
                root = null;
                count = 0;
            }

        boolean insert(int key)
            {
                //check for invalid key
                if (key < 1 || key > 99)
                    {
                        throw new IllegalArgumentException();
                    }

                //if no previous elements exist
                if (count == 0)
                    {
                        root = new TreeNode(key);
                        count++;
                        return true;
                    }

                TreeNode current = root;
                //traversing the tree
                while (current != null)
                    {
                        //element already exists
                        if (current.key == key)
                            {
                                //element exist logically
                                if (!current.deleted)
                                    {
                                        return false;
                                    }
                                else
                                    {
                                        //element was lazily deleted
                                        current.deleted = false;
                                        count++;
                                        return true;
                                    }
                            }
                        //key is less than current
                        if (key < current.key)
                            {
                                //current has no left child
                                if (current.leftChild == null)
                                    {
                                        current.leftChild = new TreeNode(key);
                                        count++;
                                        return true;
                                    }
                                //need to go deeper
                                current = current.leftChild;
                            }
                        //key is greater than current
                        if (key > current.key)
                            {
                                //current has no right child
                                if (current.rightChild == null)
                                    {
                                        current.rightChild = new TreeNode(key);
                                        count++;
                                        return true;
                                    }
                                //we need to go deeper
                                current = current.rightChild;
                            }
                    }
                return false;
            }

        boolean delete(int key)
            {
                //check for invalid key
                if (key < 1 || key > 99)
                    {
                        throw new IllegalArgumentException();
                    }

                //empty tree
                if (count == 0)
                    {
                        return false;
                    }
                TreeNode current = root;
                //traversing the tree
                while (current != null)
                    {
                        //element to be deleted
                        if (current.key == key)
                            {
                                //element exists
                                if (!current.deleted)
                                    {
                                        current.deleted = true;
                                        return true;
                                    }
                                else
                                    {
                                        //element was lazily deleted
                                        return false;
                                    }
                            }
                        //key is less than current
                        if (key < current.key)
                            {
                                //need to go deeper
                                current = current.leftChild;
                            }
                        //key is greater than current
                        if (key > current.key)
                            {
                                //we need to go deeper
                                current = current.rightChild;
                            }
                    }
                return false;

            }

        int findMin()
            {
                int min = 0;
                //tree is empty
                if (count == 0)
                    {
                        return -1;
                    }
                TreeNode current = root;

                //loops to leftmost node
                while (current != null)
                    {
                        if (!current.deleted)
                            {
                                min = current.key;
                            }
                        current = current.leftChild;
                    }
                return min;
            }

        int findMax()
            {
                int max = 0;
                //tree is empty
                if (count == 0)
                    {
                        return -1;
                    }
                TreeNode current = root;

                //loops to rightmost node
                while (current != null)
                    {
                        if (!current.deleted)
                            {
                                max = current.key;
                            }
                        current = current.rightChild;
                    }
                return max;
            }

        boolean contains(int key)
            {
                //check for invalid key
                if (key < 1 || key > 99)
                    {
                        throw new IllegalArgumentException();
                    }

                if (count == 0)
                    {
                        return false;
                    }
                TreeNode current = root;
                //traversing the tree
                while (current != null)
                    {
                        //element exist
                        if (current.key == key)
                            {
                                return !current.deleted;
                            }
                        //key is less than current
                        if (key < current.key)
                            {
                                if (current.leftChild == null)
                                    {
                                        return false;
                                    }
                                //need to go deeper
                                current = current.leftChild;
                            }
                        //key is greater than current
                        if (key > current.key)
                            {
                                if (current.rightChild == null)
                                    {
                                        return false;
                                    }
                                //we need to go deeper
                                current = current.rightChild;
                            }
                    }
                return false;
            }


        public String toString()
            {
                return toString(root);
            }

        String toString(TreeNode current)
            {
                if (current == null)
                    {
                        return "";
                    }

                String temp = current.key + " ";
                if (current.deleted)
                    {
                        temp = "*" + temp;
                    }
                return temp + toString(current.leftChild) + toString(current.rightChild);
            }

        int height()
            {
                return height(root);
            }

        int height(TreeNode current)
            {
                if (current == null)
                    {
                        return -1;
                    }
                return 1 + Math.max(height(current.leftChild), height(current.rightChild));
            }


        int size()
            {
                return count;
            }

        private class TreeNode
            {
                int key;
                TreeNode leftChild;
                TreeNode rightChild;
                boolean deleted;

                private TreeNode(int key)
                    {
                        this.key = key;
                        deleted = false;
                        leftChild = null;
                        rightChild = null;
                    }

            }
    }
