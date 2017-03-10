package io.granska.scrutinize;

import io.granska.entity.Token;
import io.granska.granska.GranskaService;
import io.granska.repository.TokenRepository;
import org.springframework.beans.factory.annotation.Autowired;

import java.util.Arrays;
import java.util.List;


public class ScrutinzeService {

    private final TokenRepository tokenRepository;
    private final GranskaService granskaService;

    @Autowired
    public ScrutinzeService(TokenRepository tokenRepository, GranskaService granskaService) {
        this.tokenRepository = tokenRepository;
        this.granskaService = granskaService;
    }



    public ScrutResult scrutinize(String language, String[] split) {
        System.out.println("Granska lang: " + language + " " + Arrays.asList(split));
        granskaService.scrutinize(Arrays.asList(split));

        return  ResultBuilder.builder()
                .withInput(split)
                .withStatus("SUCCESS")
                .build();
    }


}
