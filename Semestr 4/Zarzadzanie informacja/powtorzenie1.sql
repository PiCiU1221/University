# 1

SELECT * FROM customers;

SELECT * FROM orders;

SELECT
    c.customerName,
    c.addressLine1,
    c.addressLine2,
    c.postalCode,
    c.country
FROM customers c
JOIN orders o ON o.customerNumber = c.customerNumber
WHERE o.orderNumber = 10100;

# 2

SELECT * FROM payments;

SELECT
	c.customerName,
    SUM(p.amount) AS wielkosci_wplat
FROM payments p
JOIN customers c ON c.customerNumber = p.customerNumber
GROUP BY p.customerNumber
ORDER BY wielkosci_wplat DESC
LIMIT 10;

# 3

SELECT
	c.customerName,
    COUNT(o.orderNumber) AS ilosc_zamowien
FROM orders o
JOIN customers c ON c.customerNumber = o.customerNumber
GROUP BY o.customerNumber
ORDER BY ilosc_zamowien DESC
LIMIT 5;

SELECT
	customerName,
    ilosc_zamowien
FROM (
	SELECT
		c.customerName,
		COUNT(o.orderNumber) AS ilosc_zamowien
	FROM orders o
	JOIN customers c ON c.customerNumber = o.customerNumber
	GROUP BY o.customerNumber
	ORDER BY ilosc_zamowien DESC
	LIMIT 5
) AS podzapytanie
ORDER BY customerName;

# 4

SELECT * FROM payments;
SELECT * FROM orders;

SELECT
	customerName,
    paymentDate,
    amount
FROM (
	SELECT
		COUNT(c.customerName) AS count,
		c.customerName,
		p.paymentDate,
		p.amount
	FROM customers c
	JOIN payments p ON p.customerNumber = c.customerNumber
	GROUP BY customerName
) AS podzapytanie
WHERE count = 1;

# 5

SELECT * FROM employees;
SELECT * FROM customers;

SELECT
	firstName AS imie,
    lastName AS nazwisko
FROM employees
UNION
SELECT
	contactFirstName AS imie,
    contactLastName AS nazwisko
FROM customers;

# 6

SELECT * FROM offices;

SELECT * FROM employees;

SELECT
	e.firstName,
    e.lastName,
    e.jobTitle,
    o.country
FROM employees e
JOIN offices o ON e.officeCode = o.officeCode
ORDER BY country;

# 7

SELECT * FROM products;
SELECT * FROM orderdetails;

SELECT
	p.productName,
    SUM(od.quantityOrdered) AS ilosc_sprzedanych_egzemplarzy
FROM orderdetails od
JOIN products p ON p.productCode = od.productCode
GROUP BY p.productCode;

# 8

SELECT * FROM offices;
SELECT * FROM customers;

SELECT
	city,
    COUNT(city) AS liczba_wystapien
FROM offices
GROUP BY city
UNION
SELECT
	city,
    COUNT(city) AS liczba_wystapien
FROM customers
GROUP BY city;

SELECT
	city,
    liczba_wystapien
FROM (
	SELECT
		city,
		COUNT(city) AS liczba_wystapien
	FROM offices
	GROUP BY city
	UNION
	SELECT
		city,
		COUNT(city) AS liczba_wystapien
	FROM customers
	GROUP BY city
) AS podzapytanie
ORDER BY liczba_wystapien DESC;

# 9

# a)
SELECT
	c.customerName,
    e.firstName,
    e.lastName,
    e.jobTitle
FROM employees e
RIGHT JOIN customers c ON c.salesRepEmployeeNumber = e.employeeNumber;

# b)

SELECT
	c.customerName,
    e.firstName,
    e.lastName,
    e.jobTitle
FROM employees e
LEFT JOIN customers c ON c.salesRepEmployeeNumber = e.employeeNumber;