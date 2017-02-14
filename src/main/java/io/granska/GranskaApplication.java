package io.granska;

import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.EnableAutoConfiguration;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.ComponentScan;

@SpringBootApplication
@EnableAutoConfiguration
@ComponentScan(basePackages={"io.granska"})
public class GranskaApplication implements CommandLineRunner {

	public static void main(String[] args) {
		SpringApplication.run(GranskaApplication.class, args);
	}

	@Override
	public void run(String... args) throws Exception {
	}
}
