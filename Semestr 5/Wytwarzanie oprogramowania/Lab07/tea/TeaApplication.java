package edu.zut.tea;

public class TeaApplication {

	public static void main(String[] args) {
		ReadingRecord aReading = acquireReading();
		aReading.calculateCharges();

		System.out.println(String.format("firstMethod=%.2f", firstMethod(aReading)));
		System.out.println(String.format("secondMethod=%.2f", secondMethod(aReading)));
		System.out.println(String.format("thirdMethod=%.2f", thirdMethod(aReading)));
	}

	public static double firstMethod(ReadingRecord aReading) {
		return aReading.getBaseCharge();
	}

	public static double secondMethod(ReadingRecord aReading) {
		return aReading.getTaxableCharge();
	}
	
	public static double thirdMethod(ReadingRecord aReading) {
		return aReading.getBaseCharge();
	}

	public static ReadingRecord acquireReading() {
		ReadingRecord reading = new ReadingRecord();
		reading.customer = "ivan";
		reading.quantity = 10;
		reading.month = 2;
		reading.year = 2019;
		return reading;
	}
}
