# TEST 4

# 1
SELECT *
FROM employees
ORDER BY officeCode DESC;

# 2
SELECT officeCode, COUNT(*)
FROM employees
GROUP BY officeCode
ORDER BY COUNT(*) DESC;

# 3
SELECT COUNT(*)
FROM customers
WHERE country = "USA";

# 4
SELECT ROUND(AVG(buyPrice), 2)
FROM products
WHERE productLine = "Classic Cars";

# 5
SELECT COUNT(*)
FROM products
WHERE MSRP < 100;

# 6
SELECT orderNumber, SUM(quantityOrdered)
FROM orderdetails
GROUP BY orderNumber
HAVING SUM(quantityOrdered) >= 500
ORDER BY SUM(quantityOrdered) DESC;