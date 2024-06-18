# 1

SELECT * FROM orders;

SELECT
	YEAR(orderDate) AS rok,
    MONTHNAME(orderDate) AS miesiac,
    COUNT(*) AS liczba_zamowien,
    AVG(DATEDIFF(shippedDate, orderDate)) AS sredni_czas_realizacji 
FROM orders
GROUP BY rok, miesiac;

# 2

SELECT * FROM orders;
SELECT * FROM orderdetails;
SELECT * FROM products;

SELECT
	p.productName AS produkt,
    COUNT(od.productCode) AS liczba_zamowien,
    SUM(od.quantityOrdered) AS razem_ilosc
FROM products p
JOIN orderdetails od ON od.productCode = p.productCode
JOIN orders o ON o.orderNumber = od.orderNumber
WHERE (MONTH(o.orderDate) BETWEEN 11 AND 12) OR (MONTH(o.orderDate) BETWEEN 1 AND 2)
GROUP BY p.productName;

# 3

SELECT * FROM payments;

SELECT
	DATE_FORMAT(paymentDate, "%d %M %Y") AS data_platnosci,
    CASE
		WHEN DAYNAME(paymentDate) = "Monday" THEN "pon."
        WHEN DAYNAME(paymentDate) = "Tuesday" THEN "wt."
        WHEN DAYNAME(paymentDate) = "Wednesday" THEN "sro."
        WHEN DAYNAME(paymentDate) = "Thursday" THEN "czw."
        WHEN DAYNAME(paymentDate) = "Friday" THEN "pt."
    END AS dzien_roboczy
FROM payments;

# 4

SELECT * FROM products;

SELECT
	SUBSTR(productName, 6, LENGTH(productName) - 5) AS Model,
    LEFT(productName, 4) AS Rok_P,
    2005 - CONVERT(LEFT(productName, 4), UNSIGNED) AS Roznica
FROM products
WHERE productLine = "Motorcycles"
ORDER BY Roznica DESC;

SELECT
	Model,
    Rok_P,
    2005 - CONVERT(Rok_P, UNSIGNED) AS Roznica
FROM (
	SELECT
		SUBSTR(productName, 6, LENGTH(productName) - 5) AS Model,
		LEFT(productName, 4) AS Rok_P
	FROM products
	WHERE productLine = "Motorcycles"
) AS a
ORDER BY Roznica DESC;