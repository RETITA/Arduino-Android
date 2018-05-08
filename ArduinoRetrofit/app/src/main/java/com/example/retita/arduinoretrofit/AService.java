package com.example.retita.arduinoretrofit;

import retrofit2.Call;
import retrofit2.http.GET;
import retrofit2.http.Query;

/**
 * Created by retita on 25/01/18.
 */

public interface AService {

    @GET("/gpio/")
    Call<Led> getAnswers(@Query("") String tags);
}
