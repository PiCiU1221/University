# 1

SELECT * FROM products;

SELECT
	LEFT(productName, 4) AS "Data",
    SUBSTR(productName, 6, LENGTH(productName) - 5) AS "Nazwa modelu"
FROM products
WHERE productLine LIKE "%car%";

# 2

SELECT
	SUBSTR(productName, 6, LENGTH(productName) - 5) AS nazwa_produktu,
	ROUND(buyPrice * quantityInStock, 2) AS cena1
FROM products;

SELECT
	nazwa_produktu,
	IF (cena1 >= 1000, CONCAT(LEFT(cena1, LENGTH(cena1) - 5), " ", RIGHT(cena1, 6)), cena1) AS wartosc_stanu_magazynowego
FROM (
	SELECT
		SUBSTR(productName, 6, LENGTH(productName) - 5) AS nazwa_produktu,
		ROUND(buyPrice * quantityInStock, 2) AS cena1
	FROM products
) AS a
ORDER BY cena1 DESC;

# 3

SELECT
	productName,
    buyPrice,
	CASE
		WHEN productLine = "Classic Cars" THEN ROUND(buyPrice * 1.1, 2)
        WHEN productLine = "Vintage Cars" THEN ROUND(buyPrice * 1.15, 2)
        ELSE ROUND(buyPrice * 1.07, 2)
	END AS obliczona_cena_sprzedazy
FROM products
ORDER BY obliczona_cena_sprzedazy DESC;