package com.crypto.bot;

import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.node.ObjectNode;

public class CppBridge {
    private final ObjectMapper mapper = new ObjectMapper();

    public CppBridge(String path) {}

    public JsonNode generateTask(String cipher, int level) {
        ObjectNode result = mapper.createObjectNode();
        result.put("question", "Расшифруйте: khoor");
        result.put("answer", "hello");
        return result;
    }
}