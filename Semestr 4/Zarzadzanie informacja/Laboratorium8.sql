# 1

SELECT productCode, productName, LENGTH(productName) AS dlugosc_nazwy
FROM products
ORDER BY LENGTH(productName) DESC
LIMIT 25;

# 2

SELECT * FROM productlines;

SELECT productLine, REPLACE(productLine, "a", "<A>")
FROM productlines;

# 3

SELECT * FROM products;

SELECT productName, productScale, productVendor
FROM products
WHERE productDescription LIKE "%wood%";

# 4

SELECT * FROM employees;

SELECT jobTitle,
firstName AS Imie,
lastName AS Nazwisko,
CONCAT(LEFT(firstName, 1), RIGHT(firstName, 1), ".", lastName, "@motorshop.biz") AS Nowy_Email
FROM employees;

# 5

SELECT * FROM products;

SELECT productName,
LEFT(productName, 4) AS rok,
SUBSTRING(productName, 5, LENGTH(productName)) AS model
FROM products
WHERE productLine = "Motorcycles"
ORDER BY rok;

# 6

SELECT * FROM customers;

SELECT customerName, country, city,
IF (state IS NULL, "brak danych", state) AS stan
FROM customers
ORDER BY country, stan;

# 7

SELECT * FROM employees;
SELECT * FROM offices;

SELECT e.officeCode AS "Kod biura",
	o.city AS "Miasto",
	e.firstName AS "Imię sprzedawcy",
	e.lastName AS "Nazwisko sprzedawcy",
	o.country AS "Kraj",
	CASE WHEN o.territory = "NA" THEN "Ameryka Północna"
		WHEN o.territory = "EMEA" THEN "Europa"
		ELSE "reszta świata"
		END AS Kod_terytorium
FROM employees e
JOIN offices o ON e.officeCode = o.officeCode
ORDER BY Kod_terytorium;