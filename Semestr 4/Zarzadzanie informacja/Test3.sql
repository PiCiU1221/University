# 1
SELECT * FROM customers;

SELECT customerName
FROM customers
WHERE city = "Oslo";

# 2 
SELECT * FROM employees;
SELECT * FROM offices;

SELECT officeCode
FROM offices
WHERE city = "Paris";

SELECT firstName, lastName
FROM employees
WHERE officeCode = (
	SELECT officeCode
	FROM offices
	WHERE city = "Paris"
);

# 3
SELECT * FROM products;

SELECT productName
FROM products
WHERE MSRP > 200;

# 4
SELECT * FROM products;

SELECT productName
FROM products
WHERE productScale = "1:10"
AND productVendor = "Second Gear Diecast";

# 5
SELECT * FROM customers;

SELECT city
FROM customers
WHERE postalCode IS NULL
AND state IS NOT NULL;

# 6
SELECT * FROM payments;

SELECT amount
FROM payments
WHERE customerNumber = 321
OR customerNumber = 148;

SELECT DISTINCT customerNumber
FROM payments
WHERE amount > ALL (
	SELECT amount
	FROM payments
	WHERE customerNumber IN (321, 148)
);