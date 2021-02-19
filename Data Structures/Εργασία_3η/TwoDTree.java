public class TwoDTree {
    private TreeNode head;
    private int treesize;

    private class TreeNode {
        Point item;
        TreeNode l;
        TreeNode r;

        public TreeNode(Point data) {
            item = data;
            l = null;
            r = null;
        }
    }

    public TwoDTree() {
        treesize = 0;
        head = null;
    }

    public void insert(Point p) {
        TreeNode dot = new TreeNode(p);
        boolean controller = true;

        if(isEmpty()) {
            head = dot;
        }
        else {
            TreeNode pos = head;
            boolean check = true;

            while (check) {
                if (controller) {
                    if (dot.item.x() == pos.item.x() && dot.item.y() == pos.item.y()) {
                        error(1);

                    } else if (dot.item.x() < pos.item.x()) {
                        if (pos.l == null) {
                            pos.l = dot;
                            check = false;
                        }
                        else {
                            pos = pos.l;
                            controller = false;
                        }
                    } else if (dot.item.x() >= pos.item.x()) {
                        if (pos.r == null) {
                            pos.r = dot;
                            check = false;
                        }
                        else {
                            pos = pos.r;
                            controller = false;
                        }

                    }
                }

                else if (!controller) {
                    if (dot.item.x() == pos.item.x() && dot.item.y() == pos.item.y()) {
                        error(1);

                    } else if (dot.item.y() < pos.item.y()) {
                        if (pos.l == null) {
                            pos.l = dot;
                            check = false;
                        }
                        else {
                            pos = pos.l;
                            controller = true;
                        }
                    } else if (dot.item.y() >= pos.item.y()) {
                        if (pos.r == null) {
                            pos.r = dot;
                            check = false;
                        }
                        else {
                            pos = pos.r;
                            controller = true;
                        }

                    }
                }
            }

        }

        if(controller) {
            if(isEmpty()) {
                System.out.println(dot.item.toString() + " - Root");
            }
            else {
                System.out.println(dot.item.toString() + " - According to x coordinate");
            }
        }
        else {
            System.out.println(dot.item.toString() + " - According to y coordinate");
        }
        treesize +=1;
    }

    public boolean search(Point p) {
        TreeNode pos = head;

        boolean check = true;
        boolean controller = true;

        while (check) {
            if (controller) {
                if (p.x() == pos.item.x() && p.y() == pos.item.y()) {
                    System.out.println("Found in Tree");
                    check = false;

                } else if (p.x() < pos.item.x()) {
                    if (pos.l == null) {
                        System.out.println("Not in Tree");
                        return false;
                    }
                    else {
                        pos = pos.l;
                        controller = false;
                    }
                } else if (p.x() >= pos.item.x()) {
                    if (pos.r == null) {
                        System.out.println("Not in Tree");
                        return false;
                    }
                    else {
                        pos = pos.r;
                        controller = false;
                    }

                }
            }

            else if (!controller) {
                if (p.x() == pos.item.x() && p.y() == pos.item.y()) {
                    System.out.println("Found in Tree");
                    check = false;

                } else if (p.y() < pos.item.y()) {
                    if (pos.l == null) {
                        System.out.println("Not in Tree");
                        return false;
                    }
                    else {
                        pos = pos.l;
                        controller = true;
                    }
                } else if (p.y() >= pos.item.y()) {
                    if (pos.r == null) {
                        System.out.println("Not in Tree");
                        return false;
                    }
                    else {
                        pos = pos.r;
                        controller = true;
                    }

                }
            }
        }
        return true;
    }

    public Point nearestNeighbor(Point p) {
        if(size()==0) {
            return null;
        }
        else {
            return null;
        }
    }

    //public List<Point> rangeSearch(Rectangle rect) {

    //}

    public boolean isEmpty() {
        return size() == 0;
    }

    public int size() {
        return treesize;
    }

    public static void error(int code) {
        switch (code) {
            case 1:
                System.out.println("Error: Item already exists in Tree");
                System.exit(2);
            default:
                System.out.println("Error");
                System.exit(2);
        }
    }

    public static void main(String[] args) {
        TwoDTree tree = new TwoDTree();

        tree.insert(new Point(70,20));
        tree.insert(new Point(50,40));
        tree.insert(new Point(20,30));
        tree.insert(new Point(40,70));

        System.out.println(tree.size());
        System.out.println(tree.search(new Point(20,30)));
        System.out.println(tree.size());

    }
}
