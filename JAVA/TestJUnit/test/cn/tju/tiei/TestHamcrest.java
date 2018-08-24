package cn.tju.tiei;

import static org.junit.Assert.*;

import org.junit.Assert;
import org.junit.Test;
import static org.hamcrest.Matchers.*;

public class TestHamcrest {

	@Test
	public void test() {
		Assert.assertThat("abcdefg", allOf(startsWith("abc"), endsWith("efg")));
	}

}
