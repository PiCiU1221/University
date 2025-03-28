package org.example.adapterKlasowy;

public class CzujnikiTest {
    
    public static void main(String[] args) {
        
        Wyswietlacz wyswietlacz = null;
        
//        możemy podpiąć WeatherSensor do Wyświetlacza.
//        poniższy fragment nie kompiluje się, bo niezgodne typy
//        Wyświetlacz nie może bezpośrednio użyć WeatherSenson!
//
//        WeatherSensor weatherSensor = new WeatherSensor();
//        wyswietlacz = new Wyswietlacz(weatherSensor);
        
        
//        dlatego przygotujemy adapter
//        tutaj wstaw kod tworzący odpowiedni adapter i podpinający go do wyświetlacza

        CzujnikPogodowy adapterKlasowy = new AdapterKlasowy();
        wyswietlacz = new Wyswietlacz(adapterKlasowy);
        
        for (int i = 0; i < 5; i++) {
            wyswietlacz.wyswietlDanePogodowe();
        }                
        
    }
}
