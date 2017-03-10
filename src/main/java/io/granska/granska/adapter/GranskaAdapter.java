package io.granska.granska.adapter;

import io.granska.entity.Analysis;
import io.granska.granska.Adapter;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.List;

public class GranskaAdapter implements Adapter {

    private final static String COMMAND = "ls";


    public Analysis get(List<String> tokens) {
        String s = executeCommand(COMMAND);
        return null;
    }

    private String executeCommand(String command) {

        StringBuffer output = new StringBuffer();

        Process p;
        try {
            p = Runtime.getRuntime().exec(command);
            p.waitFor();
            BufferedReader reader =
                    new BufferedReader(new InputStreamReader(p.getInputStream()));

            String line = "";
            while ((line = reader.readLine())!= null) {
                output.append(line + "\n");
            }

        } catch (Exception e) {
            System.out.println("Can not parse granska information");
        }

        return output.toString();

    }
}
