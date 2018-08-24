import java.io.*;
import java.util.*;

public class FileProperties implements FileIO {
	Properties p;
	
	public FileProperties() {
		this.p = new Properties();
	}
	
	public void readFromFile(String filename) throws IOException {
		InputStream in = new FileInputStream(filename);
		p.load(in);
	}
	
    public void writeToFile(String filename) throws IOException {
    	OutputStream out = new FileOutputStream(filename);
    	p.store(out, "writen by FileProperties");
    }
    
    public void setValue(String key, String value) {
    	p.setProperty(key, value);
    }
    
    public String getValue(String key) {
    	return p.getProperty(key);
    }
}
