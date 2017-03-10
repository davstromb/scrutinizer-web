package io.granska.entity;

import java.util.ArrayList;
import java.util.List;


public class Analysis {

    public String raw;

    public Analysis() {
        this.sentences = new ArrayList<>();
    }

    public Integer size;

    public List<Sentence> sentences;

}
