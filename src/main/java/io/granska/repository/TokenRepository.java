package io.granska.repository;

import io.granska.entity.Token;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;

import java.util.List;


public interface TokenRepository extends JpaRepository<Token,Long> {

    List<Token> findByToken(String token);

    Long countByToken(String token);

    @Query(value = "select * from token2 where token='x'", nativeQuery = true)
    int nEddie();
}
