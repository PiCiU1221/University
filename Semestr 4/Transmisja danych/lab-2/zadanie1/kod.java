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
}