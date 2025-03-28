package org.example.Pizzeria2;

import org.example.Pizzeria2.fabryka.AmerykańskaFabrykaSkładnikówPizzy;
import org.example.Pizzeria2.fabryka.FabrykaSkładnikówPizzy;
import org.example.Pizzeria2.pizza.*;

public class AmerykańskaPizzeria extends Pizzeria {
    protected Pizza utwórzPizza(String item) {
        Pizza pizza = null;
        FabrykaSkładnikówPizzy fabrykaSkładników = new AmerykańskaFabrykaSkładnikówPizzy();
        if (item.equals("serowa")) {
            pizza = new SerowaPizza(fabrykaSkładników);
            pizza.ustawNazwa("Amerykańska Pizza Serowa");
        } else if (item.equals("wegetariańska")) {
            pizza = new WegetariańskaPizza(fabrykaSkładników);
            pizza.ustawNazwa("Amerykańska Pizza Wegetariańska");
        } else if (item.equals("owoce morza")) {
            pizza = new OwoceMorzaPizza(fabrykaSkładników);
            pizza.ustawNazwa("Amerykańska Pizza Owoce Morza");
        } else if (item.equals("pepperoni")) {
            pizza = new PepperoniPizza(fabrykaSkładników);
            pizza.ustawNazwa("Amerykańska Pizza Pepperoni");
        }
        return pizza;
    }
}