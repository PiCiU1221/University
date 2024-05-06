package org.zut.lab1.zadanie4;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.XYPlot;
import org.jfree.data.xy.DefaultXYDataset;

import javax.swing.*;
import java.awt.*;
import java.io.File;
import java.io.IOException;

public class Lab1Zadanie4 {

    private static final float TC = 1;
    private static final float FS = 22050;
    private static final float N = TC * FS;
    private static final float TS = 1 / FS;

    public static void plotFunctions() {
        plotFunction(generateDataB1(), "b1");
        plotFunction(generateDataB2(), "b2");
        plotFunction(generateDataB3(), "b3");
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

    private static double[][] generateDataB1() {
        float t = 0;

        double[][] data = new double[2][(int)N];
        for (int n = 0; n < N; n++) {
            t = n * TS;

            double result = 0;

            for (int h = 1; h <= 5; h++) {
                result += (Math.pow(-1,h)/h) * Math.sin(h * Math.PI * 2 * t);
            }

            result *= 2/Math.PI;

            data[0][n] = t;
            data[1][n] = result;
        }
        return data;
    }

    private static double[][] generateDataB2() {
        float t = 0;

        double[][] data = new double[2][(int)N];
        for (int n = 0; n < N; n++) {
            t = n * TS;

            double result = 0;

            for (int h = 1; h <= 20; h++) {
                result += (Math.pow(-1,h)/h) * Math.sin(h * Math.PI * 2 * t);
            }

            result *= 2/Math.PI;

            data[0][n] = t;
            data[1][n] = result;
        }
        return data;
    }

    private static double[][] generateDataB3() {
        float t = 0;

        double[][] data = new double[2][(int)N];
        for (int n = 0; n < N; n++) {
            t = n * TS;

            double result = 0;

            for (int h = 1; h <= 50; h++) {
                result += (Math.pow(-1,h)/h) * Math.sin(h * Math.PI * 2 * t);
            }

            result *= 2/Math.PI;

            data[0][n] = t;
            data[1][n] = result;
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