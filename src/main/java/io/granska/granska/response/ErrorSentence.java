package io.granska.granska.response;

import javax.xml.bind.annotation.*;
import java.util.List;

@XmlAccessorType(XmlAccessType.FIELD)
public class ErrorSentence {

    @XmlAttribute(name = "ref")
    public Integer index;

    @XmlElementWrapper(name="gramerrors")
    @XmlElement(name="gramerror")
    public List<GrammarError> errors;

}
