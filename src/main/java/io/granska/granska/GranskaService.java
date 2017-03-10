package io.granska.granska;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.SerializationFeature;
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
        final Analysis analysis = adapter.get(tokens);

        try {
            System.out.println(new ObjectMapper().enable(SerializationFeature.INDENT_OUTPUT).writeValueAsString(analysis));

        } catch (JsonProcessingException e) {
            e.printStackTrace();
        }
        return analysis;
    }
}
