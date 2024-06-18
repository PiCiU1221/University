package org.zut.lab6;

import java.util.Arrays;
import java.util.Random;

public class Lab6 {
    public static int[] koderHamminga7i4(int[] sygnal) {
        int[] x = new int[7];

        x[2] = sygnal[0];
        x[4] = sygnal[1];
        x[5] = sygnal[2];
        x[6] = sygnal[3];

        x[0] = ((x[2] + x[4]) % 2  + x[6]) % 2;
        x[1] = ((x[2] + x[5]) % 2  + x[6]) % 2;
        x[3] = ((x[4] + x[5]) % 2  + x[6]) % 2;

        return x;
    }

    public static int[] dekoderHamminga7i4(int[] sygnal) {
        int[] x = new int[4];

        int x1p = ((sygnal[2] + sygnal[4]) % 2  + sygnal[6]) % 2;
        int x2p = ((sygnal[2] + sygnal[5]) % 2  + sygnal[6]) % 2;
        int x4p = ((sygnal[4] + sygnal[5]) % 2  + sygnal[6]) % 2;

        int x1Inv = (sygnal[0] + x1p) % 2;
        int x2Inv = (sygnal[1] + x2p) % 2;
        int x4Inv = (sygnal[3] + x4p) % 2;

        int S = (int) (x1Inv * Math.pow(2, 0) + x2Inv * Math.pow(2, 1) + x4Inv * Math.pow(2, 2));

        if (S != 0) {
            sygnal[S - 1] ^= 1;
        }

        x[0] = sygnal[2];
        x[1] = sygnal[4];
        x[2] = sygnal[5];
        x[3] = sygnal[6];

        return x;
    }

    public static void cwiczenie1() {
        int[] sygnal = {1, 1, 0, 1};

        System.out.print("Sygnal pierwotny:  ");

        for (int i = 0; i < sygnal.length; i++) {
            System.out.print(sygnal[i] + " ");
        }

        int[] zakodowany = koderHamminga7i4(sygnal);

        System.out.print("\nSygnal zakodowany: ");

        for (int i = 0; i < zakodowany.length; i++) {
            System.out.print(zakodowany[i] + " ");
        }

        // PRZYPADEK I
        // bez zmian

        int[] zdekodowany1 = dekoderHamminga7i4(zakodowany);

        System.out.println("\n\nPrzypadek I - bez zmian");
        System.out.print("Sygnal przed: ");

        for (int i = 0; i < sygnal.length; i++) {
            System.out.print(sygnal[i] + " ");
        }

        System.out.print("\nSygnal po:    ");

        for (int i = 0; i < zdekodowany1.length; i++) {
            System.out.print(zdekodowany1[i] + " ");
        }

        // PRZYPADEK II
        // jeden losowy bit jest negowany

        Random random = new Random();
        int randomNumber = random.nextInt(7);

        System.out.println("\n\nLosowy bit przed: " + zakodowany[randomNumber]);

        // negacja losowego bitu
        zakodowany[randomNumber] ^= 1;

        System.out.println("Losowy bit po   : " + zakodowany[randomNumber]);

        int[] zdekodowany2 = dekoderHamminga7i4(zakodowany);

        System.out.println("\nPrzypadek II - jeden losowy bit zanegowany");
        System.out.print("Sygnal przed: ");

        for (int i = 0; i < sygnal.length; i++) {
            System.out.print(sygnal[i] + " ");
        }

        System.out.print("\nSygnal po:    ");

        for (int i = 0; i < zdekodowany2.length; i++) {
            System.out.print(zdekodowany2[i] + " ");
        }
    }

    public static int[][] generujMacierzP() {
        int[][] P = new int[11][4];
        int offset;

        for (int i = 0; i < 4; i++) {
            for (int j = 1; j <= 15; j++) {
                if (j != 1 && j != 2 && j != 4 && j != 8) {
                    if (j > 8) {
                        offset = 4;
                    } else if (j > 4) {
                        offset = 3;
                    } else {
                        offset = 2;
                    }

                    P[j - offset - 1][i] = (j >> i) % 2;
                }
            }
        }

        return P;
    }

