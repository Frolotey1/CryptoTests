package com.crypto.bot;

public class User {
private long id;
private String username;
private int level;
private int correctCount;
private int wrongCount;
private String currentTaskQuestion;
private String currentTaskAnswer;
private String currentCipher;

public User(long id, String username) {
this.id = id;
this.username = username;
this.level = 1;
this.correctCount = 0;
this.wrongCount = 0;
}

public long getId() { return id; }
public String getUsername() { return username; }
public int getLevel() { return level; }
public void setLevel(int level) { this.level = level; }
public int getCorrectCount() { return correctCount; }
public void incrementCorrect() { correctCount++; }
public void incrementWrong() { wrongCount++; }
public String getCurrentTaskQuestion() { return currentTaskQuestion; }
public void setCurrentTaskQuestion(String q) { currentTaskQuestion = q; }
public String getCurrentTaskAnswer() { return currentTaskAnswer; }
public void setCurrentTaskAnswer(String a) { currentTaskAnswer = a; }
public String getCurrentCipher() { return currentCipher; }
public void setCurrentCipher(String c) { currentCipher = c; }
}
