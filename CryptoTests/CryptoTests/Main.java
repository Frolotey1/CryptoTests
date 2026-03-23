package com.crypto;

import com.crypto.bot.BotConfig;
import com.crypto.bot.CppBridge;
import com.crypto.bot.CryptoBot;
import com.crypto.bot.Storage;
import
org.telegram.telegrambots.meta.TelegramBotsApi;
import org.telegram.telegrambots.meta.exceptions.TelegramApiException;
import org.telegram.telegrambots.updatesreceivers.DefaultBotSession;

public class Main {
public static void main(String[] args) {
BotConfig config = new BotConfig();
Storage storage = new Storage();
CppBridge cppBridge = new CppBridge(config.getCppExecutablePath());
CryptoBot bot = new CryptoBot(config, storage, cppBridge);
try {
TelegramBotsApi botsApi = new TelegramBotsApi(DefaultBotSession.class);
botsApi.registerBot(bot);
System.out.println("Bot started!");
} catch (TelegramApiException e) {
e.printStackTrace();
}
}
}
