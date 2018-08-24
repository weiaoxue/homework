package idcard;
import framework.*;
import java.util.*;

public class IDCardFactory extends Factory {
	//private List owners = new ArrayList();
	private int id = 1;
	private HashMap database = new HashMap();
    protected Product createProduct(String owner) {
        return new IDCard(owner, id++);
    }
    protected void registerProduct(Product product) {
        //owners.add(((IDCard)product).getOwner());
        IDCard card = (IDCard)product;
        database.put(card.getID(), card.getOwner());
    }
    public HashMap getDatabase() {
        return database;
    }
}
