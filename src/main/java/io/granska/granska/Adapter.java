package io.granska.granska;

import io.granska.entity.Analysis;
import io.granska.entity.builder.AnalysisBuilder;
import io.granska.granska.response.GranskaResponse;

import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBException;
import javax.xml.bind.Unmarshaller;
import java.io.StringReader;
import java.util.List;

/**
 * Created by david on 10/03/17.
 */
public interface Adapter {

    public Analysis get(List<String> tokens);

    default GranskaResponse parseXml(String xml) throws JAXBException {
        JAXBContext jaxbContext = JAXBContext.newInstance(GranskaResponse.class);

        Unmarshaller jaxbUnmarshaller = jaxbContext.createUnmarshaller();
        return (GranskaResponse) jaxbUnmarshaller.unmarshal(new StringReader(xml));
    }

    default Analysis convertToAnalysis(GranskaResponse response) {
        return AnalysisBuilder.builder()
                .withSize(response.sentences.stream()
                        .mapToInt(s -> s.numberOfTokens)
                        .sum())
                .withSentences(response.sentences, response.tags, response.scrutinizer.sentence)
                .build();
    }


}
