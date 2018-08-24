
public class Main {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		for (int i = 0; i < 9; i++) {
			Triple triple = Triple.getInstance(i % 3);
			System.out.println(i + ":" + triple);
		}
	}

}
