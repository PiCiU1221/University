# 1
SELECT productLine, textDescription
FROM productlines;

# 2
SELECT * FROM customers;

SELECT country
FROM customers;

# 3
SELECT DISTINCT country
FROM customers;

# 4
SELECT * FROM products;

SELECT *
FROM products
WHERE quantityInStock > 9000;

# 5
SELECT * FROM orders;
SELECT DISTINCT status
FROM orders;

SELECT status, comments, customerNumber
FROM orders
WHERE status = "Cancelled"
OR status = "On Hold"
OR status = "Resolved";

#6
SELECT * FROM orderdetails;

SELECT productCode, quantityOrdered, priceEach
FROM orderdetails
WHERE (quantityOrdered > 80 AND priceEach <= 200)
OR (quantityOrdered <= 80 AND priceEach > 200);

#7
SELECT * FROM orders;

SELECT *
FROM orders
WHERE status != "Shipped";

#8
SELECT *
FROM orders
WHERE comments IS NOT NULL;

#9
SELECT * FROM products;

SELECT productName,
ROUND(buyPrice * quantityInStock, 2) AS Wartosc
FROM products;

#10
SELECT * FROM customers;

SELECT DISTINCT country
FROM customers
WHERE city = "Oulu"
OR city = "Herzlia"
OR city = "Hatfield"
OR city = "Cowes";

SELECT customerName, city, country
FROM customers
WHERE country IN (
	SELECT DISTINCT country
	FROM customers
	WHERE city = "Oulu"
	OR city = "Herzlia"
	OR city = "Hatfield"
	OR city = "Cowes"
);

# 11
SELECT MAX(creditLimit)
FROM customers
WHERE country = "UK";

SELECT customerName, country
FROM customers
WHERE creditLimit > ALL (
	SELECT creditLimit
	FROM customers
	WHERE country = "UK"
);