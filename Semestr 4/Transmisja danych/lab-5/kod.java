package org.zut.lab5;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.NumberAxis;
import org.jfree.chart.plot.XYPlot;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;
import org.zut.lab2.Lab2;

import javax.swing.*;
import java.awt.*;
import java.util.Arrays;

import static org.zut.lab4.Lab4.*;

public class Lab5 {
    public static double[] obliczanieSygnaluP(double[] sygnal, float fs, float tb, float A, float fn, String nazwa) {
        double ts = 1 / fs;

        plotSignal(sygnal, fs, nazwa + "_z");

        // SYGNAL X

        double[] sygnalX = new double[sygnal.length];

        for (int n = 0; n < sygnal.length; n++) {
            double t = n * ts;

            sygnalX[n] = sygnal[n] * (A * Math.sin(2 * Math.PI * fn * t));
        }

        plotSignal(sygnalX, fs, nazwa + "_x");

        // SYGNAL P

        int ileProbek = (int)(fs * tb);
        double[] sygnalP = new double[sygnal.length];
        int counter = 0;

        for (int n = 0; n < sygnal.length; n++) {
            if (counter % ileProbek == 0) {
                sygnalP[n] = 0;
                counter++;
                continue;
            }

            sygnalP[n] = sygnalP[n-1] + sygnalX[n];
            counter++;
        }

        plotSignal(sygnalP, fs, nazwa + "_p");

        return sygnalP;
    }

    public static double[] demodulacjaASK(double[] sygnal, float fn, float A, float fs, float tb) {
        double[] sygnalP = obliczanieSygnaluP(sygnal, fs, tb, A, fn, "ask");

        double maxP = Double.MIN_VALUE;
        for (double value : sygnalP) {
            maxP = Math.max(maxP, value);
        }

        double h = 0.4 * maxP;

        // Moglbyc int ale funkcja plotujaca dziala na double
        double[] sygnalC = new double[sygnal.length];

        for (int n = 0; n < sygnal.length; n++) {
            if (sygnalP[n] > h) {
                sygnalC[n] = 1;
            } else {
                sygnalC[n] = 0;
            }
        }

        plotSignal(sygnalC, fs, "ask_c");

        return sygnalC;
    }

    public static double[] demodulacjaPSK(double[] sygnal, float fn, float A, float fs, float tb) {
        double[] sygnalP = obliczanieSygnaluP(sygnal, fs, tb, A, fn, "psk");

        double[] sygnalC = new double[sygnal.length];

        for (int n = 0; n < sygnal.length; n++) {
            if (sygnalP[n] < 0) {
                sygnalC[n] = 1;
            } else {
                sygnalC[n] = 0;
            }
        }

        plotSignal(sygnalC, fs, "psk_c");

        return sygnalC;
    }

    public static double[] demodulacjaFSK(double[] sygnal, float tb, float fs, float W, int tc) {
        float fn1 = (W + 1) / tb;
        float fn2 = (W + 2) / tb;
        float A = 1;

        double[] sygnalP1 = obliczanieSygnaluP(sygnal, fs, tb, A, fn1, "fsk1");
        double[] sygnalP2 = obliczanieSygnaluP(sygnal, fs, tb, A, fn2, "fsk2");

        double[] sygnalP = new double[sygnal.length];

        for (int i = 0; i < sygnalP1.length; i++) {
            sygnalP[i] = sygnalP2[i] - sygnalP1[i];
        }

        plotSignal(sygnalP, fs, "fsk_p");

        double[] sygnalC = new double[sygnal.length];

        for (int n = 0; n < sygnal.length; n++) {
            if (sygnalP[n] > 0) {
                sygnalC[n] = 1;
            } else {
                sygnalC[n] = 0;
            }
        }

        plotSignal(sygnalC, fs, "fsk_c");

        return sygnalC;
    }

    // Ta sama funkcja z poprzednich labow, bo przycina gdy y = 0
    // wiec musialem ja po raz kolejny przerobic
    public static void plotSignal(double[] sygnal, float fs, String name) {
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

        // Kod z chatu GPT, by dobrze ustawic zakres osi y
        double minY = Double.MAX_VALUE;
        double maxY = -Double.MAX_VALUE;
        for (double value : sygnal) {
            minY = Math.min(minY, value);
            maxY = Math.max(maxY, value);
        }

        NumberAxis yAxis = (NumberAxis) plot.getRangeAxis();
        double range = maxY - minY;
        double padding = range * 0.1;
        yAxis.setRange(minY - padding, maxY + padding);


        plot.getRenderer().setSeriesPaint(0, Color.RED);

        ChartPanel chartPanel = new ChartPanel(chart);
        chartPanel.setPreferredSize(new Dimension(800, 600));

        JFrame frame = new JFrame("Signal Plot");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().add(chartPanel);
        frame.pack();
        frame.setVisible(true);

        Lab2.saveChartAsPNG(chart, name);
    }

    public static int[] sygnalCnaCiagBitow(double[] sygnal, float fs, float tb) {
        int ileProbek = (int)(fs * tb);
        int sumTemp = 0;
        int[] ciagBitow = new int[sygnal.length / ileProbek];

        for (int n = 0; n < ciagBitow.length; n++) {
            for (int i = 0; i < ileProbek; i++) {
                if (sygnal[n * ileProbek + i] == 1) {
                    sumTemp++;
                }
            }

            if ((double) sumTemp / ileProbek > 0.5) {
                ciagBitow[n] = 1;
            } else {
                ciagBitow[n] = 0;
            }

            sumTemp = 0;
        }

        return ciagBitow;
    }

