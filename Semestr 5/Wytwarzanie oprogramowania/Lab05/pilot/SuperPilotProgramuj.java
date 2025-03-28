package org.example.pilot;

import org.example.pilot.polecenia.*;
import org.example.pilot.sterowniki.DrzwiGarażu;
import org.example.pilot.sterowniki.WentylatorSufitowy;
import org.example.pilot.sterowniki.WieżaStereo;
import org.example.pilot.sterowniki.Światło;

public class SuperPilotProgramuj {
 
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

		System.out.println(superPilot);
 
		superPilot.wciśniętoPrzyciskWłącz(0);
		superPilot.wciśniętoPrzyciskWycofaj();
		superPilot.wciśniętoPrzyciskWyłącz(0);
		superPilot.wciśniętoPrzyciskWłącz(1);
		superPilot.wciśniętoPrzyciskWyłącz(1);
		superPilot.wciśniętoPrzyciskWłącz(2);
		superPilot.wciśniętoPrzyciskWyłącz(2);
		superPilot.wciśniętoPrzyciskWłącz(3);
		superPilot.wciśniętoPrzyciskWyłącz(3);
		superPilot.wciśniętoPrzyciskWłącz(4);
		superPilot.wciśniętoPrzyciskWyłącz(4);
	}
}
