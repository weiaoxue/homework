package cn.tjuscs.se.dao;

import cn.tjuscs.se.model.User;

public interface IUserDao {
	public void add(User user);
	public User load(String username);
	public void delete(String username);
}
