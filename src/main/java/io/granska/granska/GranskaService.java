package io.granska.granska;

import io.granska.entity.Analysis;
import io.granska.granska.fakeadapter.FakeAdapter;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class GranskaService {

    private final Adapter adapter;

    public GranskaService() {
        this.adapter = new FakeAdapter();
    }

    public Analysis scrutinize(List<String> tokens) {
        System.out.println("About to run adapter");
        return adapter.get(tokens);
    }
}
