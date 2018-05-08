package com.example.retita.arduinoretrofit;

/**
 * Created by retita on 25/01/18.
 */

public class ApiUtils {

    public static final String BASE_URL = "http://172.16.198.146/";

    public static AService getLedService() {
        return RetrofitClient.getClient(BASE_URL).create(AService.class);
    }
}
