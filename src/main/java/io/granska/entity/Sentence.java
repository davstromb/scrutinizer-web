package io.granska.entity;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by david on 10/03/17.
 */
public class Sentence {

    public Integer index;
    public boolean valid;
    public List<Token> tokens;
    public List<SentenceError> errors;


    public Sentence() {
        this.tokens = new ArrayList<>();
    }

    public Sentence(Integer index) {
        this();
        this.index = index;
    }

}
