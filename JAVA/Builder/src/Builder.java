
public abstract class Builder {
	private boolean hasTitle = false;
	public void buildTitle(String title) {
		if (!hasTitle) {
			makeTitle(title);
		}
	}
	public void buildString(String str) {
		if (hasTitle) {
			makeString(str);
		}
	}
	public void buildItems(String[] items) {
		if (hasTitle) {
			makeItems(items);
		}
	}
	public void buildClose() {
		if (hasTitle) {
			close();
		}
	}
	public abstract void makeTitle(String title);
    public abstract void makeString(String str);
    public abstract void makeItems(String[] items);
    public abstract void close();
}
