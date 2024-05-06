package org.zut.lab2;

import org.apache.commons.math3.complex.Complex;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.XYPlot;
import org.jfree.data.xy.DefaultXYDataset;

import javax.swing.*;
import java.awt.*;
import java.io.File;
import java.io.IOException;

public class Lab2 {

    public static double[] wygenerujSygnalX(float tc, float fs) {
        float N = tc * fs;
        float ts = 1 / fs;
        float phi = 2;
        float f = 2;
        float t;

        double[] signal = new double[(int)N];
        for (int n = 0; n < N; n++) {
            t = n * ts;

            signal[n] = Math.cos(2 * Math.PI * f * t + phi) * Math.cos(2.5 * Math.pow(t, 0.2) * Math.PI);
        }

        return signal;
    }

    public static double[] wygenerujSygnalY(float tc, float fs) {
        float N = tc * fs;
        float ts = 1 / fs;
        float phi = 2;
        float f = 2;
        float t;

        double xFunction = 0.0;

        double[] signal = new double[(int)N];
        for (int n = 0; n < N; n++) {
            t = n * ts;

            xFunction = Math.cos(2 * Math.PI * f * t + phi) * Math.cos(2.5 * Math.pow(t, 0.2) * Math.PI);

            signal[n] = (xFunction * t)/(3 + Math.cos(20 * Math.PI * t));
        }

        return signal;
    }

    public static double[] wygenerujSygnalZ(float tc, float fs) {
        float N = tc * fs;
        float ts = 1 / fs;
        float phi = 2;
        float f = 2;
        float t;

        double xFunction = 0;
        double yFunction = 0;

        double[] signal = new double[(int)N];
        for (int n = 0; n < N; n++) {
            t = n * ts;

            xFunction = Math.cos(2 * Math.PI * f * t + phi) * Math.cos(2.5 * Math.pow(t, 0.2) * Math.PI);
            yFunction = (xFunction * t)/(3 + Math.cos(20 * Math.PI * t));

            signal[n] = Math.pow(t, 2) * Math.abs(xFunction * yFunction - (2/(10 + yFunction)));
        }

        return signal;
    }

    public static double[] wygenerujSygnalV(float tc, float fs) {
        float N = tc * fs;
        float ts = 1 / fs;
        float phi = 2;
        float f = 2;
        float t;

        double xFunction = 0;
        double yFunction = 0;
        double zFunction = 0;

        double[] signal = new double[(int)N];
        for (int n = 0; n < N; n++) {
            t = n * ts;

            xFunction = Math.cos(2 * Math.PI * f * t + phi) * Math.cos(2.5 * Math.pow(t, 0.2) * Math.PI);
            yFunction = (xFunction * t)/(3 + Math.cos(20 * Math.PI * t));
            zFunction = Math.pow(t, 2) * Math.abs(xFunction * yFunction - (2/(10 + yFunction)));


            signal[n] = Math.pow(zFunction, 3) + 3 * Math.sin(zFunction * yFunction) * Math.abs(yFunction - xFunction);
        }

        return signal;
    }

    public static double[] wygenerujSygnalU(float tc, float fs) {
        float N = tc * fs;
        float ts = 1/fs;

        float t;

        double[] signal = new double[(int)N];
        for (int n = 0; n < N; n++) {
            t = n * ts;
            signal[n] = t;

            if (t >= 0 && t < 0.1) {
                signal[n] = Math.sin(6 * Math.PI * t) * Math.cos(5 * Math.PI * t);
            } else if (t >= 0.1 && t < 0.4) {
                signal[n] = -1.1 * t * Math.cos(41 * Math.PI * Math.pow(t, 2));
            } else if (t >= 0.4 && t < 0.72) {
                signal[n] = t * Math.sin(20 * Math.pow(t, 4));
            } else if (t >= 0.72 && t < 1) {
                signal[n] = 3.3 * (t - 0.72) * Math.cos(27 * t + 1.3);
            }
        }
        return signal;
    }

    public static double[] generateSignalB1(float tc, float fs) {
        float N = tc * fs;
        float ts = 1 / fs;
        float t;

        double[] signal = new double[(int)N];
        for (int n = 0; n < N; n++) {
            t = n * ts;

            double result = 0;

            for (int h = 1; h <= 5; h++) {
                result += (Math.pow(-1, h) / h) * Math.sin(h * Math.PI * 2 * t);
            }

            result *= 2 / Math.PI;

            signal[n] = result;
        }
        return signal;
    }

    public static double[] generateSignalB2(float tc, float fs) {
        float N = tc * fs;
        float ts = 1 / fs;
        float t;

        double[] signal = new double[(int) N];
        for (int n = 0; n < N; n++) {
            t = n * ts;

            double result = 0;

            for (int h = 1; h <= 20; h++) {
                result += (Math.pow(-1, h) / h) * Math.sin(h * Math.PI * 2 * t);
            }

            result *= 2 / Math.PI;

            signal[n] = result;
        }
        return signal;
    }

