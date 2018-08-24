import java.util.*;

public class RandomCountDisplay extends CountDisplay {
	private Random random = new Random();
	public RandomCountDisplay(DisplayImpl impl) {
        super(impl);
    }
	public void randomDisplay(int times) {
		int t = random.nextInt(times);
		//System.out.println(t);
		multiDisplay(t);
	}
}
