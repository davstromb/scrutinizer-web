package io.granska.granska.response;

import javax.xml.bind.annotation.*;
import java.util.List;

@XmlAccessorType(XmlAccessType.FIELD)
public class XMLSentence {

    @XmlAttribute(name="ref")
    public Integer reference;

    @XmlElement(name="words")
    public Integer numberOfTokens;

    @XmlElement(name="text")
    public String input;

    @XmlElementWrapper(name="contents")
    @XmlElement(name="w")
    public List<Word> words;

}
