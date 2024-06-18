package org.zut.lab7;

import com.google.gson.Gson;
import org.zut.lab4.Lab4;
import org.zut.lab5.Lab5;
import org.zut.lab6.Lab6;

import java.io.FileWriter;
import java.io.IOException;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.Random;

public class Lab7 {

    static int tc = 53;
    static int W = 1;
    static float A1 = 0.5f;
    static float A2 = 1;
    static int fs = 8000;

    private static int[] kodowanie(Boolean hamming74, int[] wiadomoscWBitach) {
        int szerokoscOknaPrzedKodowaniem;
        int szerokoscOknaPoKodowaniu;

        if (hamming74) {
            szerokoscOknaPrzedKodowaniem = 4;
            szerokoscOknaPoKodowaniu = 7;
        } else {
            szerokoscOknaPrzedKodowaniem = 11;
            szerokoscOknaPoKodowaniu = 15;
        }

        int iloscOkienek = (wiadomoscWBitach.length + szerokoscOknaPrzedKodowaniem - 1) / szerokoscOknaPrzedKodowaniem;

        int[] zakodowanaWiadomosc = new int[iloscOkienek * szerokoscOknaPoKodowaniu];

        for (int i = 0; i < iloscOkienek; i++) {
            int[] okno = new int[szerokoscOknaPrzedKodowaniem];

            for (int j = 0; j < szerokoscOknaPrzedKodowaniem; j++) {
                if (i * szerokoscOknaPrzedKodowaniem + j < wiadomoscWBitach.length) {
                    okno[j] = wiadomoscWBitach[i * szerokoscOknaPrzedKodowaniem + j];
                } else {
                    okno[j] = 0;
                }
            }

            int[] zakodowaneOkno;

            if (hamming74) {
                zakodowaneOkno = Lab6.koderHamminga7i4(okno);
            } else {
                zakodowaneOkno = Lab6.koderHamminga15i11(okno);
            }

            for (int j = 0; j < szerokoscOknaPoKodowaniu; j++) {
                zakodowanaWiadomosc[i * szerokoscOknaPoKodowaniu + j] = zakodowaneOkno[j];
            }
        }

        return zakodowanaWiadomosc;
    }

    private static int[] dekodowanie(Boolean hamming74, int[] wiadomoscWBitach) {
        int szerokoscOknaPrzedKodowaniem;
        int szerokoscOknaPoKodowaniu;

        if (hamming74) {
            szerokoscOknaPrzedKodowaniem = 4;
            szerokoscOknaPoKodowaniu = 7;
        } else {
            szerokoscOknaPrzedKodowaniem = 11;
            szerokoscOknaPoKodowaniu = 15;
        }

        int iloscOkienek = (wiadomoscWBitach.length + szerokoscOknaPoKodowaniu - 1) / szerokoscOknaPoKodowaniu;

        int[] zdekodowanaWiadomosc = new int[iloscOkienek * szerokoscOknaPrzedKodowaniem];

        for (int i = 0; i < iloscOkienek; i++) {
            int[] okno = new int[szerokoscOknaPoKodowaniu];

            for (int j = 0; j < szerokoscOknaPoKodowaniu; j++) {
                if (i * szerokoscOknaPoKodowaniu + j < wiadomoscWBitach.length) {
                    okno[j] = wiadomoscWBitach[i * szerokoscOknaPoKodowaniu + j];
                } else {
                    okno[j] = 0;
                }
            }

            int[] zdekodowaneOkno;

            if (hamming74) {
                zdekodowaneOkno = Lab6.dekoderHamminga7i4(okno);
            } else {
                zdekodowaneOkno = Lab6.dekoderHamminga15i11(okno);
            }

            for (int j = 0; j < szerokoscOknaPrzedKodowaniem; j++) {
                zdekodowanaWiadomosc[i * szerokoscOknaPrzedKodowaniem + j] = zdekodowaneOkno[j];
            }
        }

        return zdekodowanaWiadomosc;
    }

