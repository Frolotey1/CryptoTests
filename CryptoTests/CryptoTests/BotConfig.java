package com.crypto.bot;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

public class BotConfig {
private static final String PROPERTIES_FILE = "config.properties";
private String botToken;
private String botUsername;
private String cppExecutablePath;

public BotConfig() {
try (InputStream input = getClass().getClassLoader().getResourceAsStream(PROPERTIES_FILE)) {
Properties prop = new Properties();
if (input == null) {
throw new RuntimeException("Unable to find " + PROPERTIES_FILE);
}
prop.load(input);
botToken = prop.getProperty("bot.token");
botUsername = prop.getProperty("bot.username");
cppExecutablePath = prop.getProperty("cpp.executable.path");
} catch (IOException e) {
throw new RuntimeException("Failed to load config", e);
}
}

public String getBotToken() { return botToken; }
public String getBotUsername() { return botUsername; }
public String getCppExecutablePath() { return cppExecutablePath; }
}
