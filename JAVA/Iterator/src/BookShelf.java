import java.util.*;

public class BookShelf {
	//private Book[] books;
	private ArrayList<Book> books;
    //private int last = 0;
    public BookShelf(int maxsize) {
        this.books = new ArrayList<Book>();
    }
    public Book getBookAt(int index) {
        return books.get(index);
    }
    public void appendBook(Book book) {
        this.books.add(book);
    }
    public int getLength() {
        return books.size();
    }
    public Iterator iterator() {
        return new BookShelfIterator(this);
    }
}
