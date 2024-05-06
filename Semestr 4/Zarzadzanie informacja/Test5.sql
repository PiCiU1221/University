SELECT * FROM employees;
SELECT * FROM customers;
SELECT * FROM products;

# 1
SELECT firstName
FROM employees
UNION
SELECT contactFirstName
FROM customers
ORDER BY firstName;

# 2
SELECT * FROM products;
SELECT * FROM orderdetails;

SELECT p.productName, od.quantityOrdered
FROM products p
JOIN orderdetails od ON p.productCode = od.productCode
WHERE orderNumber = 10217;

# 3
SELECT c.customerName, e.firstName, e.lastName, o.city
FROM employees e
JOIN customers c ON e.employeeNumber = c.salesRepEmployeeNumber
JOIN offices o ON e.officeCode = o.officeCode
WHERE c.country = "Canada";

# 4
SELECT c.customerName, e.firstName, e.lastName
FROM customers c
LEFT JOIN employees e ON c.salesRepEmployeeNumber = e.employeeNumber
WHERE c.country = "Germany";

# 5
SELECT * FROM orders;

SELECT c.customerName, COUNT(o.customerNumber) as count
FROM customers c
LEFT JOIN orders o ON c.customerNumber = o.customerNumber
GROUP BY customerName
ORDER BY count;

# 6
SELECT e.firstName, e.lastName, COUNT(DISTINCT c.country) as liczbaKrajow
FROM employees e
JOIN customers c ON e.employeeNumber = c.salesRepEmployeeNumber
WHERE e.jobTitle = "Sales Rep"
GROUP BY lastName
ORDER BY liczbaKrajow DESC;