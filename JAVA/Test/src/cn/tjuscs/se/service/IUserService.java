package cn.tjuscs.se.service;

import cn.tjuscs.se.model.User;

public interface IUserService {
	public void add(User user);
	public void delete(String username);
	public User load(String username);
	public User login(String username, String password);
}