    // z Chatu GPT, bo szybciej i działa
    public static String zamienBitowyNaASCII(int[] strumienBitowy) {
        StringBuilder sb = new StringBuilder();

        // Calculate how many bits are needed to complete the last group of 7
        int paddingBits = (7 - (strumienBitowy.length % 7)) % 7;
        int totalLength = strumienBitowy.length + paddingBits;

        // Process each group of 7 bits
        for (int i = 0; i < totalLength; i += 7) {
            int character = 0;

            // Build the character from the bit stream, adding 0 padding bits if necessary
            for (int j = 0; j < 7; j++) {
                if (i + j < strumienBitowy.length) {
                    character = (character << 1) | strumienBitowy[i + j];
                } else {
                    // Add padding bits (0) for incomplete groups
                    character = (character << 1);
                }
            }
            sb.append((char) character);
        }

        // Convert to string and strip trailing null characters (which are just zeros)
        String result = sb.toString();
        return result.replaceAll("\\u0000+$", "");
    }

    private static String pierwszyUklad(String wiadomosc, Boolean hamming7i4, String rodzajModulacji) {
        int[] wiadomoscWBitach = Lab4.zamienASCIInaBitowy(wiadomosc);

        int[] zakodowanaWiadomosc = kodowanie(hamming7i4, wiadomoscWBitach);

        int B = zakodowanaWiadomosc.length;
        //float tb = (float)tc/B;
        float tb = 0.5f;
        float fn = W * (1/tb);

        double[] zmodulowanaWiadomosc;
        double[] zdemodulowanaWiadomosc;

        switch (rodzajModulacji) {
            case "ASK":
                zmodulowanaWiadomosc = Lab4.kluczowanieAmplitudy(zakodowanaWiadomosc, A1, A2, fn, tb, fs, tc);
                zdemodulowanaWiadomosc = Lab5.demodulacjaASK(zmodulowanaWiadomosc, fn, 2, fs, tb);
                break;
            case "PSK":
                zmodulowanaWiadomosc = Lab4.kluczowanieFazy(zakodowanaWiadomosc, fn, tb, fs, tc);
                zdemodulowanaWiadomosc = Lab5.demodulacjaPSK(zmodulowanaWiadomosc, fn, 2, fs, tb);
                break;
            case "FSK":
                zmodulowanaWiadomosc = Lab4.kluczowanieCzestotliwosci(zakodowanaWiadomosc, tb, fs, W, tc);
                zdemodulowanaWiadomosc = Lab5.demodulacjaFSK(zmodulowanaWiadomosc, tb, fs, W, tc);
                break;
            default:
                throw new IllegalArgumentException("Zmienna: rodzajModulacji powinna miec tylko wartosci: ASK, FSK, PSK");
        }

        int[] zdemodulowanaWiadomoscWBitach = Lab5.sygnalCnaCiagBitow(zdemodulowanaWiadomosc, fs, tb);

        int[] zdekodowanaWiadomosc = dekodowanie(hamming7i4, zdemodulowanaWiadomoscWBitach);

        String wiadomoscPoPrzetworzeniu = zamienBitowyNaASCII(zdekodowanaWiadomosc);

        return wiadomoscPoPrzetworzeniu;
    }

    private static void zadanie1(String wiadomosc, Boolean hamming7i4, String rodzajModulacji) {
        String wiadomoscPoPrzetworzeniu = pierwszyUklad(wiadomosc, hamming7i4, rodzajModulacji);

        System.out.println("Wiadomosc:                  " + wiadomosc);
        System.out.println("Wiadomosc po przetworzeniu: " + wiadomoscPoPrzetworzeniu);
    }

    public static double[] dodajSzumBialy(double[] sygnal, double alfa) {
        Random random = new Random();
        double[] sygnalZSzumem = new double[sygnal.length];

        for (int t = 0; t < sygnal.length; t++) {
            double szum = alfa * random.nextGaussian();
            sygnalZSzumem[t] = sygnal[t] + szum;
        }

        return sygnalZSzumem;
    }

