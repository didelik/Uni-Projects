import java.lang.Math;

public class Point {
    private int x, y;

    public Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public int x() {
        return x;
    }

    public int y() {
        return y;
    }

    public double distanceTo(Point z) {
        return Math.sqrt(Math.pow(z.x() - this.x(), 2) + Math.pow(z.y() - this.y(), 2));
    }

    public int squareDistanceTo(Point z) {
        return (int)Math.pow(this.distanceTo(z), 2);
    }

    @Override
    public String toString(){
       return "("+x()+", "+y()+")";
    }
}
