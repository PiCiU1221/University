package org.example.adapterObiektowy;

public class AdapterObiektowy implements CzujnikPogodowy {
    WeatherSensor weatherSensor;

    public AdapterObiektowy(WeatherSensor weatherSensor) {
        this.weatherSensor = weatherSensor;
    }

    @Override
    public double pobierzTemperature() {
        double temperaturaWCelsjuszach =  (weatherSensor.readTemp() - 32) * 5 / 9;
        return Math.round(temperaturaWCelsjuszach * 10) / 10.0;
    }

    @Override
    public double pobierzCisnienie() {
        double cisnienieHpa = weatherSensor.readPressure() * 1000;
        return Math.round(cisnienieHpa * 10) / 10.0;
    }

    @Override
    public double pobierzWilgotnosc() {
        double wilgotnoscWProcentach = weatherSensor.readHumidity() * 100;
        return Math.round(wilgotnoscWProcentach * 10) / 10.0;
    }
}