    public static void porownajStrumienieBitoweTekstowo(int[] input, int[] output, String nazwa) {
        System.out.println("\n\n" + nazwa);
        System.out.print("Przed demulacja: ");

        for (int i = 0; i < input.length; i++) {
            System.out.print(input[i] + " ");
        }

        System.out.print("\nPo demodulacji:  ");

        for (int i = 0; i < output.length; i++) {
            System.out.print(output[i] + " ");
        }
    }

    public static double[] stworzSygnalZCiaguBitowego(int[] ciagBitowy, float fs, float tc, float tb) {
        double[] sygnal = new double[(int)(fs * tc)];

        double ileProbek = fs * tb;

        for (int n = 0; n < ciagBitowy.length; n++) {
            if (ciagBitowy[n] == 1) {
                for (int i = 0; i < ileProbek; i++) {
                    sygnal[(int) (n * ileProbek + i)] = 1;
                }
            } else {
                for (int i = 0; i < ileProbek; i++) {
                    sygnal[(int) (n * ileProbek + i)] = 0;
                }
            }
        }

        return sygnal;
    }

    public static void plotSignals(double[] signal1, double[] signal2, float fs, String name) {
        XYSeries series1 = new XYSeries("Signal 1");
        XYSeries series2 = new XYSeries("Signal 2");

        float ts = 1 / fs;
        for (int i = 0; i < signal1.length; i++) {
            double t = i * ts;
            series1.add(t, signal1[i]);
            series2.add(t, signal2[i]);
        }

        XYSeriesCollection dataset = new XYSeriesCollection();
        dataset.addSeries(series1);
        dataset.addSeries(series2);

        JFreeChart chart = ChartFactory.createXYLineChart(
                name,
                "Czas (s)",
                "Amplituda",
                dataset
        );

        XYPlot plot = chart.getXYPlot();

        double minY = Math.min(Arrays.stream(signal1).min().getAsDouble(), Arrays.stream(signal2).min().getAsDouble());
        double maxY = Math.max(Arrays.stream(signal1).max().getAsDouble(), Arrays.stream(signal2).max().getAsDouble());
        double range = maxY - minY;
        double padding = range * 0.1;
        NumberAxis yAxis = (NumberAxis) plot.getRangeAxis();
        yAxis.setRange(minY - padding, maxY + padding);

        plot.getRenderer().setSeriesPaint(0, Color.RED);
        plot.getRenderer().setSeriesPaint(1, Color.BLUE);

        ChartPanel chartPanel = new ChartPanel(chart);
        chartPanel.setPreferredSize(new Dimension(800, 600));

        JFrame frame = new JFrame("Signal Plot");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().add(chartPanel);
        frame.pack();
        frame.setVisible(true);

        // Czekamy 2 sekundy, by wykres zdarzyl sie narysowac przed zapisem, bo
        // inaczej wywala blad
        try {
            Thread.sleep(2000);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }

        Lab2.saveChartAsPNG(chart, name);
    }


    public static void main(String[] args) {
        String stringDoZamiany = "Test";
        int[] strumienBitowy = zamienASCIInaBitowy(stringDoZamiany);

        int B = strumienBitowy.length;
        int tc = 1;
        int W = 1;
        float tb = (float)tc/B;
        float A1 = 2;
        float A2 = 6;
        float fn = W * (1/tb);
        int fs = 8000;

        // ASK

        double[] sygnalKluczowanyAmplituda = kluczowanieAmplitudy(strumienBitowy, A1, A2, fn, tb, fs, tc);
        double[] zdemodulowanyASK = demodulacjaASK(sygnalKluczowanyAmplituda, fn, 2, fs, tb);
        int[] ciagBitowASK = sygnalCnaCiagBitow(zdemodulowanyASK, fs, tb);
        porownajStrumienieBitoweTekstowo(strumienBitowy, ciagBitowASK, "ASK");

        // PSK

        double[] sygnalKluczowanyFaza = kluczowanieFazy(strumienBitowy, fn, tb, fs, tc);
        double[] zdemodulowanyPSK = demodulacjaPSK(sygnalKluczowanyFaza, fn, 2, fs, tb);
        int[] ciagBitowPSK = sygnalCnaCiagBitow(zdemodulowanyPSK, fs, tb);
        porownajStrumienieBitoweTekstowo(strumienBitowy, ciagBitowPSK, "PSK");

        // FSK

        double[] sygnalKluczowanyCzestotliwosc = kluczowanieCzestotliwosci(strumienBitowy, tb, fs, W, tc);
        double[] zdemodulowanyFSK = demodulacjaFSK(sygnalKluczowanyCzestotliwosc, tb, fs, W, tc);
        int[] ciagBitowFSK = sygnalCnaCiagBitow(zdemodulowanyFSK, fs, tb);
        porownajStrumienieBitoweTekstowo(strumienBitowy, ciagBitowFSK, "FSK");

        double[] sygnalPoczatkowy = stworzSygnalZCiaguBitowego(strumienBitowy, fs, tc, tb);
        double[] sygnalPoDemodulacjiASK = stworzSygnalZCiaguBitowego(ciagBitowASK, fs, tc, tb);
        double[] sygnalPoDemodulacjiPSK = stworzSygnalZCiaguBitowego(ciagBitowPSK, fs, tc, tb);
        double[] sygnalPoDemodulacjiFSK = stworzSygnalZCiaguBitowego(ciagBitowFSK, fs, tc, tb);

        plotSignals(sygnalPoczatkowy, sygnalPoDemodulacjiASK, fs, "porownanie_ask");
        plotSignals(sygnalPoczatkowy, sygnalPoDemodulacjiPSK, fs, "porownanie_psk");
        plotSignals(sygnalPoczatkowy, sygnalPoDemodulacjiFSK, fs, "porownanie_fsk");
    }
}
