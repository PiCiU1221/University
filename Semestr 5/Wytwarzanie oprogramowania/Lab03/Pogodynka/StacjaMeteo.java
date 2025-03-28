package org.example.Pogodynka.src.pl.edu.zut.wo.wzorce.pogodynka;

import org.example.Pogodynka.src.pl.edu.zut.wo.wzorce.pogodynka.wyświetl.IndeksCiepłaWyświetlanie;
import org.example.Pogodynka.src.pl.edu.zut.wo.wzorce.pogodynka.wyświetl.PrognozaWyświetlanie;
import org.example.Pogodynka.src.pl.edu.zut.wo.wzorce.pogodynka.wyświetl.StatystykaWyświetlanie;
import org.example.Pogodynka.src.pl.edu.zut.wo.wzorce.pogodynka.wyświetl.WarunkiBieżąceWyświetlanie;

public class StacjaMeteo {

	public static void main(String[] args) {
		DanePogodowe danePogodowe = new DanePogodowe();
		PrognozaWyświetlanie prognozaWyświetlanie = new PrognozaWyświetlanie();
		StatystykaWyświetlanie statystykaWyświetlanie = new StatystykaWyświetlanie();
		WarunkiBieżąceWyświetlanie warunkiBieżąceWyświetlanie = new WarunkiBieżąceWyświetlanie();

		danePogodowe.zarejestrujObserwatora(prognozaWyświetlanie);
		danePogodowe.zarejestrujObserwatora(statystykaWyświetlanie);
		danePogodowe.zarejestrujObserwatora(warunkiBieżąceWyświetlanie);

		danePogodowe.ustawOdczyty(26.6f, 65, 1013.1f);
		danePogodowe.powiadomObserwatorów();
		System.out.println();

		danePogodowe.ustawOdczyty(27.7f, 70, 997.0f);
		danePogodowe.usuńObserwatora(warunkiBieżąceWyświetlanie);
		danePogodowe.powiadomObserwatorów();
		System.out.println();

		danePogodowe.ustawOdczyty(25.5f, 90, 997.0f);
		danePogodowe.usuńObserwatora(statystykaWyświetlanie);
		danePogodowe.powiadomObserwatorów();
		System.out.println();

		IndeksCiepłaWyświetlanie indeksCiepłaWyświetlanie = new IndeksCiepłaWyświetlanie();

		danePogodowe.zarejestrujObserwatora(indeksCiepłaWyświetlanie);
		danePogodowe.ustawOdczyty(22.5f, 92, 997.0f);
		danePogodowe.powiadomObserwatorów();
	}
	
}