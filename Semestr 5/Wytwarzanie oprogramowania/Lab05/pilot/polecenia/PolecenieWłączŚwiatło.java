package org.example.pilot.polecenia;

import org.example.pilot.sterowniki.Światło;

public class PolecenieWłączŚwiatło implements Polecenie {
	Światło światło;

	public PolecenieWłączŚwiatło(Światło światło) {
		super();
		this.światło = światło;
	}

	public void wykonaj() {
		światło.włącz();
	}

	public void wycofaj() {
		światło.wyłącz();
	}
}
