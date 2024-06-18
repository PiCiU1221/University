# 1

SELECT * FROM orders;

SELECT 
	YEAR(orderDate) AS rok,
    MONTHNAME(orderDate) AS miesiac,
    COUNT(orderNumber) AS liczba_zamowien,
    AVG(DATEDIFF(shippedDate, orderDate)) AS sredni_czas_realizacji
FROM
	orders
WHERE
	status = "Shipped"
GROUP BY
	rok, miesiac
ORDER BY
	YEAR(orderDate),
    MONTH(orderDate);

# 2

SELECT * FROM orderdetails;

SELECT
	p.productName AS product,
    COUNT(od.productCode) AS liczba_zamowien,
    SUM(od.quantityOrdered) AS razem_ilosc
FROM
	orderdetails od
JOIN products p ON
	p.productCode = od.productCode
JOIN orders o ON
	o.orderNumber = od.orderNumber
WHERE
	(MONTH(o.orderDate) BETWEEN 11 AND 12) OR
    (MONTH(o.orderDate) BETWEEN 1 AND 2)
GROUP BY
	product;

# 3

SELECT * FROM products;
SELECT * FROM orderdetails;

SELECT
	p.productLine AS nazwa_kategorii,
    AVG(od.priceEach * od.quantityOrdered) AS srednia_cena_sprzedazy,
    COUNT(od.productCode) AS liczba_transakcji
FROM
	orderdetails od
JOIN products p ON
	p.productCode = od.productCode
GROUP BY
	p.productLine
ORDER BY
	srednia_cena_sprzedazy DESC;

# 4

SELECT * FROM products;

SELECT
	SUBSTR(productName, 6, LENGTH(productName) - 5) AS Model,
    LEFT(productName, 4) AS Rok_P,
    2005 - LEFT(productName, 4) AS Roznica
FROM
	products
WHERE
	productLine = "Motorcycles"
ORDER BY
	Roznica DESC;

# 5

SELECT * FROM employees;
SELECT * FROM offices;

SELECT
	o.officeCode AS kod_oddzialu,
    o.country AS kraj,
    COUNT(e.officeCode) AS liczba_zatrudnionych
FROM
	offices o
JOIN employees e ON
	e.officeCode = o.officeCode
GROUP BY
	kod_oddzialu;

# 6

SELECT * FROM products;
SELECT * FROM orderdetails;

SELECT
	p.productName AS nazwa_modelu,
    MAX(od.priceEach - p.buyPrice) AS max_marza
FROM
	products p
JOIN orderdetails od ON
	p.productCode = od.productCode
GROUP BY
	nazwa_modelu
ORDER BY
	max_marza;