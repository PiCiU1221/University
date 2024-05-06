# LAB 6

# 1
SELECT * FROM employees;
SELECT * FROM offices;

SELECT e.firstName,	e.lastName, e.email, (
	SELECT o.city
    FROM offices o
    WHERE o.officeCode = e.officeCode
    ) AS city
FROM 
	employees e;
    
# 2
SELECT * FROM offices;

SELECT e.firstName, e.lastName, e.email
FROM employees e
WHERE (
	SELECT city
    FROM offices o
    WHERE o.officeCode = e.officeCode
    ) = "Sydney";
    
# 3
SELECT c.customerName, (
	SELECT e.email
    FROM employees e
    WHERE e.employeeNumber = c.salesRepEmployeeNumber) as salesRepEmail
FROM customers c;

# 4
SELECT * FROM products;

SELECT p.productName,
	(SELECT p.MSRP - p.buyPrice) as roznica
FROM products p
WHERE roznica > 50
ORDER BY roznica;

# a)
SELECT productName, roznica
FROM (
	SELECT p.productName, (
		SELECT p.MSRP - p.buyPrice) as roznica
	FROM products p
    ) as a
WHERE roznica > 50
ORDER BY roznica;

# 5
SELECT * FROM employees;
SELECT * FROM payments;

SELECT c.customerName, (
	SELECT SUM(amount)
    FROM payments p
    WHERE p.customerNumber = c.customerNumber
    ) as suma
FROM customers c;

# a)
SELECT customerName, suma
FROM (
	SELECT c.customerName, (
		SELECT SUM(amount)
		FROM payments p
		WHERE p.customerNumber = c.customerNumber
		) as suma
	FROM customers c
) as a
WHERE suma > 100000
ORDER BY suma;