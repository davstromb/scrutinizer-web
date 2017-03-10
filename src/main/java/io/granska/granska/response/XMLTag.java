package io.granska.granska.response;


import javax.xml.bind.annotation.XmlAttribute;

public class XMLTag {

    @XmlAttribute(name = "no")
    public Integer index;

    @XmlAttribute(name = "name")
    public String text;

}
