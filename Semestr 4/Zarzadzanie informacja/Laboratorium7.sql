# 1
SELECT * FROM customers;

SELECT postalCode, CONVERT(postalCode, DATE) AS daty
FROM customers
WHERE postalCode IS NOT NULL
ORDER BY daty DESC;

# 2
SELECT postalCode, CONVERT(postalCode, TIME) AS time
FROM customers
WHERE postalCode IS NOT NULL
ORDER BY time DESC;

# 3
SELECT * FROM products;

SELECT ABS(buyPrice - MSRP) AS wynik
FROM products
WHERE productCode = "S18_4027";

# 4
SELECT TRUNCATE(POW(buyPrice, 3), 2) AS wynik
FROM products
WHERE productCode = "S24_2972";

# 5
SELECT * FROM payments;

SELECT ROUND(SQRT(SUM(amount)), 4)
FROM payments
WHERE customerNumber = 131;

# 6
SELECT * FROM payments;

SELECT POW(COUNT(customerNumber), 1/3)
FROM payments
WHERE customerNumber = 124;

# 7
SELECT * FROM employees;
SELECT * FROM offices;

SELECT DISTINCT o.city
FROM offices o
WHERE EXISTS (
	SELECT firstName
    FROM employees e
    WHERE e.officeCode = o.officeCode
    AND e.jobTitle != "Sales Rep"
);

# 8
SELECT * FROM orderdetails;

SELECT p.productName
FROM products p
WHERE EXISTS (
	SELECT productCode
    FROM orderdetails od
    WHERE od.productCode = p.productCode
    AND quantityOrdered >= 90
);

# 9
SELECT COUNT(customerNumber)
FROM (
	SELECT customerNumber
    FROM customers
	WHERE MOD(customerNumber, 2) = 1
) AS a;

# 10
SELECT * FROM products;

SELECT ROUND(SUM(quantityInStock * (MSRP - buyPrice)), 0) AS SUM
FROM products;

# 10 a)
SELECT SUM(quantityInStock * (ROUND(MSRP, 0) - ROUND(buyPrice, 0))) AS SUM_ROUND
FROM products;

# 10 b)
SELECT SUM(quantityInStock * (CEIL(MSRP) - CEIL(buyPrice))) AS SUM_CEIL
FROM products;

# 10 c)
SELECT SUM(quantityInStock * (FLOOR(MSRP) - FLOOR(buyPrice))) AS SUM_FLOOR
FROM products;

# 10 razem
SELECT
ROUND(SUM(quantityInStock * (MSRP - buyPrice)), 0) AS SUM,
SUM(quantityInStock * (ROUND(MSRP, 0) - ROUND(buyPrice, 0))) AS SUM_ROUND,
SUM(quantityInStock * (CEIL(MSRP) - CEIL(buyPrice))) AS SUM_CEIL,
SUM(quantityInStock * (FLOOR(MSRP) - FLOOR(buyPrice))) AS SUM_FLOOR
FROM products;