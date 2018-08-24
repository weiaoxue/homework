package cn.tjuscs.se.service;

import static org.junit.Assert.*;

import org.easymock.EasyMock;
import org.junit.Test;

import cn.tjuscs.se.dao.IUserDao;
import cn.tjuscs.se.model.User;
import cn.tjuscs.se.util.EntitiesHelper;

public class TestEasyMockSingle {

	@Test
	public void testLoadMock() {
		//IUserDao ud = EasyMock.createMock(IUserDao.class);
		IUserDao ud = EasyMock.createStrictMock(IUserDao.class);
		User u = new User(1, "admin", "123", "管理员");
		
		ud.delete("abc");
		EasyMock.expectLastCall();
		EasyMock.expect(ud.load("admin")).andReturn(u);
		EasyMock.replay(ud);
		IUserService us = new UserService(ud);
		User tu = us.load("admin");
		EntitiesHelper.assertUser(tu, u);
		EasyMock.verify(ud);
	}

}
