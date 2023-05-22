import java.io.File;
import java.io.PrintWriter;
import java.util.*;

public class Main
    {
        public static void main(String[] args)
            {


                Scanner in;
                if (args.length != 2)
                    {
                        System.out.print("Error Incorrect Arguments:" + Arrays.toString(args));
                        System.exit(0);

                    }
                try
                    {
                        File input_file = new File(args[0]);
                        in = new Scanner(input_file);
                        File output_file = new File(args[1]);
                        PrintWriter out;
                        out = new PrintWriter(output_file);

                        LazyBinarySearchTree LBST = new LazyBinarySearchTree();


                        boolean result=false;

                        while (in.hasNext())
                            {
                                String line = in.nextLine();
                                String[] operation = line.split(":");
                                if (operation.length == 1 && (operation[0].equals("Insert") || operation[0].equals("Delete") || operation[0].equals("Contains")))
                                    {
                                        out.println("Error in Line: " + operation[0]);
                                        continue;
                                    }


                                switch (operation[0])
                                    {
                                        case "Insert":
                                            try
                                                {
                                                    result = LBST.insert(Integer.parseInt(operation[1]));
                                                    out.println(result ? "True" : "False");
                                                } catch (Exception e)
                                                {
                                                    out.println("Error in insert: IllegalArgumentException raised");
                                                }
                                            break;
                                        case "Delete":
                                            try
                                                {
                                                    result = LBST.delete(Integer.parseInt(operation[1]));
                                                    out.println(result ? "True" : "False");
                                                } catch (Exception e)
                                                {
                                                    out.println("Error in delete: IllegalArgumentException raised");
                                                }
                                            break;
                                        case "Contains":
                                            try
                                                {
                                                    result = LBST.contains(Integer.parseInt(operation[1]));
                                                    out.println(result ? "True" : "False");
                                                } catch (Exception e)
                                                {
                                                    out.println("Error in contains: IllegalArgumentException raised");
                                                }
                                            break;
                                        case "FindMin":
                                            out.println(LBST.findMin());
                                            break;
                                        case "FindMax":
                                            out.println(LBST.findMax());
                                            break;
                                        case "Size":
                                            out.println(LBST.size());
                                            break;
                                        case "PrintTree":
                                            out.println(LBST.toString());
                                            break;
                                        case "Height":
                                            out.println(LBST.height());
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