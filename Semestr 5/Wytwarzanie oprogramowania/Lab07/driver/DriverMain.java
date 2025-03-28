package edu.zut.driver;

public class DriverMain {

	public static void main(String[] args) {
		Driver driver = new Driver("jan kowalski", 6);

		String driverName = driver.getName();
		int rating = (driver.getLateDeliveries() > 5) ? 2 : 1;
		System.out.println(String.format("driver: %s, rating %d", driverName, rating));
	}
}
