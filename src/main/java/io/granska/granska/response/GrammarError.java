package io.granska.granska.response;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlElementWrapper;
import java.util.List;

@XmlAccessorType(XmlAccessType.FIELD)
public class GrammarError {

    @XmlElement(name = "marked")
    public XMLMarked marked;

    @XmlElement(name="rule")
    public String rule;

    @XmlElement(name="info")
    public String info;

    @XmlElementWrapper(name="suggestions")
    @XmlElement(name="sugg")
    public List<XMLSuggestion> suggestions;

    @XmlElement(name="marked_section")
    public XMLMark mark;
}
