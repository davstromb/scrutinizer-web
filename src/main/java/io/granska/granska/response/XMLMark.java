package io.granska.granska.response;

import javax.xml.bind.annotation.XmlAttribute;

/**
 * Created by david on 10/03/17.
 */
public class XMLMark {

    @XmlAttribute
    public Integer begin;

    @XmlAttribute
    public Integer end;
}
