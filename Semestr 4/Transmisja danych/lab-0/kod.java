package org.zut;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.data.xy.DefaultXYDataset;

import javax.swing.*;
import java.io.File;
import java.io.IOException;

public class Lab0 {

    public static void plotFunction() {
        DefaultXYDataset dataset = new DefaultXYDataset();
        double[][] data = generateData();
        dataset.addSeries("Function", data);

        JFreeChart chart = ChartFactory.createXYLineChart(
                "Graph", // chart title
                "X", // x-axis label
                "Y", // y-axis label
                dataset
        );

        chart.removeLegend();

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
        int points = 201;
        double[][] data = new double[2][points];
        for (int i = 0; i < points; i++) {
            double x = -10 + i * 0.1;
            data[0][i] = x;
            data[1][i] = Math.sin(x);
        }
        return data;
    }

    private static void saveChartAsPNG(JFreeChart chart) {

        String filePath = "src/main/java/org/zut/chart/f.png";
        try {
            File file = new File(filePath);
            org.jfree.chart.ChartUtils.saveChartAsPNG(file, chart, 800, 600);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}