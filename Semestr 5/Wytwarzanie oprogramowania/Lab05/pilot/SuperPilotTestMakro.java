package org.example.pilot;

import org.example.pilot.polecenia.*;
import org.example.pilot.sterowniki.*;

public class SuperPilotTestMakro {
    public static void main(String[] args) {
        SuperPilot superPilot = new SuperPilot();

        Światło salonŚwiatło = new Światło("Salon");
        Światło kuchniaŚwiatło = new Światło("Kuchnia");
        WentylatorSufitowy wentylatorSalon = new WentylatorSufitowy("Salon");
        DrzwiGarażu drzwiGarażu = new DrzwiGarażu("Dom");
        WieżaStereo wieżaStereo = new WieżaStereo("Salon");

        Polecenie salonŚwiatłoWłącz = new PolecenieWłączŚwiatło(salonŚwiatło);
        Polecenie salonŚwiatłoWyłącz = new PolecenieWyłączŚwiatło(salonŚwiatło);
        superPilot.ustawPolecenie(0, salonŚwiatłoWłącz,  salonŚwiatłoWyłącz);

        Polecenie kuchniaŚwiatłoWłącz = new PolecenieWłączŚwiatło(kuchniaŚwiatło);
        Polecenie kuchniaŚwiatłoWyłącz = new PolecenieWyłączŚwiatło(kuchniaŚwiatło);
        superPilot.ustawPolecenie(1, kuchniaŚwiatłoWłącz,  kuchniaŚwiatłoWyłącz);

        Polecenie wentylatorSalonWysokieObroty = new WentylatorSufitowyWysokieObroty(wentylatorSalon);
        Polecenie wentylatorSalonWyłącz = new WyłączWentylatorSufitowy(wentylatorSalon);
        superPilot.ustawPolecenie(2, wentylatorSalonWysokieObroty,  wentylatorSalonWyłącz);

        Polecenie otwórzDrzwiGarażowe = new OtwórzDrzwiGarażowe(drzwiGarażu);
        Polecenie zamknijDrzwiGarażowe = new ZamknijDrzwiGarażowe(drzwiGarażu);
        superPilot.ustawPolecenie(3, otwórzDrzwiGarażowe,  zamknijDrzwiGarażowe);

        Polecenie wieżaStereoWłączCD = new WieżaStereoWłączCD(wieżaStereo);
        Polecenie wyłączWieżaStereo = new WyłączWieżaStereo(wieżaStereo);
        superPilot.ustawPolecenie(4, wieżaStereoWłączCD,  wyłączWieżaStereo);

        MakroPolecenie wszystkieŚwiatłaWłącz = new MakroPolecenie(new Polecenie[] { salonŚwiatłoWłącz, kuchniaŚwiatłoWłącz });
        MakroPolecenie wszystkieŚwiatłaWyłącz = new MakroPolecenie(new Polecenie[] { salonŚwiatłoWyłącz, kuchniaŚwiatłoWyłącz });
        superPilot.ustawPolecenie(5, wszystkieŚwiatłaWłącz, wszystkieŚwiatłaWyłącz);

        TV tv = new TV("Salon");
        Polecenie telewizorWłącz = new TelewizorWłącz(tv);
        Polecenie przełączZestawNaDVD = new PrzełączZestawNaDVD(wieżaStereo, tv);
        Jacuzzi jacuzzi = new Jacuzzi();
        Polecenie przygotujJacuzzi = new PrzygotujJacuzzi(jacuzzi);

        MakroPolecenie trybImprezaWłącz = new MakroPolecenie(
                new Polecenie[] { wszystkieŚwiatłaWyłącz, wieżaStereoWłączCD, telewizorWłącz, przełączZestawNaDVD, przygotujJacuzzi }
        );

        Polecenie telewizorWyłącz = new TelewizorWyłącz(tv);
        Polecenie wyłączJacuzzi = new WyłączJacuzzi(jacuzzi);

        MakroPolecenie trybImprezaWyłącz = new MakroPolecenie(
                new Polecenie[] { wszystkieŚwiatłaWłącz, wyłączWieżaStereo, telewizorWyłącz, wyłączJacuzzi }
        );

        superPilot.ustawPolecenie(6, trybImprezaWłącz, trybImprezaWyłącz);

        System.out.println(superPilot);

        superPilot.wciśniętoPrzyciskWłącz(0);
        superPilot.wciśniętoPrzyciskWycofaj();
        superPilot.wciśniętoPrzyciskWyłącz(0);

        System.out.println();

        superPilot.wciśniętoPrzyciskWłącz(1);
        superPilot.wciśniętoPrzyciskWyłącz(1);

        System.out.println();

        superPilot.wciśniętoPrzyciskWłącz(2);
        superPilot.wciśniętoPrzyciskWyłącz(2);

        System.out.println();

        superPilot.wciśniętoPrzyciskWłącz(3);
        superPilot.wciśniętoPrzyciskWyłącz(3);

        System.out.println();

        superPilot.wciśniętoPrzyciskWłącz(4);
        superPilot.wciśniętoPrzyciskWyłącz(4);

        System.out.println();

        superPilot.wciśniętoPrzyciskWłącz(5);
        superPilot.wciśniętoPrzyciskWyłącz(5);

        System.out.println();

        superPilot.wciśniętoPrzyciskWłącz(6);
        superPilot.wciśniętoPrzyciskWyłącz(6);
    }
}
