package edu.zut.tea;

public class ReadingRecord {
	String customer;
	int quantity;
	int month;
	int year;

	private double baseCharge;
	private double taxableCharge;

	public double getCalculatedBaseCharge() {
		return getBaseRate() * quantity;
	}

	public double getTaxThreshold() {
		return 100;
	}

	public double getBaseRate() {
		return 12.5;
	}

	public double getBaseCharge() {
		return baseCharge;
	}

	public double getTaxableCharge() {
		return taxableCharge;
	}

	public void calculateCharges() {
		this.baseCharge = getBaseRate() * quantity;
		this.taxableCharge = Math.max(0, baseCharge - getTaxThreshold());
	}
}
