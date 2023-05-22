import java.io.File;
import java.io.PrintWriter;
import java.util.*;

public class Main
    {
        public static void main(String[] args)
            {


                Scanner in;
                //check for arguments and end if not correct
                if (args.length != 2)
                    {
                        System.out.print("Error Incorrect Arguments:" + Arrays.toString(args));
                        System.exit(0);

                    }
                try
                    {
                        //initializing in and out files
                        File input_file = new File(args[0]);
                        in = new Scanner(input_file);
                        File output_file = new File(args[1]);
                        PrintWriter out;
                        out = new PrintWriter(output_file);

                        //type parameter
                        String type = in.nextLine();
                        RedBlackTree RBT = null;

                        //initialing as string or integer RBT
                        if (type.equals("Integer"))
                            {
                                RBT = new RedBlackTree<Integer>();
                            }
                        else
                            {
                                if (type.equals("String"))
                                    {
                                        RBT = new RedBlackTree<String>();
                                    }
                                else//improper type used so print error message and end program
                                    {
                                        out.println("Only works for objects Integers and Strings");
                                        out.close();
                                        in.close();
                                        System.exit(0);
                                    }
                            }

                        boolean result = false;

                        while (in.hasNext())
                            {
                                //getting operation
                                String line = in.nextLine();

                                String[] operation = line.split(":");
                                //if operation requires an argument print error if it is not provided
                                if (operation.length == 1 && (operation[0].equals("Insert") || operation[0].equals("Contains")))
                                    {
                                        out.println("Error in Line: " + operation[0]);
                                        continue;
                                    }


                                switch (operation[0])
                                    {
                                        case "Insert":
                                            try
                                                {
                                                    if(type.equals("Integer"))
                                                        {
                                                            result = RBT.insert(Integer.parseInt(operation[1]));
                                                        }
                                                    else
                                                        {
                                                            result=RBT.insert(operation[1]);
                                                        }
                                                    out.println(result ? "True" : "False");
                                                } catch (Exception e)
                                                {
                                                    //wrong type given
                                                    out.println("Error in insert: IllegalArgumentException raised");
                                                }
                                            break;
                                        case "Contains":
                                            if(type.equals("Integer"))
                                                {
                                                    result = RBT.contains(Integer.parseInt(operation[1]));
                                                }
                                            else
                                                {
                                                    result=RBT.contains(operation[1]);
                                                }
                                            out.println(result ? "True" : "False");
                                            break;
                                        case "PrintTree":
                                            out.println(RBT.toString());
                                            break;
                                        default:
                                            out.println("Error in Line: " + operation[0]);

                                    }

                            }
                        in.close();
                        out.close();

                    } catch (Exception e)
                    {
                        System.out.println("Exception: " + e.getMessage());
                    }
            }
    }