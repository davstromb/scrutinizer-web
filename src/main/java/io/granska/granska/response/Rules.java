package io.granska.granska.response;

import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlElementWrapper;
import java.util.List;

/**
 * Created by david on 10/03/17.
 */
public class Rules {

    @XmlElementWrapper(name="categories")
    @XmlElement(name="category")
    List<Category> categories;

    @XmlElementWrapper(name="rules_used")
    @XmlElement(name="rule")
    List<Rule> used;


}
