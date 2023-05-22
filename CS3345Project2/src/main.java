import java.util.LinkedList;
import java.util.List;

public class main
    {
        public static void main(String[] args)
            {
                List<Integer> desc = new LinkedList<>();
                IDedLinkedList<MyItem> tester = new IDedLinkedList<>();
                for (int i = 10; i > 0; i--)
                    {
                        desc.add(i);
                        tester.insertAtFront(new MyItem(i,i,desc));
                    }
                for (int i = 1; i <= 10; i++)
                    {
                        System.out.println(tester.findID(i).printID());
                    }

                System.out.println(tester.findID(2).printID());
                System.out.println(tester.findID(4).printID());
                System.out.println(tester.findID(10).printID());

            }
    }
