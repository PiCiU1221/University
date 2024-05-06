package org.zut.lab1.zadanie2;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.XYPlot;
import org.jfree.data.xy.DefaultXYDataset;

import javax.swing.*;
import java.awt.*;
import java.io.File;
import java.io.IOException;

public class Lab1Zadanie2 {

    private static final float TC = 2;
    private static final float FS = 8000;
    private static final float N = TC * FS;
    private static final float PHI = 2;
    private static final float TS = 1 / FS;
    private static final float F = 2;

    public static void plotFunctions() {
        plotFunction(generateDataY(), "y");
        plotFunction(generateDataZ(), "z");
        plotFunction(generateDataV(), "v");
    }

    public static void plotFunction(double[][] data, String fileName) {
        DefaultXYDataset dataset = new DefaultXYDataset();
        dataset.addSeries("Function", data);

        JFreeChart chart = ChartFactory.createXYLineChart(
                fileName,
                "Czas [s]",
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

    private static double[][] generateDataY() {
        float t = 0;

        double xFunction = 0.0;

        double[][] data = new double[2][(int)N];
        for (int n = 0; n < N; n++) {
            t = n * TS;

            xFunction = Math.cos(2 * Math.PI * F * t + PHI) * Math.cos(2.5 * Math.pow(t, 0.2) * Math.PI);

            data[0][n] = t;
            data[1][n] = (xFunction * t)/(3 + Math.cos(20 * Math.PI * t));
        }
        return data;
    }

    private static double[][] generateDataZ() {
        float t = 0;

        double xFunction = 0;
        double yFunction = 0;

        double[][] data = new double[2][(int)N];
        for (int n = 0; n < N; n++) {
            t = n * TS;

            xFunction = Math.cos(2 * Math.PI * F * t + PHI) * Math.cos(2.5 * Math.pow(t, 0.2) * Math.PI);
            yFunction = (xFunction * t)/(3 + Math.cos(20 * Math.PI * t));

            data[0][n] = t;
            data[1][n] = Math.pow(t, 2) * Math.abs(xFunction * yFunction - (2/(10 + yFunction)));
        }
        return data;
    }

    private static double[][] generateDataV() {
        float t = 0;

        double xFunction = 0;
        double yFunction = 0;
        double zFunction = 0;

        double[][] data = new double[2][(int)N];
        for (int n = 0; n < N; n++) {
            t = n * TS;

            xFunction = Math.cos(2 * Math.PI * F * t + PHI) * Math.cos(2.5 * Math.pow(t, 0.2) * Math.PI);
            yFunction = (xFunction * t)/(3 + Math.cos(20 * Math.PI * t));
            zFunction = Math.pow(t, 2) * Math.abs(xFunction * yFunction - (2/(10 + yFunction)));

            data[0][n] = t;
            data[1][n] = Math.pow(zFunction, 3) + 3 * Math.sin(zFunction * yFunction) * Math.abs(yFunction - xFunction);
        }
        return data;
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
}