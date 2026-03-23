package com.crypto.bot;

import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.TimeUnit;

public class CppBridge {
private final String executablePath;
private final ObjectMapper mapper = new ObjectMapper();

public CppBridge(String executablePath) {
this.executablePath = executablePath;
}

public JsonNode generateTask(String cipher, int level) throws Exception {
List<String> command = new ArrayList<>();
command.add(executablePath);
command.add("--mode=generate");
command.add("--cipher=" + cipher);
command.add("--level=" + level);
return runCommand(command);
}

private JsonNode runCommand(List<String> command) throws Exception {
ProcessBuilder pb = new ProcessBuilder(command);
pb.redirectErrorStream(true);
Process process = pb.start();
boolean finished = process.waitFor(5, TimeUnit.SECONDS);
if (!finished) {
process.destroyForcibly();
throw new RuntimeException("C++ process timed out");
}
int exitCode = process.exitValue();
if (exitCode != 0) {
throw new RuntimeException("C++ process exited with code " + exitCode);
}
try (BufferedReader reader = new
BufferedReader(new InputStreamReader(process.getInputStream()))) {
StringBuilder output = new StringBuilder();
String line;
while ((line = reader.readLine()) != null) {
output.append(line);
}
return mapper.readTree(output.toString());
}
}
}
