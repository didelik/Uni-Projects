import java.lang.Math;

public class Rectangle {

    private int xmin, ymin, xmax, ymax;

    public Rectangle(int xmin, int ymin, int xmax, int ymax){
        this.xmin = xmin;
        this.ymin = ymin;
        this.xmax = xmax;
        this.ymax = ymax;
    }

    public int xmin() {
        return xmin;
    }

    public int ymin() {
        return ymin;
    }

    public int xmax() {
        return xmax;
    }

    public int ymax() {
        return ymax;
    }

    public boolean contains(Point p) {
        return xmin() <= p.x() && p.x() <= xmax() && ymin() <= p.y() && p.y() <= ymax();
    }

    public boolean intersects(Rectangle that) {
        boolean first_check = this.contains(new Point(that.xmin(), that.ymin())) || this.contains(new Point(that.xmin(), that.ymax())) || this.contains(new Point(that.xmax(), that.ymin())) || this.contains(new Point(that.xmax(), that.ymax()));
        boolean second_check = that.contains(new Point(xmin(), ymin())) || that.contains(new Point(xmin(), ymax())) || that.contains(new Point(xmax(), ymin())) || that.contains(new Point(xmax(), ymax()));

        boolean third_check = (that.xmin() < xmin() && that.xmax() > xmax()) || (that.ymin() < ymin() && that.ymax() > ymax());
        boolean fourth_check = (xmin() < that.xmin() && xmax() > that.xmax()) || (ymin() < that.ymin() && ymax() > that.ymax());

        System.out.println(first_check + " " + second_check + " " + third_check + " " + fourth_check );

        return first_check || second_check || (third_check && fourth_check);
    }

    public double distanceTo(Point p) {
        if(contains(p)) {
            return 0;
        }
        else if(xmin() < p.x() && p.x() < xmax()) {
            return Math.min(Math.abs(p.y() - ymin()),Math.abs(p.y() - ymax()));
        }
        else if(ymin() < p.y() && p.y() < ymax()) {
            return Math.min(Math.abs(p.x() - xmin()),Math.abs(p.x() - xmax()));
        }
        else {
            return Math.min(Math.min(p.distanceTo(new Point(xmin(), ymin())), p.distanceTo(new Point(xmin(), ymax()))), Math.min(p.distanceTo(new Point(xmax(), ymin())), p.distanceTo(new Point(xmax(), ymax()))));
        }
    }

    public int squareDistanceTo(Point p) {
        return (int)Math.pow(this.distanceTo(p), 2);
    }

    public String toString() {
        return "[" + xmin() + ", " + xmax() + "] x [" + ymin() + ", " + ymax() + "]";
    }
}
