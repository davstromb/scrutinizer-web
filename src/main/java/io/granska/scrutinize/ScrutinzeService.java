package io.granska.scrutinize;

import io.granska.entity.Token;
import io.granska.repository.TokenRepository;
import org.springframework.beans.factory.annotation.Autowired;

import java.util.Arrays;
import java.util.List;


public class ScrutinzeService {

    private final TokenRepository tokenRepository;

    @Autowired
    public ScrutinzeService(TokenRepository tokenRepository) {
        this.tokenRepository = tokenRepository;
    }

    public ScrutResult scrutinize(String language, String[] split) {
        tokenRepository
                .findAll()
                .stream()
                .forEach(token -> System.out.println(token.token));


        List<Token> edwards = tokenRepository.findByToken("edward");
        edwards.stream().forEach(edward -> System.out.println(edward.hash));


        System.out.println("Number of x: " + tokenRepository.countByToken("x"));
        System.out.println("Number of e: " + tokenRepository.nEddie());

        Arrays.asList(split).stream()
                .map(token -> new Token(token))
                .forEach(tokenRepository::save);


        return  ResultBuilder.builder()
                .withInput(split)
                .withStatus("SUCCESS")
                .build();

    }


}