    private static String drugiUklad(String wiadomosc, Boolean hamming7i4, String rodzajModulacji, double alfa, Boolean wypisacBER) {
        int[] wiadomoscWBitach = Lab4.zamienASCIInaBitowy(wiadomosc);

        int[] zakodowanaWiadomosc = kodowanie(hamming7i4, wiadomoscWBitach);

        int B = zakodowanaWiadomosc.length;
        //float tb = (float)tc/B;
        float tb = 0.5f;
        float fn = W * (1/tb);

        double[] zmodulowanaWiadomosc;
        double[] zdemodulowanaWiadomosc;

        switch (rodzajModulacji) {
            case "ASK":
                zmodulowanaWiadomosc = Lab4.kluczowanieAmplitudy(zakodowanaWiadomosc, A1, A2, fn, tb, fs, tc);
                zmodulowanaWiadomosc = dodajSzumBialy(zmodulowanaWiadomosc, alfa);
                zdemodulowanaWiadomosc = Lab5.demodulacjaASK(zmodulowanaWiadomosc, fn, 2, fs, tb);
                break;
            case "PSK":
                zmodulowanaWiadomosc = Lab4.kluczowanieFazy(zakodowanaWiadomosc, fn, tb, fs, tc);
                zmodulowanaWiadomosc = dodajSzumBialy(zmodulowanaWiadomosc, alfa);
                zdemodulowanaWiadomosc = Lab5.demodulacjaPSK(zmodulowanaWiadomosc, fn, 2, fs, tb);
                break;
            case "FSK":
                zmodulowanaWiadomosc = Lab4.kluczowanieCzestotliwosci(zakodowanaWiadomosc, tb, fs, W, tc);
                zmodulowanaWiadomosc = dodajSzumBialy(zmodulowanaWiadomosc, alfa);
                zdemodulowanaWiadomosc = Lab5.demodulacjaFSK(zmodulowanaWiadomosc, tb, fs, W, tc);
                break;
            default:
                throw new IllegalArgumentException("Zmienna: rodzajModulacji powinna miec tylko wartosci: ASK, FSK, PSK");
        }

        int[] zdemodulowanaWiadomoscWBitach = Lab5.sygnalCnaCiagBitow(zdemodulowanaWiadomosc, fs, tb);

        int[] zdekodowanaWiadomosc = dekodowanie(hamming7i4, zdemodulowanaWiadomoscWBitach);

        if (wypisacBER) {
            int iloscBledow = 0;
            for (int i = 0; i < wiadomoscWBitach.length; i++) {
                if (wiadomoscWBitach[i] != zdekodowanaWiadomosc[i]) {
                    iloscBledow++;
                }
            }

            System.out.printf("BER: %.2f", (double)iloscBledow / wiadomoscWBitach.length);
        }

        String wiadomoscPoPrzetworzeniu = zamienBitowyNaASCII(zdekodowanaWiadomosc);

        return wiadomoscPoPrzetworzeniu;
    }

    private static void zadanie2(String wiadomosc, Boolean hamming7i4) {
        System.out.println("\nBER dla ASK, PSK i FSK po dodaniu szumu bialego:");
        System.out.println("\n                 ASK         PSK         FSK");

        for (double alfa = 0.0; alfa < 1.0; alfa += 0.1) {
            System.out.printf("alfa = %.1f:   ", alfa);
            drugiUklad(wiadomosc, hamming7i4, "ASK", alfa, true);
            System.out.print("   ");
            drugiUklad(wiadomosc, hamming7i4, "PSK", alfa, true);
            System.out.print("   ");
            drugiUklad(wiadomosc, hamming7i4, "FSK", alfa, true);
            System.out.println(" ");
        }
    }

    public static double[] dodajTlumienie(double[] sygnal, double beta) {
        double[] sygnalZTlumieniem = new double[sygnal.length];

        for (int t = 0; t < sygnal.length; t++) {
            double znormalizowaneT = (double) t / sygnal.length;
            double tlumienie = Math.exp(-beta * znormalizowaneT);
            sygnalZTlumieniem[t] = sygnal[t] * tlumienie;
        }

        return sygnalZTlumieniem;
    }

