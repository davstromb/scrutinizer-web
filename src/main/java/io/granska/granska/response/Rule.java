package io.granska.granska.response;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;

@XmlAccessorType(XmlAccessType.FIELD)
public class Rule {

    @XmlElement(name = "name")
    public String name;

    @XmlElement(name = "category")
    public String category;

    @XmlElement(name = "linkurl")
    public String linkurl;

    @XmlElement(name = "linktext")
    public String linktext;
}
