package org.example.adapterKlasowy;

public interface CzujnikPogodowy {
	
	/** 
	 * Zwraca temperaturę.
	 * @return Temperatura w °C.
	 */
    public double pobierzTemperature();
    
    /** 
     * Ciśnienie
     * @return Ciśnienie w hPa.
     */
    public double pobierzCisnienie();
    
    /**
     * Wilgotność
     * @return Wilgotność w %.
     */
    public double pobierzWilgotnosc();
}
