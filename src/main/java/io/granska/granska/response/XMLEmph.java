package io.granska.granska.response;

import javax.xml.bind.annotation.*;

/**
 * Created by david on 10/03/17.
 */
public class XMLEmph {

    @XmlAttribute
    public String type;

    @XmlValue
    public String value;
}