    private static String trzeciUklad(String wiadomosc, Boolean hamming7i4, String rodzajModulacji, double beta, Boolean wypisacBER) {
        int[] wiadomoscWBitach = Lab4.zamienASCIInaBitowy(wiadomosc);
        System.out.print("Wiadomosc w bitach:   ");
        for (int i = 0; i < wiadomoscWBitach.length; i++) {
            System.out.print(wiadomoscWBitach[i] + " ");
            if (i % 11 == 10) {
                System.out.print("           ");
            }
        }

        System.out.print("\nZakodowana wiadomosc: ");
        int[] zakodowanaWiadomosc = kodowanie(hamming7i4, wiadomoscWBitach);
        for (int i = 0; i < zakodowanaWiadomosc.length; i++) {
            System.out.print(zakodowanaWiadomosc[i] + " ");
            if (i % 15 == 14) {
                System.out.print("   ");
            }
        }

        int B = zakodowanaWiadomosc.length;
//        float tb = (float)tc/B;
        float tb = 0.5f;
        float fn = W * (1/tb);

        double[] zmodulowanaWiadomosc;
        double[] zdemodulowanaWiadomosc;

        switch (rodzajModulacji) {
            case "ASK":
                zmodulowanaWiadomosc = Lab4.kluczowanieAmplitudy(zakodowanaWiadomosc, A1, A2, fn, tb, fs, tc);
                zmodulowanaWiadomosc = dodajTlumienie(zmodulowanaWiadomosc, beta);
                zdemodulowanaWiadomosc = Lab5.demodulacjaASK(zmodulowanaWiadomosc, fn, 2, fs, tb);
                break;
            case "PSK":
                zmodulowanaWiadomosc = Lab4.kluczowanieFazy(zakodowanaWiadomosc, fn, tb, fs, tc);
                zmodulowanaWiadomosc = dodajTlumienie(zmodulowanaWiadomosc, beta);
                zdemodulowanaWiadomosc = Lab5.demodulacjaPSK(zmodulowanaWiadomosc, fn, 2, fs, tb);
                break;
            case "FSK":
                zmodulowanaWiadomosc = Lab4.kluczowanieCzestotliwosci(zakodowanaWiadomosc, tb, fs, W, tc);
                zmodulowanaWiadomosc = dodajTlumienie(zmodulowanaWiadomosc, beta);
                zdemodulowanaWiadomosc = Lab5.demodulacjaFSK(zmodulowanaWiadomosc, tb, fs, W, tc);
                break;
            default:
                throw new IllegalArgumentException("Zmienna: rodzajModulacji powinna miec tylko wartosci: ASK, FSK, PSK");
        }

        int[] zdemodulowanaWiadomoscWBitach = Lab5.sygnalCnaCiagBitow(zdemodulowanaWiadomosc, fs, tb);

        int[] zdekodowanaWiadomosc = dekodowanie(hamming7i4, zdemodulowanaWiadomoscWBitach);

        if (wypisacBER) {
            int iloscBledow = 0;
            for (int i = 0; i < wiadomoscWBitach.length; i++) {
                if (wiadomoscWBitach[i] != zdekodowanaWiadomosc[i]) {
                    iloscBledow++;
                }
            }

            System.out.printf("BER: %.2f", (double)iloscBledow / wiadomoscWBitach.length);
        }

        String wiadomoscPoPrzetworzeniu = zamienBitowyNaASCII(zdekodowanaWiadomosc);

        return wiadomoscPoPrzetworzeniu;
    }

    private static void zadanie3(String wiadomosc, Boolean hamming7i4) {
        System.out.println("\nBER dla ASK, PSK i FSK po dodaniu tlumienia:");
        System.out.println("\n                  ASK         PSK         FSK");

        for (double beta = 0.0; beta < 10.1; beta += 1.0) {
            System.out.printf("beta = %4.1f:   ", beta);
            trzeciUklad(wiadomosc, hamming7i4, "ASK", beta, true);
            System.out.print("   ");
            trzeciUklad(wiadomosc, hamming7i4, "PSK", beta, true);
            System.out.print("   ");
            trzeciUklad(wiadomosc, hamming7i4, "FSK", beta, true);
            System.out.println(" ");
        }
    }

    // struktura danych z Chatu GPT
    static class BERResults {
        private Map<String, Map<Double, Map<Double, Double>>> results;

        public BERResults() {
            results = new HashMap<>();
            results.put("ASK", new HashMap<>());
            results.put("PSK", new HashMap<>());
            results.put("FSK", new HashMap<>());
        }

        public void addResult(String modulation, double alfa, double beta, double ber) {
            results.get(modulation).computeIfAbsent(alfa, k -> new HashMap<>()).put(beta, ber);
        }
    }


