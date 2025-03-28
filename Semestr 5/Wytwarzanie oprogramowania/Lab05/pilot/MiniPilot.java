package org.example.pilot;

import org.example.pilot.polecenia.Polecenie;

public class MiniPilot {
	Polecenie slot;
	
	public void ustawPolecenie(Polecenie polecenie) {
		slot = polecenie;
	}
	
	public void przyciskZostałNaciśnięty() {
		slot.wykonaj();
	}

}
