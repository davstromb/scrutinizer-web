package io.granska.granska.response;

import javax.xml.bind.annotation.XmlElement;

/**
 * Created by david on 10/03/17.
 */
public class XMLSuggestion {

    @XmlElement(name="emph")
    public XMLEmph emph;
}
