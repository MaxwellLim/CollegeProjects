import java.util.LinkedList;
import java.util.List;

public class MyItem implements IDedObject
    {
        private int itemID;
        private int itemPrice;
        private List<Integer> itemDescription;

        //constructors
        public MyItem(int ID,int price, List<Integer> desc)
            {
                itemID=ID;
                itemPrice=price;
                itemDescription=new LinkedList<>();
                itemDescription.addAll(desc);
            }

        @Override
        public int getID()
            {
                return itemID;
            }

        @Override
        public String printID()
            {
                String output;
                output=itemID+" "+itemPrice;
                for (Integer x:itemDescription)
                    {
                        output+=(" "+x);
                    }
                return output;
            }
    }
