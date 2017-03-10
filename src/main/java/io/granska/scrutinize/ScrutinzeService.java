package io.granska.scrutinize;

import io.granska.entity.Analysis;
import io.granska.granska.GranskaService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.Arrays;

@Service
public class ScrutinzeService {

    private final GranskaService granskaService;

    @Autowired
    public ScrutinzeService(GranskaService granskaService) {
        this.granskaService = granskaService;
    }



    public Analysis scrutinize(String language, String input) {
        String[] split = input.split("\\+");

        System.out.println("Granska lang: " + language + " " + Arrays.asList(split));
        Analysis result = granskaService.scrutinize(Arrays.asList(split));

        result.raw = input;
        return result;
    }


}
