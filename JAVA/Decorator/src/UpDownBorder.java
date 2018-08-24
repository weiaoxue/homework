
public class UpDownBorder extends Border {
	private char borderChar;
	public UpDownBorder(Display display, char ch) {
        super(display);
        this.borderChar = ch;
    }
    public int getColumns() {
        return display.getColumns();
    }
    public int getRows() {                      // 行数为被装饰物的行数加上上下边框的行数
        return 1 + display.getRows() + 1;
    }
    public String getRowText(int row) {         // 指定的那一行的字符串
        if (row == 0) {                                                 // 上边框
            return makeLine(borderChar, display.getColumns());
        } else if (row == display.getRows() + 1) {                      // 下边框
            return makeLine(borderChar, display.getColumns());
        } else {                                                        // 其他边框
            return display.getRowText(row - 1);
        }
    }
    private String makeLine(char ch, int count) {         // 生成一个重复count次字符ch的字符串 
        StringBuffer buf = new StringBuffer();
        for (int i = 0; i < count; i++) {
            buf.append(ch);
        }
        return buf.toString();
    }
}
