# 1.a)

SELECT * FROM customers;

CREATE FUNCTION contactPerson(customerNumber INT)
RETURNS VARCHAR(100)
DETERMINISTIC
RETURN (
	SELECT CONCAT(contactFirstName, " ", contactLastName)
    FROM customers
    WHERE customers.customerNumber = customerNumber
);

# 1.b)

SELECT
	contactPerson(customerNumber),
    contactFirstName,
    contactLastName
FROM customers;

# 2

CREATE FUNCTION limitKredytowy(input FLOAT)
RETURNS VARCHAR(100)
DETERMINISTIC
RETURN (
	CASE
		WHEN input < 100000 THEN "maly"
        WHEN input BETWEEN 100000 AND 200000 THEN "sredni"
        ELSE "duzy"
	END
);

SELECT limitKredytowy(10000);   # maly
SELECT limitKredytowy(100000);  # sredni
SELECT limitKredytowy(1000000); # duzy

# 2.a)

CREATE FUNCTION limitKredytowy(input FLOAT)
RETURNS VARCHAR(100)
DETERMINISTIC
BEGIN
	CASE
		WHEN input < 100000 THEN RETURN "maly";
        WHEN input BETWEEN 100000 AND 200000 THEN RETURN "sredni";
        ELSE RETURN "duzy";
	END CASE;
END;