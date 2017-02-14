package io.granska.controller;

import io.granska.scrutinize.ScrutResult;
import io.granska.scrutinize.ScrutinzeService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("scrutinizer")
public class ScrutinizeController {


    private final ScrutinzeService scrutinzeService;

    @Autowired
    public ScrutinizeController(ScrutinzeService scrutinzeService) {
        this.scrutinzeService = scrutinzeService;
    }

    @RequestMapping(value = "ping", method = RequestMethod.GET, produces = "text/plain")
    public String ping() {
        return "pong";
    }

    @RequestMapping(value = "scrutinize/{language}/{tokens}", method = RequestMethod.GET, produces = "application/json")
    public ScrutResult scrutinize(@PathVariable final String language, @PathVariable final String tokens) {
        return scrutinzeService.scrutinize(language, tokens.split("\\+"));
    }
}
