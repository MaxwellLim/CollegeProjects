public class IDedLinkedList<AnyType extends IDedObject>
    {
        private class Node
            {
                AnyType data;
                Node next;
                public Node(AnyType x)
                    {
                        data=x;
                    }
                void setNext(Node x)
                    {
                        next=x;
                    }
                AnyType getData()
                    {
                        return data;
                    }
                int getDataID()
                    {
                        return data.getID();
                    }


            }
        private Node head;
        private int count;

        public IDedLinkedList()
            {
                head=null;
                count=0;
            }

        void makeEmpty()
            {
                head=null;
                count=0;
            }
        AnyType findID(int ID)
            {
                if(count==0)
                    {return null;}
                Node current=head;
                while(current != null)
                    {
                        if(current.getDataID()==ID)
                            {return current.data;}
                        current=current.next;
                    }
                return null;

            }
        boolean insertAtFront(AnyType x)
            {
                Node temp = new Node(x);
                if(count==0)
                    {
                        head=temp;
                        count++;
                        return true;
                    }
                if(findID(x.getID())!=null)
                    {return false;}
                temp.setNext(head);
                head=temp;
                count++;
                return true;

            }
        AnyType deleteFromFront()
            {
                if (count == 0)
                    {return null;}
                Node temp = head;
                head = temp.next;
                count--;
                return temp.data;

            }
        AnyType delete(int ID)
            {
                if(count==0)
                    {return null;}
                if(head.getDataID()==ID)
                    {return deleteFromFront();}
                Node current=head.next;
                Node prev=head;

                while(current != null)
                    {
                        if(current.getDataID()==ID)
                            {
                                count--;
                                prev.setNext(current.next);
                                return current.data;
                            }
                        prev=current;
                        current=current.next;
                    }
                return null;
            }
        int printTotal()
            {
                if(count==0)
                    {return -1;}
                int sum=0;
                Node current = head;
                while(current!=null)
                    {
                        sum+=current.getDataID();
                        current=current.next;
                    }
                return sum;
            }
    }