    private static double czwartyUklad(String wiadomosc, Boolean hamming7i4, String rodzajModulacji, double alfa, double beta, Boolean pierwszaKonfiguracja) {
        int[] wiadomoscWBitach = Lab4.zamienASCIInaBitowy(wiadomosc);
        System.out.print("Wiadomosc w bitach:   ");
        for (int i = 0; i < wiadomoscWBitach.length; i++) {
            System.out.print(wiadomoscWBitach[i] + " ");
            if (i % 11 == 10) {
                System.out.print("           ");
            }
        }

        System.out.print("\nZakodowana wiadomosc: ");
        int[] zakodowanaWiadomosc = kodowanie(hamming7i4, wiadomoscWBitach);
        for (int i = 0; i < zakodowanaWiadomosc.length; i++) {
            System.out.print(zakodowanaWiadomosc[i] + " ");
            if (i % 15 == 14) {
                System.out.print("   ");
            }
        }

        int B = zakodowanaWiadomosc.length;
//        float tb = (float)tc/B;
        float tb = 0.5f;
        float fn = W * (1/tb);

        double[] zmodulowanaWiadomosc;
        double[] zdemodulowanaWiadomosc;

        switch (rodzajModulacji) {
            case "ASK":
                zmodulowanaWiadomosc = Lab4.kluczowanieAmplitudy(zakodowanaWiadomosc, A1, A2, fn, tb, fs, tc);
                Lab5.plotSignal(zmodulowanaWiadomosc, fs, "zmodulowanaWiadomosc");

                if (pierwszaKonfiguracja) {
                    zmodulowanaWiadomosc = dodajSzumBialy(zmodulowanaWiadomosc, alfa);
                    Lab5.plotSignal(zmodulowanaWiadomosc, fs, "zmodulowanaWiadomosc z szumem");
                    zmodulowanaWiadomosc = dodajTlumienie(zmodulowanaWiadomosc, beta);
                    Lab5.plotSignal(zmodulowanaWiadomosc, fs, "zmodulowanaWiadomosc z szumem i tlumieniem");
                } else {
                    zmodulowanaWiadomosc = dodajTlumienie(zmodulowanaWiadomosc, beta);
                    zmodulowanaWiadomosc = dodajSzumBialy(zmodulowanaWiadomosc, alfa);
                }

                zdemodulowanaWiadomosc = Lab5.demodulacjaASK(zmodulowanaWiadomosc, fn, 2, fs, tb);
                break;
            case "PSK":
                zmodulowanaWiadomosc = Lab4.kluczowanieFazy(zakodowanaWiadomosc, fn, tb, fs, tc);

                if (pierwszaKonfiguracja) {
                    zmodulowanaWiadomosc = dodajSzumBialy(zmodulowanaWiadomosc, alfa);
                    zmodulowanaWiadomosc = dodajTlumienie(zmodulowanaWiadomosc, beta);
                } else {
                    zmodulowanaWiadomosc = dodajTlumienie(zmodulowanaWiadomosc, beta);
                    zmodulowanaWiadomosc = dodajSzumBialy(zmodulowanaWiadomosc, alfa);
                }

                zdemodulowanaWiadomosc = Lab5.demodulacjaPSK(zmodulowanaWiadomosc, fn, 2, fs, tb);
                break;
            case "FSK":
                zmodulowanaWiadomosc = Lab4.kluczowanieCzestotliwosci(zakodowanaWiadomosc, tb, fs, W, tc);

                if (pierwszaKonfiguracja) {
                    zmodulowanaWiadomosc = dodajSzumBialy(zmodulowanaWiadomosc, alfa);
                    zmodulowanaWiadomosc = dodajTlumienie(zmodulowanaWiadomosc, beta);
                } else {
                    zmodulowanaWiadomosc = dodajTlumienie(zmodulowanaWiadomosc, beta);
                    zmodulowanaWiadomosc = dodajSzumBialy(zmodulowanaWiadomosc, alfa);
                }

                zdemodulowanaWiadomosc = Lab5.demodulacjaFSK(zmodulowanaWiadomosc, tb, fs, W, tc);
                break;
            default:
                throw new IllegalArgumentException("Zmienna: rodzajModulacji powinna miec tylko wartosci: ASK, FSK, PSK");
        }

        int[] zdemodulowanaWiadomoscWBitach = Lab5.sygnalCnaCiagBitow(zdemodulowanaWiadomosc, fs, tb);

        int[] zdekodowanaWiadomosc = dekodowanie(hamming7i4, zdemodulowanaWiadomoscWBitach);

        System.out.print("\n\nZdekodowana wiadomosc: " + zamienBitowyNaASCII(zdekodowanaWiadomosc));

        int iloscBledow = 0;
        for (int i = 0; i < wiadomoscWBitach.length; i++) {
            if (wiadomoscWBitach[i] != zdekodowanaWiadomosc[i]) {
                iloscBledow++;
            }
        }

        return (double)iloscBledow / wiadomoscWBitach.length;
    }

