package org.zut.lab1.zadanie3;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.XYPlot;
import org.jfree.data.xy.DefaultXYDataset;

import javax.swing.*;
import java.awt.*;
import java.io.File;
import java.io.IOException;

public class Lab1Zadanie3 {

    public static void plotFunction() {
        DefaultXYDataset dataset = new DefaultXYDataset();
        double[][] data = generateData();
        dataset.addSeries("Function", data);

        JFreeChart chart = ChartFactory.createXYLineChart(
                "u",
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
        float tc = 1;
        float fs = 8000;
        float N = tc * fs;
        float ts = 1/fs;

        float t = 0;

        double[][] data = new double[2][(int)N];
        for (int n = 0; n < N; n++) {
            t = n * ts;
            data[0][n] = t;

            if (t >= 0 && t < 0.1) {
                data[1][n] = Math.sin(6 * Math.PI * t) * Math.cos(5 * Math.PI * t);
            } else if (t >= 0.1 && t < 0.4) {
                data[1][n] = -1.1 * t * Math.cos(41 * Math.PI * Math.pow(t, 2));
            } else if (t >= 0.4 && t < 0.72) {
                data[1][n] = t * Math.sin(20 * Math.pow(t, 4));
            } else if (t >= 0.72 && t < 1) {
                data[1][n] = 3.3 * (t - 0.72) * Math.cos(27 * t + 1.3);
            }
        }
        return data;
    }

    private static void saveChartAsPNG(JFreeChart chart) {

        String filePath = "src/main/java/org/zut/chart/u.png";
        try {
            File file = new File(filePath);
            org.jfree.chart.ChartUtils.saveChartAsPNG(file, chart, 800, 600);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}