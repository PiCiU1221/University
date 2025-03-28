package org.example.Pizzeria2.fabryka;

import org.example.Pizzeria2.składniki.*;

public interface FabrykaSkładnikówPizzy {
	public Ciasto utwórzCiasto();

	public Sos utwórzSos();

	public Ser utwórzSer();

	public Warzywa[] utwórzWarzywa();

	public Pepperoni utwórzPepperoni();

	public Małże utwórzMałże();
}