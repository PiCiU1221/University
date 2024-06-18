# 1

SELECT CURDATE();

# a)

SELECT ADDDATE(CURDATE(), 120);

SELECT
	DAY(dzisiejsza_data),
    MONTHNAME(dzisiejsza_data),
    YEAR(dzisiejsza_data),
    DAYNAME(dzisiejsza_data)
FROM (
	SELECT ADDDATE(CURDATE(), 120) AS dzisiejsza_data
) as a;

# b)

SELECT DAYNAME(MAKEDATE(2024, 205));

# c)

SELECT DATE_SUB(CURDATE(), INTERVAL 15 MONTH);

# 2
# a)

SELECT DATE_FORMAT(orderDate, "%Y %M %d - %W")
FROM orders;

# b)

SELECT DATE_FORMAT(paymentDate, "%Y %M, %W")
FROM payments;

# 3

SELECT TIMEDIFF("23:31:10", "12:01:20");

# 4

SELECT * FROM orders;

SELECT
	orderNumber AS "Nr zamówienia",
    DATE_FORMAT(orderDate, "%W %Y.%M.%d"),
    status AS "Status zamówienia"
FROM orders
WHERE DAYNAME(orderDate) = "Friday"
ORDER BY MONTH(orderDate);

# 5

SELECT
	YEAR(orderDate) AS "rok",
    WEEK(orderDate) AS "numer_tygodnia",
    COUNT(*) AS "ilość zamówień"
FROM orders
WHERE WEEK(orderDate) BETWEEN 12 AND 15
GROUP BY rok, numer_tygodnia;

# 6

SELECT * FROM payments;

SELECT
	p.customerNumber,
    c.customerName AS klient,
    SUM(amount) AS kwota
FROM payments p
JOIN customers c ON c.customerNumber = p.customerNumber
WHERE QUARTER(paymentDate) = 4
GROUP BY customerNumber
ORDER BY kwota DESC;

# 7

SELECT * FROM orders;

SELECT
	orderNumber,
    orderDate AS Data_zamowienia,
    shippedDate AS "Data wysylki",
    DATEDIFF(shippedDate, orderDate) AS "Dni_do_Wysylki"
FROM orders
ORDER BY DATEDIFF(shippedDate, orderDate) DESC;