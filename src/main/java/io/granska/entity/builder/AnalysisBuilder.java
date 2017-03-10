package io.granska.entity.builder;

import io.granska.entity.*;
import io.granska.entity.TokenError;
import io.granska.granska.response.*;

import java.util.*;
import java.util.stream.Collectors;

/**
 * Created by david on 10/03/17.
 */
public class AnalysisBuilder {

    private Analysis analysis;

    public AnalysisBuilder() {
        this.analysis = new Analysis();
    }

    public static AnalysisBuilder builder() {
        return new AnalysisBuilder();
    }

    public Analysis build() {
        return this.analysis;
    }

    public AnalysisBuilder withSize(Integer numberOfTokens) {
        this.analysis.size = numberOfTokens;
        return this;
    }

    public AnalysisBuilder withSentences(List<XMLSentence> sentences, List<XMLTag> tags, List<ErrorSentence> errors) {
        Map<Integer,String> tagMap = new HashMap<Integer,String>();
        tags.stream().forEach(tag -> tagMap.put(tag.index, tag.text));

        Map<Integer, ErrorSentence> errorMap = new HashMap<>();
        errors.forEach(error -> errorMap.put(error.index, error));

        for(XMLSentence sentece : sentences) {
            Sentence s = new Sentence(0);
            s.tokens = sentece.words.stream().map(l -> getToken(sentece.reference, l, tagMap, errorMap)).collect(Collectors.toList());
            s.errors = getSentenceErrors(sentece.reference, errors);
            s.valid = true;
            if(s.errors.size() > 0 ) {
                s.valid = false;
            }

            this.analysis.sentences.add(s);
        }


        return this;
    }

    private List<SentenceError> getSentenceErrors(Integer ref, List<ErrorSentence> errorMap) {
        return errorMap.stream()
                .filter(e -> Objects.equals(ref, e.index))
                .map(e -> e.errors)
                .flatMap(Collection::stream)
                .filter(e -> Objects.isNull(e.marked.emph))
                .map(this::toSentenceError)
                .collect(Collectors.toList());
    }

    private SentenceError toSentenceError(GrammarError grammarError) {
        SentenceError se = new SentenceError();
        se.rule = grammarError.rule;
        se.info = grammarError.info;
        return se;
    }

    private Token getToken(final Integer reference, final Word word, final Map<Integer, String> map, final Map<Integer, ErrorSentence> errors) {
        Token t = new Token(word.lemma);
        t.tag = map.get(word.index);
        t.valid = true;
        System.out.println("errors " + errors.size());
        if(errors.containsKey(reference)) {
            ErrorSentence errorSentence = errors.get(reference);
            System.out.println("Ref " + reference);

            Objects.requireNonNull(errorSentence);

            Objects.requireNonNull(errorSentence.errors);
            t.errors = errorSentence.errors.stream()
                    .filter(e -> ! Objects.isNull(e.marked.emph))
                    .filter(e -> filter(e, word))
                    .map(this::mapToError)
                    .collect(Collectors.toList());
            if(t.errors.size() > 0) {
                t.valid = false;
            }

        } else {
            System.out.println("Ref: " + reference + ", error: " + errors.keySet());
        }
        return t;
    }

    private boolean filter(GrammarError e, Word word) {
        try {
            System.out.println("Comparing: " + word.lemma + " with " + e.marked.emph.value);
            return Objects.equals(word.lemma, e.marked.emph.value.trim());
        } catch(Exception ignored) {
            ignored.printStackTrace();
            System.out.println("lol");
        }
        return false;
    }

    private TokenError mapToError(GrammarError grammarError) {
        TokenError error = new TokenError();
        error.info = grammarError.info;
        error.rule = grammarError.rule;
        error.suggestions = grammarError
                .suggestions
                .stream()
                .map(s -> s.emph.value).collect(Collectors.toList());
        System.out.println("Error created " + error.info);
        return error;
    }
}
