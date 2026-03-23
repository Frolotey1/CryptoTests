package com.crypto.bot;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.SerializationFeature;

import java.io.File;
import java.io.IOException;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class Storage {
private final Map<Long, User> users = new ConcurrentHashMap<>();
private final ObjectMapper mapper = new ObjectMapper().enable(SerializationFeature.INDENT_OUTPUT);
private final File storageFile = new File("users.json");

public Storage() {
load();
Runtime.getRuntime().addShutdownHook(new Thread(this::save));
}

public User getUser(long id) {
return users.computeIfAbsent(id, k -> new User(k, "unknown"));
}

public void updateUser(User user) {
users.put(user.getId(), user);
}

public Map<Long, User> getAllUsers() {
return users;
}

private void load() {
if (storageFile.exists()) {
try {
Map<Long, User> loaded = mapper.readValue(storageFile,
mapper.getTypeFactory().constructMapType(Map.class, Long.class, User.class));
users.putAll(loaded);
} catch (IOException e) {
System.err.println("Failed to load users: " + e.getMessage());
}
}
}

private void save() {
try {
mapper.writeValue(storageFile, users);
} catch (IOException e) {
System.err.println("Failed to save users: " + e.getMessage());
}
}
}
