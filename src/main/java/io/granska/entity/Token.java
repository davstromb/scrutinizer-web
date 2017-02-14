package io.granska.entity;

import javax.persistence.*;

@Table(name = "token2")
@Entity
public class Token {

    @Id
    @GeneratedValue(strategy= GenerationType.AUTO, generator="seq_id")
    @SequenceGenerator(name="seq_id", sequenceName="TOKEN_SEQ", allocationSize=1)
    public Long id;

    @Column(name = "token")
    public String token;

    @Column(name = "hashcode")
    public int hash;

    public Token() {}

    public Token(String token) {
        this.token = token;
        this.hash = token.hashCode();
    }
}
