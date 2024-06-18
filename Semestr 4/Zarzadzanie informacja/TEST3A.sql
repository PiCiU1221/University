# TEST 3A

# 1.

SELECT * FROM orders;

SELECT
	ROUND(AVG(DATEDIFF(shippedDate, orderDate)), 2)
FROM
	orders;
    
    
# 2.

SELECT * FROM customers;

SELECT
	customerName
FROM
	customers
WHERE
	customerName LIKE "%tr%";
    
    
# 3.
# DO POPRAWKI CHYBA

SELECT * FROM customers;
SELECT * FROM employees;

SELECT
    lastName AS nazwisko
FROM
	employees
UNION
SELECT
    contactLastName AS nazwisko
FROM
	customers;
    
SELECT
	nazwisko
FROM (
	SELECT
		lastName AS nazwisko
	FROM
		employees
	UNION
	SELECT
		contactLastName AS nazwisko
	FROM
		customers
) AS podzapytanie
ORDER BY
	LENGTH(nazwisko)
LIMIT 3;


# 4.

SELECT * FROM orders;

SELECT
	DAYNAME(orderDate) AS nazwa_dnia,
    COUNT(orderNumber) AS liczba_zamowien
FROM
	orders
GROUP BY
	DAYNAME(orderDate)
ORDER BY
	COUNT(orderNumber) DESC
LIMIT 1;


# 5

SELECT * FROM orders;

SELECT
	o.orderNumber,
    o.status,
    c.customerName AS klient
FROM
	orders o
JOIN
	customers c ON c.customerNumber = o.customerNumber;
    
    
# 6
    
SELECT
	e.lastName,
	e.firstName
FROM
	employees e
JOIN
	offices o ON o.officeCode = e.officeCode
WHERE
	o.country = "USA";
    
    
# 7

SELECT * FROM payments;

SELECT
	checkNumber,
    paymentDate,
    DATEDIFF("2024-06-12", paymentDate) AS ilosc_dni_ktore_uplynely
FROM
	payments
WHERE
	customerNumber = 124;
    
    
# 8
# NIE ZROBIONE

SELECT * FROM products;
SELECT * FROM orderdetails;

SELECT
	productCode,
    SUM(quantityOrdered) AS sprzedaz,
    COUNT(productCode) AS liczba_transakcji
FROM
	orderdetails
GROUP BY
	productCode;

SELECT
	productCode
FROM (
	SELECT
		productCode,
		SUM(quantityOrdered) AS sprzedaz,
		COUNT(productCode) AS liczba_transakcji
	FROM
		orderdetails
	GROUP BY
		productCode
) AS podzapytanie
WHERE
	sprzedaz > 2500
    AND liczba_transakcji > 40;


# 9
# DO ZROBIENIA

SELECT * FROM offices;
SELECT * FROM customers;
SELECT * FROM payments;

SELECT
	SUM(p.amount) AS pierwszy_kwartal
FROM
	payments p
JOIN
	customers c ON c.customerNumber = p.customerNumber
JOIN
	employees e ON e.employeeNumber = c.salesRepEmployeeNumber
JOIN
	offices o ON o.officeCode = e.officeCode
WHERE
	QUARTER(p.paymentDate) = 1 AND o.city = "NYC";
    
SELECT
	SUM(p.amount) AS drugi_kwartal
FROM
	payments p
JOIN
	customers c ON c.customerNumber = p.customerNumber
JOIN
	employees e ON e.employeeNumber = c.salesRepEmployeeNumber
JOIN
	offices o ON o.officeCode = e.officeCode
WHERE
	QUARTER(p.paymentDate) = 2 AND o.city = "NYC" AND YEAR(p.paymentDate) = 2003;
    
SELECT
	pierwszy_kwartal
FROM (
	SELECT
		SUM(p.amount) AS pierwszy_kwartal
	FROM
		payments p
	JOIN
		customers c ON c.customerNumber = p.customerNumber
	JOIN
		employees e ON e.employeeNumber = c.salesRepEmployeeNumber
	JOIN
		offices o ON o.officeCode = e.officeCode
	WHERE
		QUARTER(p.paymentDate) = 1 AND o.city = "NYC"
) AS a;

SELECT
	(SELECT SUM(p.amount) AS pierwszy_kwartal
	FROM payments p
	JOIN customers c ON c.customerNumber = p.customerNumber
	JOIN employees e ON e.employeeNumber = c.salesRepEmployeeNumber
	JOIN offices o ON o.officeCode = e.officeCode
	WHERE QUARTER(p.paymentDate) = 1 AND o.city = "NYC") AS pierwszy_kwartal,
	(SELECT SUM(p.amount) AS drugi_kwartal
	FROM payments p
	JOIN customers c ON c.customerNumber = p.customerNumber
	JOIN employees e ON e.employeeNumber = c.salesRepEmployeeNumber
	JOIN offices o ON o.officeCode = e.officeCode
	WHERE QUARTER(p.paymentDate) = 2 AND o.city = "NYC") AS drugi_kwartal,
    (SELECT SUM(p.amount) AS pierwszy_kwartal
	FROM payments p
	JOIN customers c ON c.customerNumber = p.customerNumber
	JOIN employees e ON e.employeeNumber = c.salesRepEmployeeNumber
	JOIN offices o ON o.officeCode = e.officeCode
	WHERE QUARTER(p.paymentDate) = 3 AND o.city = "NYC") AS trzeci_kwartal,
    (SELECT SUM(p.amount) AS pierwszy_kwartal
	FROM payments p
	JOIN customers c ON c.customerNumber = p.customerNumber
	JOIN employees e ON e.employeeNumber = c.salesRepEmployeeNumber
	JOIN offices o ON o.officeCode = e.officeCode
	WHERE QUARTER(p.paymentDate) = 4 AND o.city = "NYC") AS czwarty_kwartal;
    
# 10

SELECT * FROM employees;
SELECT * FROM customers;
SELECT * FROM offices;

SELECT
	o.officeCode,
    o.city,
    COUNT(c.salesRepEmployeeNumber) AS liczba_klientow
FROM
	customers c
JOIN
	employees e ON e.employeeNumber = c.salesRepEmployeeNumber
JOIN
	offices o ON o.officeCode = e.officeCode
GROUP BY
	o.officeCode;