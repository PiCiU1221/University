# 5. Łaczenie tabel

SELECT * FROM productlines;
SELECT * FROM products;

# 1
SELECT p.productName, pl.textDescription
FROM products p, productlines pl
WHERE p.productLine = pl.productLine
AND p.productName = "1968 Ford Mustang";

# 2
SELECT p.productName, pl.textDescription
FROM products p
JOIN productlines pl ON p.productLine = pl.productLine
WHERE p.productName = "1968 Ford Mustang";

# 3
SELECT * FROM orders;
SELECT * FROM customers;
SELECT * FROM orderdetails;

SELECT o.orderNumber, c.customerName, SUM(od.priceEach * od.quantityOrdered), o.status
FROM orders o
JOIN customers c ON o.customerNumber = c.customerNumber
JOIN orderdetails od ON o.orderNumber = od.orderNumber
WHERE o.orderNumber = 10100;

# 4
SELECT * FROM customers;

SELECT c.customerName, SUM(od.priceEach * od.quantityOrdered) AS totalAmount
FROM orders o
JOIN customers c ON o.customerNumber = c.customerNumber
JOIN orderdetails od ON o.orderNumber = od.orderNumber
GROUP BY c.customerName
ORDER BY totalAmount DESC
LIMIT 1;

# 5
SELECT * FROM payments;

SELECT c.customerName, p.amount
FROM customers c
JOIN payments p ON c.customerNumber = p.customerNumber
GROUP BY c.customerNumber
HAVING COUNT(*) = 1;

# 6
SELECT * FROM employees;
SELECT * FROM customers;

SELECT firstName FROM employees
UNION ALL
SELECT contactFirstName AS firstName FROM customers;

# 7
SELECT firstName FROM employees
UNION
SELECT contactFirstName AS firstName FROM customers;

# 8
SELECT * FROM offices;
SELECT * FROM customers;

SELECT city FROM offices
UNION ALL
SELECT city FROM customers
ORDER BY city;

# 9
SELECT city, COUNT(city) FROM (
	SELECT city FROM offices
	UNION ALL
	SELECT city FROM customers
) AS subquery
GROUP BY city
ORDER BY COUNT(city) DESC;

# 10
SELECT * FROM employees;
SELECT * FROM offices;

SELECT e.firstName, e.lastName, o.country
FROM employees e
JOIN offices o ON e.officeCode = o.officeCode
ORDER BY country;

# 11
SELECT * FROM customers;
SELECT * FROM orders;

SELECT c.customerName, COUNT(orderNumber) AS liczba_zamowien
FROM customers c
JOIN orders o ON c.customerNumber = o.customerNumber
GROUP BY customerName
ORDER BY liczba_zamowien DESC
LIMIT 10;

# 12
SELECT * FROM employees;
SELECT * FROM customers;

SELECT e.firstName, e.lastName, e.jobTitle, c.customerName
FROM employees e
JOIN customers c ON e.employeeNumber = c.salesRepEmployeeNumber
ORDER BY customerName;

# 13
SELECT e.firstName, e.lastName, e.jobTitle, c.customerName
FROM employees e
RIGHT JOIN customers c ON e.employeeNumber = c.salesRepEmployeeNumber
ORDER BY customerName;

# 14
SELECT e.firstName, e.lastName, e.jobTitle, c.customerName
FROM employees e
LEFT JOIN customers c ON e.employeeNumber = c.salesRepEmployeeNumber
UNION
SELECT e.firstName, e.lastName, e.jobTitle, c.customerName
FROM employees e
RIGHT JOIN customers c ON e.employeeNumber = c.salesRepEmployeeNumber
ORDER BY customerName;

# 15
SELECT * FROM products;
SELECT * FROM orderdetails;

SELECT p.productCode, COALESCE(SUM(od.quantityOrdered), 0) AS totalOrdered
FROM products p
LEFT JOIN orderdetails od ON p.productCode = od.productCode
GROUP BY p.productCode;