package io.granska.granska;

import org.springframework.stereotype.Service;

import java.util.Arrays;
import java.util.List;

@Service
public class GranskaService {

    private final GranskaAdapter adapter;

    public GranskaService(GranskaAdapter adapter) {
        this.adapter = adapter;
    }

    public void scrutinize(List<String> tokens) {
        System.out.println("About to run adapter");
        adapter.run(tokens);
    }
}
