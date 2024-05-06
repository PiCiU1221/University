# 1
SELECT * FROM orderdetails;

SELECT od.orderNumber, SUM(od.quantityOrdered) AS suma_modeli
FROM orderdetails od
GROUP BY orderNumber;

SELECT orderNumber, suma_modeli
FROM (
	SELECT od.orderNumber, SUM(od.quantityOrdered) AS suma_modeli
	FROM orderdetails od
	GROUP BY orderNumber
) AS a
WHERE suma_modeli >= 600
ORDER BY suma_modeli DESC;

# 2
SELECT * FROM customers;
SELECT * FROM orders;

SELECT c.customerName, COUNT(o.orderNumber)
FROM customers c
LEFT JOIN orders o ON o.customerNumber = c.customerNumber
GROUP BY customerName;

SELECT customerName
FROM (
	SELECT c.customerName, COUNT(o.orderNumber) AS liczba_zamowien
	FROM customers c
	LEFT JOIN orders o ON o.customerNumber = c.customerNumber
	GROUP BY customerName
) AS a
WHERE liczba_zamowien = 0
AND (
	SELECT cus.salesRepEmployeeNumber
    FROM customers cus
    WHERE cus.customerName = a.customerName
);

# 3
SELECT * FROM orderdetails;
SELECT * FROM products;

SELECT p.productVendor, ROUND(SUM(od.quantityOrdered) / COUNT(DISTINCT od.orderNumber), 2) AS SZT_ZAM
FROM products p
JOIN orderdetails od ON od.productCode = p.productCode
GROUP BY productVendor
ORDER BY SZT_ZAM DESC;

# 4
SELECT * FROM payments;

SELECT e.firstName, e.lastName
FROM employees e;

SELECT customerNumber, AVG(amount)
FROM payments
GROUP BY customerNumber;

SELECT customerNumber
FROM (
	SELECT customerNumber, AVG(amount) AS srednia
	FROM payments
	GROUP BY customerNumber
) AS a
WHERE srednia > 50000;

SELECT DISTINCT e.lastName, e.firstName
FROM employees e
JOIN customers c ON c.salesRepEmployeeNumber = e.employeeNumber
WHERE (
	SELECT customerNumber
	FROM (
		SELECT customerNumber, AVG(amount) AS srednia
		FROM payments
		GROUP BY customerNumber
	) AS a
	WHERE srednia > 50000
    AND customerNumber = c.customerNumber
)
ORDER BY lastName;