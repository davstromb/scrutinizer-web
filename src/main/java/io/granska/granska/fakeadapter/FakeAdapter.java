package io.granska.granska.fakeadapter;

import io.granska.entity.Analysis;
import io.granska.granska.Adapter;
import io.granska.granska.response.GranskaResponse;

import javax.xml.bind.JAXBException;
import java.util.List;

public class FakeAdapter implements Adapter {


    @Override
    public Analysis get(List<String> tokens) {
        GranskaResponse response = null;
        try {
            response = parseXml(FakeData.XML_ERROR);
        } catch (JAXBException e) {
            e.printStackTrace();
        }
        return this.convertToAnalysis(response);
    }

}
