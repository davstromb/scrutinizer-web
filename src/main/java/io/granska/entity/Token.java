package io.granska.entity;

import java.util.List;

public class Token {

    public String token;

    public String tag;

    public boolean valid;

    public List<TokenError> errors;

    public Token() {}

    public Token(String token) {
        this.token = token;
    }
}
