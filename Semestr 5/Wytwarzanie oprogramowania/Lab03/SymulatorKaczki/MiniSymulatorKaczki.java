package org.example.SymulatorKaczki.src.pl.edu.zut.wo.wzorce.symulator;

import org.example.SymulatorKaczki.src.pl.edu.zut.wo.wzorce.symulator.Kaczki.*;
import org.example.SymulatorKaczki.src.pl.edu.zut.wo.wzorce.symulator.Kwakanie.Kwacz;
import org.example.SymulatorKaczki.src.pl.edu.zut.wo.wzorce.symulator.Kwakanie.NieKwacz;
import org.example.SymulatorKaczki.src.pl.edu.zut.wo.wzorce.symulator.Kwakanie.Piszcz;
import org.example.SymulatorKaczki.src.pl.edu.zut.wo.wzorce.symulator.Latanie.LatamBoMamSkrzydla;
import org.example.SymulatorKaczki.src.pl.edu.zut.wo.wzorce.symulator.Latanie.LotZNapędemRakietowym;
import org.example.SymulatorKaczki.src.pl.edu.zut.wo.wzorce.symulator.Latanie.NieLatam;

public class MiniSymulatorKaczki {

	public static void main(String[] args) {
		Kwacz kwacz = new Kwacz();
		NieKwacz nieKwacz = new NieKwacz();
		Piszcz piszcz = new Piszcz();

		LatamBoMamSkrzydla latamBoMamSkrzydla = new LatamBoMamSkrzydla();
		NieLatam nieLatam = new NieLatam();

		Kaczka dzika = new DzikaKaczka();
		dzika.ustawKwaczInt(kwacz);
		dzika.ustawLećInt(latamBoMamSkrzydla);
		dzika.wyświetl();
		dzika.wykonajLec();
		dzika.wykonajKwacz();

		Kaczka gumowa = new GumowaKaczka();
		gumowa.ustawKwaczInt(piszcz);
		gumowa.ustawLećInt(nieLatam);
		gumowa.wyświetl();
		gumowa.wykonajLec();
		gumowa.wykonajKwacz();

		Kaczka plaskonosa = new PłaskonosKaczka();
		plaskonosa.ustawKwaczInt(nieKwacz);
		plaskonosa.ustawLećInt(nieLatam);
		plaskonosa.wyświetl();
		plaskonosa.wykonajLec();
		plaskonosa.wykonajKwacz();

		Kaczka wabikKaczka = new WabikKaczka();
		wabikKaczka.ustawKwaczInt(nieKwacz);
		wabikKaczka.ustawLećInt(nieLatam);
		wabikKaczka.wyświetl();
		wabikKaczka.wykonajLec();
		wabikKaczka.wykonajKwacz();

		LotZNapędemRakietowym lotZNapędemRakietowym = new LotZNapędemRakietowym();

		Kaczka modelKaczka = new ModelKaczki();
		modelKaczka.ustawKwaczInt(kwacz);
		modelKaczka.ustawLećInt(lotZNapędemRakietowym);
		modelKaczka.wyświetl();
		modelKaczka.wykonajLec();
		modelKaczka.wykonajKwacz();

		modelKaczka.ustawKwaczInt(nieKwacz);
		modelKaczka.ustawLećInt(nieLatam);
		modelKaczka.wykonajLec();
		modelKaczka.wykonajKwacz();
	}
}