    public static int[][] generujMacierzI(int n) {
        int[][] I = new int[n][n];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                I[i][j] = i == j ? 1 : 0;
            }
        }

        return I;
    }

    public static int[] koderHamminga15i11(int[] sygnal) {
        int[][] P = generujMacierzP();

        int[][] I = generujMacierzI(11);

        int[][] G = new int[11][4 + 11];

        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 15; j++) {
                if (j < 4) {
                    G[i][j] = P[i][j];
                } else {
                    G[i][j] = I[i][j-4];
                }
            }
        }

        int[] c = new int[15];

        for (int i = 0; i < 15; i++) {
            c[i] = 0;

            for(int j = 0; j < 11; j++) {
                c[i] += sygnal[j] * G[j][i];
            }

            c[i] %= 2;
        }

        return c;
    }

    public static int[][] transponujMacierz(int[][] macierz) {
        int iloscWierszy = macierz.length;
        int iloscKolumn = macierz[0].length;
        int[][] macierzTransponowana = new int[iloscKolumn][iloscWierszy];

        for (int i = 0; i < iloscKolumn; i++) {
            for (int j = 0; j < iloscWierszy; j++) {
                macierzTransponowana[i][j] = macierz[j][i];
            }
        }

        return macierzTransponowana;
    }

    public static int[] dekoderHamminga15i11(int[] c) {

        int[][] P = generujMacierzP();
        int[][] I = generujMacierzI(4);

        int[][] PT = transponujMacierz(P);

        int[][] H = new int[4][11 + 4];

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 15; j++) {
                if (j < 4) {
                    H[i][j] = I[i][j];
                } else {
                    H[i][j] = PT[i][j-4];
                }
            }
        }

        int[][] HT = transponujMacierz(H);

        int[] s = new int[4];

        for (int i = 0; i < 4; i++) {
            s[i] = 0;

            for (int j = 0; j < 15; j++) {
                s[i] += c[j] * HT[j][i];
            }

            s[i] %= 2;
        }

        int S = (int) (s[0] * Math.pow(2, 0) + s[1] * Math.pow(2, 1) + s[2] * Math.pow(2, 2) + s[3] * Math.pow(2, 3));

        int[] newC = new int[15];

        newC[0] = c[0];
        newC[1] = c[1];
        newC[2] = c[4];
        newC[3] = c[2];
        newC[4] = c[5];
        newC[5] = c[6];
        newC[6] = c[7];
        newC[7] = c[3];
        newC[8] = c[8];
        newC[9] = c[9];
        newC[10] = c[10];
        newC[11] = c[11];
        newC[12] = c[12];
        newC[13] = c[13];
        newC[14] = c[14];

        c = newC;

        if (S != 0) {
            c[S - 1] ^= 1;
        }

        // Pomijamy bity parzystosci i zwracamy tylko bity informacyjne
        int[] x = new int[11];

        x[0] = c[2];
        x[1] = c[4];
        x[2] = c[5];
        x[3] = c[6];
        x[4] = c[8];
        x[5] = c[9];
        x[6] = c[10];
        x[7] = c[11];
        x[8] = c[12];
        x[9] = c[13];
        x[10] = c[14];


        return x;
    }

    public static void cwiczenie2() {
        int[] sygnal = {1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0};

        System.out.print("Sygnal pierwotny:  ");

        for (int i = 0; i < sygnal.length; i++) {
            System.out.print(sygnal[i] + " ");
        }

        int[] zakodowany = koderHamminga15i11(sygnal);

        System.out.print("\nSygnal zakodowany: ");

        for (int i = 0; i < zakodowany.length; i++) {
            System.out.print(zakodowany[i] + " ");
        }

        // PRZYPADEK I
        // bez zmian

        int[] zdekodowany1 = dekoderHamminga15i11(zakodowany);

        System.out.println("\n\nPrzypadek I - bez zmian");
        System.out.print("Sygnal przed: ");

        for (int i = 0; i < sygnal.length; i++) {
            System.out.print(sygnal[i] + " ");
        }

        System.out.print("\nSygnal po:    ");

        for (int i = 0; i < zdekodowany1.length; i++) {
            System.out.print(zdekodowany1[i] + " ");
        }

        // PRZYPADEK II
        // jeden losowy bit jest negowany

        Random random = new Random();
        int randomNumber = random.nextInt(15);

        System.out.println("\n\nLosowy bit przed: " + zakodowany[randomNumber]);

        // negacja losowego bitu
        zakodowany[randomNumber] ^= 1;

        System.out.println("Losowy bit po   : " + zakodowany[randomNumber]);

        int[] zdekodowany2 = dekoderHamminga15i11(zakodowany);

        System.out.println("\nPrzypadek II - jeden losowy bit zanegowany");
        System.out.print("Sygnal przed: ");

        for (int i = 0; i < sygnal.length; i++) {
            System.out.print(sygnal[i] + " ");
        }

        System.out.print("\nSygnal po:    ");

        for (int i = 0; i < zdekodowany2.length; i++) {
            System.out.print(zdekodowany2[i] + " ");
        }
    }

    public static void main(String[] args) {
        //cwiczenie1();
        cwiczenie2();
    }
}
