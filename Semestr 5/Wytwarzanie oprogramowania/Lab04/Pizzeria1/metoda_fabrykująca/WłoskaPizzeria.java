package org.example.Pizzeria1.metoda_fabrykująca;

import org.example.Pizzeria1.pizza.*;

public class WłoskaPizzeria extends Pizzeria {
    @Override
    Pizza utwórzPizza(String type) {
        Pizza pizza = null;
        if (type.equals("serowa")) {
            pizza = new WłoskaSerowaPizza();
        } else if (type.equals("pepperoni")) {
            pizza = new WłoskaPepperoniPizza();
        } else if (type.equals("owocemorza")) {
            pizza = new WłoskaOwoceMorzaPizza();
        } else if (type.equals("wegetariańska")) {
            pizza = new WłoskaWegetariańskaPizza();
        }

        return pizza;
    }
}
