package unsw.slope;

import java.util.ArrayList;

public class Slope {
    private int start;
    private int end;
    private int gradient;

    public int getStart() {
        return start;
    }

    public ArrayList<Slope> findCrossed(Slope slope) {
        ArrayList<Slope> arrayList = new ArrayList<>();
        int start = slope.getStart();
        int end = slope.getEnd();
        if ( (start>= this.start && start <= this.end) || (end >= this.start && end <= this.end)) {
            arrayList.add(slope);
            arrayList.add(this);
        }
        return arrayList;
    }

    public int getGradient() {
        return gradient;
    }

    public Slope(int end, int start, int gradient) {
        this.gradient = gradient;
        this.start = start;
        this.end = end;
    }

    public int getEnd() {
        return end;
    }

    public double getHeight(double position) {
        return (position - start) * gradient;
    }

    public void modify(int angle, boolean isStart) {
        if (isStart) {
            start = angle;
        } else {
            end = angle;
        }
    }
}
