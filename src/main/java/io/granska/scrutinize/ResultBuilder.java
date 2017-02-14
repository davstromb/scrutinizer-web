package io.granska.scrutinize;

import java.util.Arrays;

/**
 * Created by david on 12/02/17.
 */
public class ResultBuilder {

    private ScrutResult scrutResult;

    public ResultBuilder() {
        this.scrutResult = new ScrutResult();
    }

    public static ResultBuilder builder() {
        return new ResultBuilder();
    }

    public ResultBuilder withInput(String[] tokens) {
        this.scrutResult.input = inputString(tokens);
        this.scrutResult.tokens = Arrays.asList(tokens);
        this.scrutResult.hash = this.scrutResult.input.hashCode();
        return this;
    }

    public ScrutResult build() {
        return this.scrutResult;
    }

    private static String inputString(String[] tokens) {
        StringBuilder sb = new StringBuilder();
        for(String token : tokens) {
            sb.append(token).append(" ");
        }
        return sb.toString().trim();
    }

    public ResultBuilder withStatus(String success) {
        this.scrutResult.status = success;
        return this;
    }
}
