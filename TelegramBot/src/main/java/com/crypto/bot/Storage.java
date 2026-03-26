package com.crypto.bot;

import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class Storage {
    private final Map<Long, User> users = new ConcurrentHashMap<>();

    public User getUser(long id) {
        return users.computeIfAbsent(id, k -> new User(k, "unknown"));
    }

    public void updateUser(User user) {
        users.put(user.getId(), user);
    }
}