    private static void zadanie4(String wiadomosc, Boolean hamming7i4, BERResults berResults, Boolean shouldPrint, Boolean pierwszaKonfiguracja) {
        if (shouldPrint) {
            System.out.println("\nBER dla ASK, PSK i FSK po dodaniu szumu bialego i tlumienia:");
            System.out.println("\n                              ASK         PSK         FSK");
        }

        for (double alfa = 0.0; alfa < 1.0; alfa += 0.1) {
            for (double beta = 0.0; beta < 10.1; beta += 1.0) {
                double berASK = czwartyUklad(wiadomosc, hamming7i4, "ASK", alfa, beta, pierwszaKonfiguracja);
                berResults.addResult("ASK", alfa, beta, berASK);
                if (shouldPrint) {
                    System.out.printf("alfa = %.1f, beta = %4.1f:   ", alfa, beta);
                    System.out.printf("BER: %.2f", berASK);
                    System.out.print("   ");
                }

                double berPSK = czwartyUklad(wiadomosc, hamming7i4, "PSK", alfa, beta, pierwszaKonfiguracja);
                berResults.addResult("PSK", alfa, beta, berPSK);
                if (shouldPrint) {
                    System.out.printf("BER: %.2f", berPSK);
                    System.out.print("   ");
                }

                double berFSK = czwartyUklad(wiadomosc, hamming7i4, "FSK", alfa, beta, pierwszaKonfiguracja);
                berResults.addResult("FSK", alfa, beta, berFSK);
                if (shouldPrint) {
                    System.out.printf("BER: %.2f", berFSK);
                    System.out.println(" ");
                }
            }
        }
    }

    public static void saveResultsToFile(BERResults berResults, String filePath) {
        Gson gson = new Gson();
        String json = gson.toJson(berResults);

        try (FileWriter file = new FileWriter(filePath)) {
            file.write(json);
            System.out.println("\nPomyślnie zapisano wyniki BER do pliku JSON.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
//        String wiadomosc = "test test test test test test test test";
//        String wiadomosc = "testowanie";
        String wiadomosc = "transmisja";

        // ZADANIE 1

        // dla kodu Hamminga 7i4
//        zadanie1(wiadomosc, true, "ASK");
//        zadanie1(wiadomosc, true, "PSK");
//        zadanie1(wiadomosc, true, "FSK");

        // dla kodu Hamminga 15i11
//        zadanie1(wiadomosc, false, "ASK");
//        zadanie1(wiadomosc, false, "PSK");
//        zadanie1(wiadomosc, false, "FSK");

        // ZADANIE 2

//        zadanie2(wiadomosc, false);

        // ZADANIE 3

//        zadanie3(wiadomosc, false);

        // ZADANIE 4
        // pierwsza konfiguracja - I+II
//        BERResults barResultsPierwsza = new BERResults();
//        zadanie4(wiadomosc, false, barResultsPierwsza, false, true);
        //saveResultsToFile(barResultsPierwsza, "src/main/java/org/zut/lab7/ber_results_pierwsza.json");

        // druga konfiguracja - II+I
//        BERResults barResultsDruga = new BERResults();
//        zadanie4(wiadomosc, false, barResultsDruga, false, false);
        //saveResultsToFile(barResultsDruga, "src/main/java/org/zut/lab7/ber_results_druga.json");


        System.out.println("Wiadomosc przed: " + wiadomosc + "\n");
        czwartyUklad(wiadomosc, false, "ASK", 0.1, 0.0, true);
    }
}
