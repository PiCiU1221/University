package org.example.Pizzeria2.fabryka;

import org.example.Pizzeria2.składniki.*;

public class AmerykańskaFabrykaSkładnikówPizzy implements FabrykaSkładnikówPizzy {
    public Ciasto utwórzCiasto() {
        return new GrubeChrupkieCiasto();
    }

    public Sos utwórzSos() {
        return new SosPomidorowy();
    }

    public Ser utwórzSer() {
        return new SerMozzarellaSerParmezan();
    }

    public Warzywa[] utwórzWarzywa() {
        Warzywa warzywa[] = { new Czosnek(), new Cebula(), new Pieczarki(), new CzerwonaPapryka() };
        return warzywa;
    }

    public Pepperoni utwórzPepperoni() {
        return new PlastryPepperoni();
    }

    public Małże utwórzMałże() {
        return new MrożoneMałże();
    }
}