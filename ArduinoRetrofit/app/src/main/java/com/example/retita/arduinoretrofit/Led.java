package com.example.retita.arduinoretrofit;

/**
 * Created by retita on 25/01/18.
 */
import com.google.gson.annotations.Expose;
import com.google.gson.annotations.SerializedName;

public class Led {

    @SerializedName("pinLed")
        @Expose
        private Integer pinLed;
        @SerializedName("allume")
        @Expose
        private Boolean allume;

        public Integer getPinLed() {
            return pinLed;
        }

        public void setPinLed(Integer pinLed) {
            this.pinLed = pinLed;
        }

        public Boolean getAllume() {
            return allume;
        }

        public void setAllume(Boolean allume) {
            this.allume = allume;
        }

    }

