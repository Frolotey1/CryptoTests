package com.crypto.bot;

import org.telegram.telegrambots.bots.TelegramLongPollingBot;
import org.telegram.telegrambots.meta.api.methods.send.SendMessage;
import org.telegram.telegrambots.meta.api.objects.Update;
import org.telegram.telegrambots.meta.exceptions.TelegramApiException;

public class CryptoBot extends TelegramLongPollingBot {
    private BotConfig config;
    private Storage storage;
    private CppBridge bridge;

    public CryptoBot(BotConfig config, Storage storage, CppBridge bridge) {
        this.config = config;
        this.storage = storage;
        this.bridge = bridge;
    }

    @Override
    public void onUpdateReceived(Update update) {
        if (update.hasMessage() && update.getMessage().hasText()) {
            long chatId = update.getMessage().getChatId();
            String text = update.getMessage().getText();

            if (text.equals("/start")) {
                sendMessage(chatId, "Привет! Бот работает!");
            } else if (text.equals("/task")) {
                var task = bridge.generateTask("caesar", 1);
                sendMessage(chatId, "Задание: " + task.get("question").asText());
            } else {
                sendMessage(chatId, "Напишите /start или /task");
            }
        }
    }

    private void sendMessage(long chatId, String text) {
        SendMessage msg = new SendMessage();
        msg.setChatId(String.valueOf(chatId));
        msg.setText(text);
        try {
            execute(msg);
        } catch (TelegramApiException e) {
            System.out.println("Ошибка: " + e.getMessage());
        }
    }

    @Override
    public String getBotUsername() { return config.getBotUsername(); }

    @Override
    public String getBotToken() { return config.getBotToken(); }
}