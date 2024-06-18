# 1

SELECT * FROM orderdetails;

SELECT od.productCode
FROM orderdetails od
WHERE quantityOrdered < 10;

SELECT p.productName
FROM products p
WHERE EXISTS (
	SELECT od.productCode
	FROM orderdetails od
	WHERE od.productCode = p.productCode
    AND quantityOrdered < 10
);

# 2

SELECT * FROM products;

SELECT POW(ROUND(MSRP), 1/2)
FROM products
WHERE productCode = "S18_4027";

# 3

SELECT * FROM payments;

SELECT SUM(CEIL(amount))
FROM payments;

# 4

SELECT * FROM employees;

SELECT email
FROM employees
WHERE MOD(employeeNumber, 2) = 1;

# 5

SELECT * FROM orders;
SELECT * FROM orderdetails;

SELECT orderNumber
FROM orders
WHERE customerNumber = 129;

SELECT SUM(quantityOrdered * priceEach)
FROM orderdetails
WHERE orderNumber IN (
	SELECT orderNumber
    FROM orders
    WHERE customerNumber = 129
);