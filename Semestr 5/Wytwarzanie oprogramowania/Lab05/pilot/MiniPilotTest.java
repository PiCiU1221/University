package org.example.pilot;

import org.example.pilot.polecenia.PolecenieWłączŚwiatło;
import org.example.pilot.sterowniki.Światło;

public class MiniPilotTest {
	public static void main(String[] args) {
		MiniPilot pilot = new MiniPilot();
		Światło światło = new Światło("lokalizacja: ");
		pilot.ustawPolecenie(new PolecenieWłączŚwiatło(światło));
		pilot.przyciskZostałNaciśnięty();
	}
}
