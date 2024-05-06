package org.zut.lab1.zadanie1;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.XYPlot;
import org.jfree.data.xy.DefaultXYDataset;

import javax.swing.*;
import java.awt.*;
import java.io.File;
import java.io.IOException;

public class Lab1Zadanie1 {

    // Wybrano funkcje numer 1

    public static void plotFunction() {
        DefaultXYDataset dataset = new DefaultXYDataset();
        double[][] data = generateData();
        dataset.addSeries("Function", data);

        JFreeChart chart = ChartFactory.createXYLineChart(
                "x",
                "Czas [s]",
                "Amplituda",
                dataset
        );

        chart.removeLegend();

        XYPlot plot = chart.getXYPlot();

        plot.getDomainAxis().setLowerBound(-0.1);

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

        saveChartAsPNG(chart);
    }

    private static double[][] generateData() {
        float tc = 2;
        float fs = 8000;
        float N = tc * fs;
        float phi = 2;
        float ts = 1/fs;
        float t = 0;
        float f = 2;

        double[][] data = new double[2][(int)N];
        for (int n = 0; n < N; n++) {
            t = n * ts;
            data[0][n] = t;
            data[1][n] = Math.cos(2 * Math.PI * f * t + phi) * Math.cos(2.5 * Math.pow(t, 0.2) * Math.PI);
        }
        return data;
    }

    private static void saveChartAsPNG(JFreeChart chart) {

        String filePath = "src/main/java/org/zut/chart/x.png";
        try {
            File file = new File(filePath);
            org.jfree.chart.ChartUtils.saveChartAsPNG(file, chart, 800, 600);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}