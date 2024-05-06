package org.zut.lab3;

import org.apache.commons.math3.complex.Complex;
import org.zut.lab2.Lab2;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.XYPlot;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

import javax.swing.*;
import java.awt.*;

import static org.zut.lab2.Lab2.*;

public class Lab3 {
    public static double[] wygenerujSygnalX(float f, float tc, float fs) {
        // tc - czas trwanie sygnalu w sekundach
        // fs - czestotliwosc probkowania w Hz

        // N - laczna ilosc probek sygnalu
        float N = tc * fs;
        if (tc % 1 != 0) {
            N = Math.round(N);
        }

        // okres probkowania
        float ts = 1 / fs;
        float t;


        double[] sygnal = new double[(int)N];
        for (int n = 0; n < N; n++) {
            t = n * ts;

            sygnal[n] = Math.sin(2 * Math.PI * f * t);
        }

        return sygnal;
    }

    public static double[] modyfikujAmplitudowo(double[] sygnal, double ka, double fn, double fs) {
        double[] sygnalAmplituda = new double[sygnal.length];
        double ts = 1 / fs;

        for (int n = 0; n < sygnal.length; n++) {
            double t = n * ts;

            sygnalAmplituda[n] = (ka * sygnal[n] + 1) * Math.cos(2 * Math.PI * fn * t);
        }

        return sygnalAmplituda;
    }

    public static double[] modyfikujFazowo(double[] sygnal, double kp, double fn, double fs) {
        double[] sygnalFaza = new double[sygnal.length];
        double ts = 1 / fs;

        for (int n = 0; n < sygnal.length; n++) {
            double t = n * ts;

            sygnalFaza[n] = Math.cos(2 * Math.PI * fn * t + kp * sygnal[n]);
        }

        return sygnalFaza;
    }

    public static double[] modyfikujCzestotliwosciowo(double[] sygnal, double kf, double fn, double fm, double fs) {
        double[] sygnalCzestotliwosc = new double[sygnal.length];
        double ts = 1 / fs;

        for (int n = 0; n < sygnal.length; n++) {
            double t = n * ts;

            sygnalCzestotliwosc[n] = Math.cos(2 * Math.PI * fn * t + kf/fm * sygnal[n]);
        }

        return sygnalCzestotliwosc;
    }

