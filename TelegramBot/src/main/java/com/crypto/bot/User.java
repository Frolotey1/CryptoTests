package com.crypto.bot;

public class User {
    private long id;
    private String username;
    private int level;
    private int correctCount;
    private int wrongCount;

    public User(long id, String username) {
        this.id = id;
        this.username = username;
        this.level = 1;
    }

    public User() {}

    public long getId() { return id; }
    public void setId(long id) { this.id = id; }
    public String getUsername() { return username; }
    public void setUsername(String username) { this.username = username; }
    public int getLevel() { return level; }
    public void setLevel(int level) { this.level = level; }
    public int getCorrectCount() { return correctCount; }
    public void setCorrectCount(int correctCount) { this.correctCount = correctCount; }
    public int getWrongCount() { return wrongCount; }
    public void setWrongCount(int wrongCount) { this.wrongCount = wrongCount; }
    public void incrementCorrect() { correctCount++; }
    public void incrementWrong() { wrongCount++; }
}