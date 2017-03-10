package io.granska.granska.response;

import javax.xml.bind.annotation.XmlAttribute;

public class Word {

    @XmlAttribute(name = "no")
    public Integer index;

    @XmlAttribute(name = "tag")
    public String tag;

    @XmlAttribute(name = "lemma")
    public String lemma;


}
