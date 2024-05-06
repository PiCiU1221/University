package org.zut.lab4;

import org.apache.commons.math3.complex.Complex;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.XYPlot;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;
import org.zut.lab2.Lab2;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.Arrays;

import static org.zut.lab2.Lab2.*;
import static org.zut.lab2.Lab2.obliczSkaleCzestotliwosci;
import static org.zut.lab3.Lab3.*;

public class Lab4 {
    public static int[] generujStrumienBitowy(int n) {
        int[] strumienBitowy = new int[n];

        for (int i = 0; i < n; i++) {
            int bit = Math.random() < 0.5 ? 0 : 1;
            strumienBitowy[i] = bit;
        }

        return strumienBitowy;
    }

    public static double[] kluczowanieAmplitudy(int[] strumienBitowy, float A1, float A2, float fn, float tb, float fs, int tc) {
        int dlugoscSygnalu = (int) (fs * tc);

        double[] sygnalAmplituda = new double[dlugoscSygnalu];
        double ts = 1 / fs;
        double ileProbek = fs * tb;

        double t;

        for (int n = 0; n < strumienBitowy.length; n++) {
            if (strumienBitowy[n] == 0) {
                for (int i = 0; i < ileProbek; i++) {
                    t = i * ts;

                    sygnalAmplituda[(int) (n * ileProbek + i)] = A1 * Math.sin(2 * Math.PI * fn * t);
                }
            } else {
                for (int i = 0; i < ileProbek; i++) {
                    t = i * ts;

                    sygnalAmplituda[(int) (n * ileProbek + i)] = A2 * Math.sin(2 * Math.PI * fn * t);
                }
            }
        }

        return sygnalAmplituda;
    }

    public static double[] kluczowanieFazy(int[] strumienBitowy, float fn, float tb, float fs, int tc) {
        int dlugoscSygnalu = (int) (fs * tc);

        double[] sygnalFaza = new double[dlugoscSygnalu];
        double ts = 1 / fs;
        double ileProbek = fs * tb;
        double t;

        for (int n = 0; n < strumienBitowy.length; n++) {
            if (strumienBitowy[n] == 0) {
                for (int i = 0; i < ileProbek; i++) {
                    t = i * ts;

                    sygnalFaza[(int) (n * ileProbek + i)] = Math.sin(2 * Math.PI * fn * t);
                }
            } else {
                for (int i = 0; i < ileProbek; i++) {
                    t = i * ts;

                    sygnalFaza[(int) (n * ileProbek + i)] = Math.sin(2 * Math.PI * fn * t + Math.PI);
                }
            }
        }

        return sygnalFaza;
    }

    public static double[] kluczowanieCzestotliwosci(int[] strumienBitowy, float tb, float fs, float W, int tc) {
        int dlugoscSygnalu = (int) (fs * tc);

        double[] sygnalCzestotliwosc = new double[dlugoscSygnalu];
        double ts = 1 / fs;
        double ileProbek = fs * tb;
        double t;

        double fn1 = (W + 1) / tb;
        double fn2 = (W + 2) / tb;

        for (int n = 0; n < strumienBitowy.length; n++) {
            if (strumienBitowy[n] == 0) {
                for (int i = 0; i < ileProbek; i++) {
                    t = i * ts;

                    sygnalCzestotliwosc[(int) (n * ileProbek + i)] = Math.sin(2 * Math.PI * fn1 * t);
                }
            } else {
                for (int i = 0; i < ileProbek; i++) {
                    t = i * ts;

                    sygnalCzestotliwosc[(int) (n * ileProbek + i)] = Math.sin(2 * Math.PI * fn2 * t);
                }
            }
        }
        return sygnalCzestotliwosc;
    }

    public static void plotSignals(double[] sygnal, float fs, String name) {
        XYSeries series = new XYSeries("Sygnal");

        float ts = 1 / fs;
        for (int i = 0; i < sygnal.length; i++) {
            double t = i * ts;
            series.add(t, sygnal[i]);
        }

        XYSeriesCollection dataset = new XYSeriesCollection();
        dataset.addSeries(series);

        JFreeChart chart = ChartFactory.createXYLineChart(
                name,
                "Czas (s)",
                "Amplituda",
                dataset
        );

        XYPlot plot = chart.getXYPlot();
        plot.getRenderer().setSeriesPaint(0, Color.RED);
        plot.getRenderer().setSeriesPaint(1, Color.BLUE);

        ChartPanel chartPanel = new ChartPanel(chart);
        chartPanel.setPreferredSize(new Dimension(800, 600));

        JFrame frame = new JFrame("Signal Plot");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().add(chartPanel);
        frame.pack();
        frame.setVisible(true);

        //Lab2.saveChartAsPNG(chart, name);
    }

