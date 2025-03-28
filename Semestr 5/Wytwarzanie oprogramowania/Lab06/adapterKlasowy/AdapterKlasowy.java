package org.example.adapterKlasowy;

public class AdapterKlasowy extends WeatherSensor implements CzujnikPogodowy {

    @Override
    public double pobierzTemperature() {
        double temperaturaWCelsjuszach =  (super.readTemp() - 32) * 5 / 9;
        return Math.round(temperaturaWCelsjuszach * 10) / 10.0;
    }

    @Override
    public double pobierzCisnienie() {
        double cisnienieHpa = super.readPressure() * 1000;
        return Math.round(cisnienieHpa * 10) / 10.0;
    }

    @Override
    public double pobierzWilgotnosc() {
        double wilgotnoscWProcentach = super.readHumidity() * 100;
        return Math.round(wilgotnoscWProcentach * 10) / 10.0;
    }
}
