package cn.tjuscs.se.service;

import cn.tjuscs.se.dao.*;
import cn.tjuscs.se.model.*;

public class UserService implements IUserService {

	private IUserDao userDao;

	public UserService(IUserDao userDao) {
		this.userDao = userDao;
	}

	public UserService() {
		// 通过Stub进行模拟，生成Map对象
		userDao = new UserStubDao();

		// 通过数据库连接，生成数据库DAO对象
		// userDao = new UserDao();

	}

	@Override
	public void add(User user) {
		if (load(user.getUsername()) != null)
			throw new UserException("用户名已经存在");
		userDao.add(user);
	}

	@Override
	public void delete(String username) {
		if (username == "superadmin")
			return;

		userDao.delete(username);
	}

	@Override
	public User load(String username) {
		// userDao.load("asd");
		userDao.delete("abc");
		// userDao.load(username);
		return userDao.load(username);
	}

	@Override
	public User login(String username, String password) {
		User u = load(username);
		if (u == null)
			throw new UserException("用户名不存在");
		if (!u.getPassword().equals(password))
			throw new UserException("用户密码不存在");
		return u;
	}

}