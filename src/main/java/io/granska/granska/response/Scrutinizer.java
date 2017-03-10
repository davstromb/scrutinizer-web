package io.granska.granska.response;

import javax.xml.bind.annotation.XmlElement;
import java.util.List;

/**
 * Created by david on 10/03/17.
 */
public class Scrutinizer {

    @XmlElement(name="s")
    public List<ErrorSentence> sentence;

}
