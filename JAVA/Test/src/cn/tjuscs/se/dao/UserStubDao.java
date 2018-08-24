package cn.tjuscs.se.dao;

import java.util.HashMap;
import java.util.Map;

import cn.tjuscs.se.model.User;

public class UserStubDao implements IUserDao {
	private Map<String, User> us = new HashMap<String, User>();
	
	public void add(User user) {
		us.put(user.getUsername(), user);
	}

	public User load(String username) {
		return us.get(username);
	}

	public void delete(String username) {
		us.remove(username);
	}

}