    public static double[] generateSignalB3(float tc, float fs) {
        float N = tc * fs;
        float ts = 1 / fs;
        float t;

        double[] signal = new double[(int) N];
        for (int n = 0; n < N; n++) {
            t = n * ts;

            double result = 0;

            for (int h = 1; h <= 50; h++) {
                result += (Math.pow(-1, h) / h) * Math.sin(h * Math.PI * 2 * t);
            }

            result *= 2 / Math.PI;

            signal[n] = result;
        }
        return signal;
    }

    public static Complex[] DFT(double[] X) {
        int N = X.length;
        Complex[] result = new Complex[N];
        double re, im;

        for (int k = 0; k < N; k++) {
            re = 0;
            im = 0;

            for (int n = 0; n < N; n++) {
                double angle = -2 * Math.PI * k * n / N;
                re += X[n] * Math.cos(angle);
                im -= X[n] * Math.sin(angle);
            }

            result[k] = new Complex(re, im);
        }

        return result;
    }

    public static double[] obliczWidmoAmplitudowe(Complex[] X) {
        int N = X.length / 2 - 1;
        double[] M = new double[N];

        for (int k = 0; k < N; k++) {
            M[k] = Math.sqrt(Math.pow(X[k].getReal(), 2) + Math.pow(X[k].getImaginary(), 2));
        }

        return M;
    }

    public static double[] przedstawJakoSkalaDecybelowa(double[] M) {
        int N = M.length;

        double[] MdB = new double[N];

        for (int k = 0; k < N; k++) {
            MdB[k] = 10 * Math.log10(M[k]);
        }

        return MdB;
    }

    public static double[] obliczSkaleCzestotliwosci(float tc, float fs) {
        float n = tc * fs;

        double[] f = new double[(int) n];

        for (int k = 0; k < n; k++) {
            f[k] = k * fs / n;
        }

        return f;
    }

    private static double[][] generateData(double[] M, double[] f) {

        int N = M.length;

        double[][] data = new double[2][N];
        for (int i = 0; i < N; i++) {
            data[0][i] = f[i];
            data[1][i] = M[i];
        }

        return data;
    }

    public static void plotFunction(double[][] data, String fileName) {
        DefaultXYDataset dataset = new DefaultXYDataset();
        dataset.addSeries("Function", data);

        JFreeChart chart = ChartFactory.createXYLineChart(
                fileName,
                "Czestotliwosc [Hz]",
                "Amplituda",
                dataset
        );

        chart.removeLegend();

        XYPlot plot = chart.getXYPlot();

        plot.getDomainAxis().setLowerBound(-0.1);

        // Calculate minimum Y value to lower the range axis
        double minY = Double.MAX_VALUE;
        for (double[] series : data) {
            for (double value : series) {
                minY = Math.min(minY, value);
            }
        }

        plot.getRangeAxis().setLowerBound(minY - 0.1);

        plot.getRenderer().setSeriesPaint(0, Color.RED);

        plot.setDomainCrosshairPaint(Color.BLACK);
        plot.setRangeCrosshairPaint(Color.BLACK);
        plot.setDomainCrosshairStroke(new BasicStroke(1.0f));
        plot.setRangeCrosshairStroke(new BasicStroke(1.0f));
        plot.setDomainCrosshairVisible(true);
        plot.setRangeCrosshairVisible(true);

        ChartPanel chartPanel = new ChartPanel(chart);
        chartPanel.setPreferredSize(new java.awt.Dimension(800, 600));

        JFrame frame = new JFrame("Graph");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().add(chartPanel);
        frame.pack();
        frame.setVisible(true);

        saveChartAsPNG(chart, fileName);
    }

    public static void wykreslWykresWidma(double[] signal, String name, float tc, float fs) {
        Complex[] X = DFT(signal);
        double[] M = obliczWidmoAmplitudowe(X);
        double[] MdB = przedstawJakoSkalaDecybelowa(M);
        double[] f = obliczSkaleCzestotliwosci(tc, fs);

        double[][] data = generateData(M, f);
        plotFunction(data, name);
    }

    private static void saveChartAsPNG(JFreeChart chart, String fileName) {

        String filePath = "src/main/java/org/zut/chart/" + fileName + ".png";
        try {
            File file = new File(filePath);
            org.jfree.chart.ChartUtils.saveChartAsPNG(file, chart, 800, 600);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        wykreslWykresWidma(wygenerujSygnalX(2, 8000), "x", 2, 8000);
       wykreslWykresWidma(wygenerujSygnalY(2, 8000), "y", 2, 8000);
       wykreslWykresWidma(wygenerujSygnalZ(2, 8000), "z", 2, 8000);
       wykreslWykresWidma(wygenerujSygnalV(2, 8000), "v", 2, 8000);
       wykreslWykresWidma(wygenerujSygnalU(1, 8000), "u", 1, 8000);
       wykreslWykresWidma(generateSignalB1(1, 22050), "b1", 1, 22050);
       wykreslWykresWidma(generateSignalB2(1, 22050), "b2", 1, 22050);
       wykreslWykresWidma(generateSignalB3(1, 22050), "b3", 1, 22050);
    }
}