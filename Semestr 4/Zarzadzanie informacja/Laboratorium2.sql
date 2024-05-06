CREATE TABLE towary (
	Kod INT AUTO_INCREMENT PRIMARY KEY,
    nazwa VARCHAR(50) NOT NULL,
    ilosc INT NOT NULL,
    cena DECIMAL(10,2) NOT NULL
);

INSERT INTO towary (nazwa, ilosc, cena)
VALUES ('Monitor LCD 21"', 3, 300.50);

INSERT INTO towary (nazwa, ilosc, cena)
VALUES ('Monitor LCD 19"', 5, 250.00);

SELECT * FROM towary;

INSERT INTO towary (nazwa, ilosc, cena)
VALUES  ('Monitor LCD 29"', 15, 550.00),
		('Monitor LCD 19"', 30, 300.00),
        ('Monitor LCD 21"', 25, 250.00),
        ('klawiatura', 15, 67.45),
        ('plyta glowna', 20, 350.20),
        ('klawiatura', 35, 42.35),
        ('mysz bezprzewodowa', 23, 51.00),
        ('pamiec SSD', 50, 75.20);
        
ALTER TABLE towary
ADD producent VARCHAR(10),
ADD model VARCHAR(20);

ALTER TABLE towary
MODIFY producent VARCHAR(20);

UPDATE towary SET producent = 'Toshiba', model = 'NC125'
WHERE Kod = 1;

UPDATE towary SET producent = 'Linea'
WHERE Kod = 2;

UPDATE towary SET producent = 'Belinea', model = 'MBE1234'
WHERE Kod = 3;

UPDATE towary SET producent = 'Sharp'
WHERE Kod = 4;

UPDATE towary SET producent = 'Sharp'
WHERE Kod = 5;

UPDATE towary SET producent = 'producent', model = 'model'
WHERE Kod = 6;

UPDATE towary SET producent = 'Assus'
WHERE Kod = 7;

UPDATE towary SET producent = 'Logitech', model = 'BKE12'
WHERE Kod = 8;

UPDATE towary SET producent = 'AITECH'
WHERE Kod = 9;

UPDATE towary SET producent = 'BIGComp', model = 'OWE12'
WHERE Kod = 10;

UPDATE towary SET producent = 'Sony'
WHERE producent = 'producent';

UPDATE towary SET model = 'Nowy'
WHERE model IS NULL;

ALTER TABLE towary
DROP COLUMN model;

DELETE FROM towary
WHERE ilosc < 10 && nazwa = "klawiatura" && cena > 200 && cena <= 300;

TRUNCATE TABLE towary;

DROP TABLE towary;