    // pomoc chatu GPT bo szybciej
    public static void plotSignals(double[] signal1, double[] signal2, float fs, String name) {
        XYSeries series1 = new XYSeries("Original Signal");
        XYSeries series2 = new XYSeries("Modified Signal");

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

    private static void generujModulacje() {
        float tc = 2;
        float fs = 8000;
        float fm = 15;
        float fn = 500;

        double[] sygnal = wygenerujSygnalX(fm, tc, fs);
        plotSignals(sygnal, sygnal, fs, "Signal startowy");

        // a)
        double ka = 0.5;
        double kp = 0.5;
        double kf = 0.5;

        double[] sygnalAmplitudowo = modyfikujAmplitudowo(sygnal, ka, fn, fs);
        plotSignals(sygnal, sygnalAmplitudowo, fs, "za_a");
        Lab2.wykreslWykresWidma(sygnalAmplitudowo, "za_a_widmo", tc, fs, true);

        double[] sygnalFazowo = modyfikujFazowo(sygnal, kp, fn, fs);
        plotSignals(sygnal, sygnalFazowo, fs, "zp_a");
        Lab2.wykreslWykresWidma(sygnalFazowo, "zp_a_widmo", tc, fs, true);

        double[] sygnalCzestotliwosciowo = modyfikujCzestotliwosciowo(sygnal, kf, fn, fm, fs);
        plotSignals(sygnal, sygnalCzestotliwosciowo, fs, "zf_a");
        Lab2.wykreslWykresWidma(sygnalCzestotliwosciowo, "zf_a_widmo", tc, fs, true);

        // b)
        ka = 8;
        kp = 1.5;
        kf = 1.5;

        sygnalAmplitudowo = modyfikujAmplitudowo(sygnal, ka, fn, fs);
        plotSignals(sygnal, sygnalAmplitudowo, fs, "za_b");
        Lab2.wykreslWykresWidma(sygnalAmplitudowo, "za_b_widmo", tc, fs, true);

        sygnalFazowo = modyfikujFazowo(sygnal, kp, fn, fs);
        plotSignals(sygnal, sygnalFazowo, fs, "zp_b");
        Lab2.wykreslWykresWidma(sygnalFazowo, "zp_b_widmo", tc, fs, true);

        sygnalCzestotliwosciowo = modyfikujCzestotliwosciowo(sygnal, kf, fn, fm, fs);
        plotSignals(sygnal, sygnalCzestotliwosciowo, fs, "zf_b");
        Lab2.wykreslWykresWidma(sygnalCzestotliwosciowo, "zf_b_widmo", tc, fs, true);

        // c)
        ka = 25;
        kp = 3 * Math.PI;
        kf = 3 * Math.PI;

        sygnalAmplitudowo = modyfikujAmplitudowo(sygnal, ka, fn, fs);
        plotSignals(sygnal, sygnalAmplitudowo, fs, "za_c");
        Lab2.wykreslWykresWidma(sygnalAmplitudowo, "za_c_widmo", tc, fs, true);

        sygnalFazowo = modyfikujFazowo(sygnal, kp, fn, fs);
        plotSignals(sygnal, sygnalFazowo, fs, "zp_c");
        Lab2.wykreslWykresWidma(sygnalFazowo, "zp_c_widmo", tc, fs, true);

        sygnalCzestotliwosciowo = modyfikujCzestotliwosciowo(sygnal, kf, fn, fm, fs);
        plotSignals(sygnal, sygnalCzestotliwosciowo, fs, "zf_c");
        Lab2.wykreslWykresWidma(sygnalCzestotliwosciowo, "zf_c_widmo", tc, fs, true);
    }

    // poczatek i zamysl z chatu GPT (który sobie nie poradził z moim paskudnym, skaczącym
    // widmem i musiałem to robić sam)
    public static double obliczSzerokoscPasma(double[] MdB, double[] f, double czestotliwoscPasma) {
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

    private static void szacowaniePasm() {
        float tc = 2;
        float fs = 8000;
        float fm = 15;
        float fn = 500;

        double[] sygnal = wygenerujSygnalX(fm, tc, fs);

        double ka = 25;
        double kp = 3 * Math.PI;
        double kf = 3 * Math.PI;

        double[] sygnalAmplitudowo = modyfikujAmplitudowo(sygnal, ka, fn, fs);

        Complex[] X = FFT(sygnalAmplitudowo);
        double[] M = obliczWidmoAmplitudowe(X, sygnal.length);
        double[] MdB = przedstawJakoSkalaDecybelowa(M);
        double[] f = obliczSkaleCzestotliwosci(tc, fs);

        double szerokoscPasma3dB = obliczSzerokoscPasma(MdB, f, 1f/2);
        double szerokoscPasma6dB = obliczSzerokoscPasma(MdB, f, 1f/4);
        double szerokoscPasma12dB = obliczSzerokoscPasma(MdB, f, 1f/16);

        System.out.println("Modulacja amplitudowa:");
        System.out.println("Szerokość pasma 3 dB: " + szerokoscPasma3dB + " Hz");
        System.out.println("Szerokość pasma 6 dB: " + szerokoscPasma6dB + " Hz");
        System.out.println("Szerokość pasma 12 dB: " + szerokoscPasma12dB + " Hz");

        double[] sygnalFazowo = modyfikujFazowo(sygnal, kp, fn, fs);

        X = FFT(sygnalFazowo);
        M = obliczWidmoAmplitudowe(X, sygnal.length);
        MdB = przedstawJakoSkalaDecybelowa(M);
        f = obliczSkaleCzestotliwosci(tc, fs);

        szerokoscPasma3dB = obliczSzerokoscPasma(MdB, f, 1f/2);
        szerokoscPasma6dB = obliczSzerokoscPasma(MdB, f, 1f/4);
        szerokoscPasma12dB = obliczSzerokoscPasma(MdB, f, 1f/16);

        System.out.println("\nModulacja fazowa:");
        System.out.println("Szerokość pasma 3 dB: " + szerokoscPasma3dB + " Hz");
        System.out.println("Szerokość pasma 6 dB: " + szerokoscPasma6dB + " Hz");
        System.out.println("Szerokość pasma 12 dB: " + szerokoscPasma12dB + " Hz");

        double[] sygnalCzestotliwosciowo = modyfikujCzestotliwosciowo(sygnal, kf, fn, fm, fs);

        X = FFT(sygnalCzestotliwosciowo);
        M = obliczWidmoAmplitudowe(X, sygnal.length);
        MdB = przedstawJakoSkalaDecybelowa(M);
        f = obliczSkaleCzestotliwosci(tc, fs);

        szerokoscPasma3dB = obliczSzerokoscPasma(MdB, f, 1f/2);
        szerokoscPasma6dB = obliczSzerokoscPasma(MdB, f, 1f/4);
        szerokoscPasma12dB = obliczSzerokoscPasma(MdB, f, 1f/16);

        System.out.println("\nModulacja częstotliwościowa:");
        System.out.println("Szerokość pasma 3 dB: " + szerokoscPasma3dB + " Hz");
        System.out.println("Szerokość pasma 6 dB: " + szerokoscPasma6dB + " Hz");
        System.out.println("Szerokość pasma 12 dB: " + szerokoscPasma12dB + " Hz");
    }

    public static void main(String[] args) {
        generujModulacje();
        szacowaniePasm();
    }
}
