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