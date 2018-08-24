public abstract class Entry {
	protected Entry parent;
    public abstract String getName();                               // 获取名字
    public abstract int getSize();                                  // 获取大小
    public Entry add(Entry entry) throws FileTreatmentException {   // 加入目录条目
        throw new FileTreatmentException();
    }
    public void printList() {                                       // 为一览加上前缀并显示目录条目一览
        printList("");
    }
    protected abstract void printList(String prefix);               // 为一览加上前缀
    public String toString() {                                      // 显示代表类的文字
        return getName() + " (" + getSize() + ")";
    }
    public String getFullName() {
    	StringBuffer fullname = new StringBuffer();
    	Entry entry = this;
    	do {
    		fullname.insert(0, "/" + entry.getName());
    		entry = entry.parent;
    	} while (entry != null);
    	return fullname.toString();
    }
}