    public static double obliczSzerokoscPasma(double[] sygnal, float tc, float fs, double czestotliwoscPasma) {
        Complex[] X = FFT(sygnal);
        double[] M = obliczWidmoAmplitudowe(X, sygnal.length);
        double[] MdB = przedstawJakoSkalaDecybelowa(M);
        double[] f = obliczSkaleCzestotliwosci(tc, fs);

        double maxAmplituda = Double.NEGATIVE_INFINITY;

        // Znajdź maksymalną amplitudę w skali decybelowej
        for (int i = 0; i < MdB.length; i++) {
            if (MdB[i] > maxAmplituda) {
                maxAmplituda = MdB[i];
            }
        }

        // Znajdz pierwsza czestotliwosc ktora spelnia warunek dB
        double pierwszaCzestotliwosc = 0;
        for (int i = 0; i < MdB.length; i++) {
            if (MdB[i] >= maxAmplituda * czestotliwoscPasma) {
                pierwszaCzestotliwosc = f[i];
                break;
            }
        }

        // Znajdz ostatnia czestotliwosc ktora spelnia warunek dB
        double ostatniaCzestotliwosc = 0;
        for (int i = 1; i < MdB.length; i++) {
            if (MdB[i] >= maxAmplituda * czestotliwoscPasma) {
                ostatniaCzestotliwosc = f[i];
            }
        }

        // Odejmij ostatnia czestotliwosc od pierwszej i mamy szerokosc naszego pasma
        return ostatniaCzestotliwosc - pierwszaCzestotliwosc;
    }

    // pomoc chatu GPT przy zamianie char na int
    public static int[] zamienASCIInaBitowy(String napis) {
        int[] strumienBitowy = new int[napis.length() * 7];

        for (int i = 0; i < napis.length(); i++) {
            char character = napis.charAt(i);
            for (int j = 0; j < 7; j++) {
                strumienBitowy[(i * 7) + (6 - j)] = (character & (1 << j)) != 0 ? 1 : 0;
            }
        }

        return strumienBitowy;
    }

    private static void obliczSzerokoscPasma(String nazwa, double[] signal, int tc, int fs) {
        double szerokoscPasma3dB = obliczSzerokoscPasma(signal, tc, fs, 1f/2);
        double szerokoscPasma6dB = obliczSzerokoscPasma(signal, tc, fs, 1f/4);
        double szerokoscPasma12dB = obliczSzerokoscPasma(signal, tc, fs, 1f/16);

        System.out.println("\n" + nazwa + ":");
        System.out.println("Szerokość pasma 3 dB: " + szerokoscPasma3dB + " Hz");
        System.out.println("Szerokość pasma 6 dB: " + szerokoscPasma6dB + " Hz");
        System.out.println("Szerokość pasma 12 dB: " + szerokoscPasma12dB + " Hz");
    }

    public static void main(String[] args) {
        String stringDoZamiany = "Test";
        int[] strumienBitowy = zamienASCIInaBitowy(stringDoZamiany);

        int B = strumienBitowy.length;
        int tc = 1;
        int W = 1;
        float tb = (float)tc/B;
        float A1 = 2;
        float A2 = 8;
        float fn = W * (1/tb);
        int fs = 8000;

        double[] sygnalKluczowanyAmplituda = kluczowanieAmplitudy(strumienBitowy, A1, A2, fn, tb, fs, tc);
        double[] sygnalKluczowanyFaza = kluczowanieFazy(strumienBitowy, fn, tb, fs, tc);
        double[] sygnalKLuczowanyCzestotliwosc = kluczowanieCzestotliwosci(strumienBitowy, tb, fs, W, tc);

        plotSignals(sygnalKluczowanyAmplituda, fs, "za");
        plotSignals(sygnalKluczowanyFaza, fs, "zp");
        plotSignals(sygnalKLuczowanyCzestotliwosc, fs, "zf");

        System.out.println("\nStrumien bitowy:");
        for (int i = 0; i < strumienBitowy.length; i++) {
            System.out.print(strumienBitowy[i] + " ");
        }
        System.out.print("\n");

        Lab2.wykreslWykresWidma(sygnalKluczowanyAmplituda, "za_widmo", tc, fs, true);
        Lab2.wykreslWykresWidma(sygnalKluczowanyFaza, "zp_widmo", tc, fs, true);
        Lab2.wykreslWykresWidma(sygnalKLuczowanyCzestotliwosc, "zf_widmo", tc, fs, true);

        obliczSzerokoscPasma("ASK", sygnalKluczowanyAmplituda, tc, fs);
        obliczSzerokoscPasma("PSK", sygnalKluczowanyFaza, tc, fs);
        obliczSzerokoscPasma("FSK", sygnalKLuczowanyCzestotliwosc, tc, fs);

//        String testString = "Testowanie";
//        int[] testStringInASCII = zamienASCIInaBitowy(testString);
//        System.out.println("\n" + testString);
//
//        for (int i = 0; i < testStringInASCII.length / 7; i++) {
//            for (int j = i * 7; j < (i * 7) + 7; j++) {
//                System.out.print(testStringInASCII[j]);
//            }
//            System.out.print(" ");
//        }
    }
}