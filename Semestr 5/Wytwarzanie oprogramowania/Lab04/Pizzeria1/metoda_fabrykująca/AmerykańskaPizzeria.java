package org.example.Pizzeria1.metoda_fabrykująca;

import org.example.Pizzeria1.pizza.*;

public class AmerykańskaPizzeria extends Pizzeria {
    @Override
    Pizza utwórzPizza(String type) {
        Pizza pizza = null;
        if (type.equals("serowa")) {
            pizza = new AmerykańskaSerowaPizza();
        } else if (type.equals("pepperoni")) {
            pizza = new AmerykańskaPepperoniPizza();
        } else if (type.equals("owocemorza")) {
            pizza = new AmerykańskaOwoceMorzaPizza();
        } else if (type.equals("wegetariańska")) {
            pizza = new AmerykańskaWegatariańskaPizza();
        }

        return pizza;
    }
}
