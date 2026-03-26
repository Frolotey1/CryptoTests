package com.crypto.bot;

import org.telegram.telegrambots.bots.TelegramLongPollingBot;
import org.telegram.telegrambots.meta.api.methods.send.SendMessage;
import org.telegram.telegrambots.meta.api.objects.Update;
import org.telegram.telegrambots.meta.api.objects.replykeyboard.ReplyKeyboardMarkup;
import org.telegram.telegrambots.meta.api.objects.replykeyboard.buttons.KeyboardRow;
import org.telegram.telegrambots.meta.exceptions.TelegramApiException;

import java.util.ArrayList;
import java.util.List;

public class CryptoBot extends TelegramLongPollingBot {
private final BotConfig config;
private final Storage storage;
private final CppBridge cppBridge;

public CryptoBot(BotConfig config, Storage storage, CppBridge cppBridge) {
this.config = config;
this.storage = storage;
this.cppBridge = cppBridge;
}

@Override
public void onUpdateReceived(Update update) {
if (update.hasMessage() && update.getMessage().hasText()) {
long chatId = update.getMessage().getChatId();
String text = update.getMessage().getText();
User user = storage.getUser(chatId);
if (user.getUsername().equals("unknown") && update.getMessage().getFrom().getUserName() != null) {
user.setUsername(update.getMessage().getFrom().getUserName());
storage.updateUser(user);
}

if (text.equals("/start")) {
sendMessage(chatId, "Welcome to Crypto Trainer! Use /task to get a task, /level to change difficulty, /stats to see your progress.");
} else if (text.equals("/task")) {
handleTaskCommand(chatId, user);
} else if (text.equals("/level")) {
handleLevelCommand(chatId);
} else if (text.equals("/stats")) {
handleStatsCommand(chatId, user);
} else if (text.equals("/help")) {
sendMessage(chatId, "Commands: /start, /task, /level, /stats, /help");
} else if
(user.getCurrentTaskQuestion() != null) {
handleAnswer(chatId, text, user);
} else {
sendMessage(chatId, "Unknown command. Type /help for help.");
}
}
}

private void handleTaskCommand(long chatId, User user) {
try {
String[] ciphers = {"caesar", "atbash", "xor", "swap_nibbles", "cbc"};
String cipher = ciphers[(int)(Math.random() * ciphers.length)];
var json = cppBridge.generateTask(cipher, user.getLevel());
if (json.has("error")) {
sendMessage(chatId, "Error generating task: " + json.get("error").asText());
return;
}
String question = json.get("question").asText();
String answer = json.get("answer").asText();
user.setCurrentTaskQuestion(question);
user.setCurrentTaskAnswer(answer);
user.setCurrentCipher(cipher);
storage.updateUser(user);
sendMessage(chatId, "Your task: " + question);
} catch (Exception e) {
e.printStackTrace();
sendMessage(chatId, "Failed to generate task. Please try again.");
}
}

private void handleAnswer(long chatId, String answerText, User user) {
if (answerText.equalsIgnoreCase(user.getCurrentTaskAnswer())) {
user.incrementCorrect();
sendMessage(chatId, "Correct! Well done!");
if (user.getCorrectCount() % 5 == 0 && user.getLevel() < 3) {
user.setLevel(user.getLevel() + 1);
sendMessage(chatId, "Level up! Your new level is " + user.getLevel());
}
} else {
user.incrementWrong();
sendMessage(chatId, "Wrong! The correct answer was: " + user.getCurrentTaskAnswer());
}
user.setCurrentTaskQuestion(null);
user.setCurrentTaskAnswer(null);
user.setCurrentCipher(null);
storage.updateUser(user);
}

private void handleLevelCommand(long chatId) {
ReplyKeyboardMarkup keyboard = new ReplyKeyboardMarkup();
keyboard.setResizeKeyboard(true);
List<KeyboardRow> rows = new ArrayList<>();
KeyboardRow row = new KeyboardRow();
row.add("Level 1");
row.add("Level 2");
row.add("Level 3");
rows.add(row);
keyboard.setKeyboard(rows);
SendMessage message = new SendMessage();
message.setChatId(chatId);
message.setText("Choose your difficulty level:");
message.setReplyMarkup(keyboard);
try {
execute(message);
} catch (TelegramApiException e) {
e.printStackTrace();
}
}

private void handleStatsCommand(long chatId, User user) {
String stats = "📊 Your stats:\n"
+ "Level: " + user.getLevel() + "\n"
+ "Correct answers: " + user.getCorrectCount() + "\n"
+ "Wrong answers: " + user.getWrongCount();
sendMessage(chatId, stats);
}

private void sendMessage(long chatId, String text) {
SendMessage message = new SendMessage();
message.setChatId(chatId);
message.setText(text);
try {
execute(message);
} catch (TelegramApiException e) {
e.printStackTrace();
}
}

@Override
public String getBotUsername() {
return config.getBotUsername();
}

@Override
public String getBotToken() {
return config.getBotToken();
}
}
