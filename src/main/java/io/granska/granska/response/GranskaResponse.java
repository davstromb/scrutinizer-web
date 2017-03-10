package io.granska.granska.response;


import javax.xml.bind.annotation.*;
import java.util.List;

@XmlRootElement(name="Root")
@XmlAccessorType(XmlAccessType.FIELD)
public class GranskaResponse {

    @XmlElement(name="s")
    public List<XMLSentence> sentences;

    @XmlElement(name="scrutinizer")
    public Scrutinizer scrutinizer;

    @XmlElementWrapper(name="tags")
    @XmlElement(name="tag")
    public List<XMLTag> tags;

    @XmlElement(name="rules")
    public Rules rules;


}
