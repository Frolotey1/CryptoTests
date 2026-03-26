package com.crypto.bot;

import org.telegram.telegrambots.meta.TelegramBotsApi;
import org.telegram.telegrambots.meta.exceptions.TelegramApiException;
import org.telegram.telegrambots.updatesreceivers.DefaultBotSession;

public class Main {
    public static void main(String[] args) {
        System.out.println("Запуск бота...");

        try {
            BotConfig config = new BotConfig();
            Storage storage = new Storage();
            CppBridge bridge = new CppBridge(config.getCppExecutablePath());
            CryptoBot bot = new CryptoBot(config, storage, bridge);

            TelegramBotsApi api = new TelegramBotsApi(DefaultBotSession.class);
            api.registerBot(bot);

            System.out.println("✓ Бот запущен!");
            System.out.println("Имя: @" + config.getBotUsername());
            System.out.println("Напишите /start в Telegram");

        } catch (TelegramApiException e) {
            System.out.println("Ошибка: " + e.getMessage());
            System.out.println("Проверьте токен бота в BotConfig.java");
        }
    }
}