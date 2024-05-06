# 1
SELECT * FROM employees;

SELECT email
FROM employees
ORDER BY email;

# 2
SELECT * FROM products;

SELECT productName, MSRP
FROM products
ORDER BY MSRP DESC;

# 3
SELECT MIN(buyPrice)
FROM products;

# 4
SELECT MAX(MSRP)
FROM products;

# 5
SELECT * FROM payments;

SELECT SUM(amount)
FROM payments;

# 6
SELECT * FROM orders;
SELECT * FROM orderdetails;

SELECT SUM(priceEach * quantityOrdered)
FROM orderdetails;

# 7
SELECT * FROM products;

SELECT SUM(MSRP)
FROM products
WHERE productLine = "Classic Cars";

# 8
SELECT COUNT(*)
FROM products
WHERE MSRP > 50;

# 9 
SELECT * FROM customers;

SELECT COUNT(*)
FROM customers
WHERE country IN("USA", "UK", "Australia");

# 10
SELECT COUNT(DISTINCT country)
FROM customers;

# 11
SELECT country, COUNT(*)
FROM customers
GROUP BY country;

# 12
SELECT * FROM products;

SELECT productLine, COUNT(*)
FROM products
WHERE buyPrice < 30
GROUP BY productLine;

# 13
SELECT * FROM payments;

SELECT customerNumber, SUM(amount) AS amount_sum
FROM payments
GROUP BY customerNumber
ORDER BY amount_sum DESC;

# 14
SELECT * FROM products;

SELECT productLine
FROM products
GROUP BY productLine
HAVING SUM(MSRP) > 1000;

# 15
SELECT productScale, quantityInStock
FROM products
GROUP BY productScale
HAVING COUNT(*) >= 10
ORDER BY quantityInStock ASC;

# 16
SELECT * FROM offices;

SELECT DISTINCT country
FROM offices;

SELECT * FROM customers;

SELECT COUNT(*)
FROM customers
WHERE country IN(
	SELECT DISTINCT country
	FROM offices
);

# 17
SELECT country, COUNT(*)
FROM customers
WHERE country IN(
	SELECT DISTINCT country
	FROM offices
)
GROUP BY country;