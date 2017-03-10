package io.granska.granska.response;

import javax.xml.bind.annotation.XmlElement;

/**
 * Created by david on 10/03/17.
 */
public class Category {

    @XmlElement(name = "name")
    public String name;

    @XmlElement(name = "info")
    public String info;

    @XmlElement(name = "count")
    public Integer count;

}
