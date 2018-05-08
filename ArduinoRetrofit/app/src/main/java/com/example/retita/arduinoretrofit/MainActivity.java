package com.example.retita.arduinoretrofit;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

public class MainActivity extends AppCompatActivity {

    private  AService aService;

    private Button hall;
    private Button cuisine;
    private Button douche;
    private Button chambre;
    private Button fenetre;

    private int[] etat = {0,0,0,0,0};

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        aService = ApiUtils.getLedService();

/*
        Button allumer;
        Button etteindre;
        allumer = (Button)findViewById(R.id.allumer);
        etteindre = (Button) findViewById(R.id.eteindre);

        allumer.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                loadAnswers(1);
            }
        });

        etteindre.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                loadAnswers(0);
            }
        });
*/


        hall =(Button)findViewById(R.id.hall);
        douche =(Button)findViewById(R.id.douche);
        cuisine =(Button)findViewById(R.id.cuisine);
        chambre =(Button)findViewById(R.id.chambre);
        fenetre =(Button)findViewById(R.id.fenetre);

        hall.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(etat[0] == 0) {
                    loadAnswers("h1");
                    etat[0] = 1;
                    hall.setSelected(true);

                }
                else{
                    loadAnswers("h0");
                    etat[0] = 0;
                    hall.setSelected(false);

                }

            }
        });

        douche.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(etat[1] == 0) {
                    loadAnswers("d1");
                    etat[1] = 1;
                    douche.setSelected(true);

                }
                else{
                    loadAnswers("d0");
                    etat[1] = 0;
                    douche.setSelected(false);
                }

            }
        });

        cuisine.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(etat[2] == 0) {
                    loadAnswers("c1");
                    etat[2] = 1;
                    cuisine.setSelected(true);

                }
                else{
                    loadAnswers("c0");
                    etat[2] = 0;
                    cuisine.setSelected(false);

                }

            }
        });

        chambre.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(etat[3] == 0) {
                    loadAnswers("C1");
                    etat[3] = 1;
                    chambre.setSelected(true);

                }
                else{
                    loadAnswers("C0");
                    etat[3] = 0;
                    chambre.setSelected(false);

                }
            }
        });


        fenetre.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

            }
        });

    }


    public void loadAnswers(String v) {
        aService.getAnswers(v).enqueue(new Callback<Led>() {
            @Override
            public void onResponse(Call<Led> call, Response<Led> response) {

                if(response.isSuccessful()) {
                    Log.d("MainActivity", "posts loaded from API");
                }else {
                    int statusCode  = response.code();
                    // handle request errors depending on status code
                }
            }

            @Override
            public void onFailure(Call<Led> call, Throwable t) {
                Log.d("MainActivity", "error loading from API");

            }
        });
    }
}
