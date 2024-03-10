CREATE DATABASE lab
	CHARACTER SET utf8 COLLATE utf8_general_ci;
    
CREATE TABLE customers (
	customerNumber INT(11) PRIMARY KEY,
    customername VARCHAR(50),
    customerLastName VARCHAR(50),
    phone VARCHAR(50),
    addressLine1 VARCHAR(50) NOT NULL,
    addressLIne2 VARCHAR(50),
    city VARCHAR(50) NOT NULL,
    state VARCHAR(50) NOT NULL,
    postalCode VARCHAR(15),
    country VARCHAR(50),
    creditLimit DECIMAL(10,2) NOT NULL
);

# DROP TABLE customers;

ALTER TABLE customers
MODIFY COLUMN postalCode VARCHAR(16);

# Zadania z Laboratorium1.pdf

CREATE TABLE payments (
	paymentId INT PRIMARY KEY,
    customerNumber INT NOT NULL,
    paymentDate DATE NOT NULL,
    amount DECIMAL(10,2) NOT NULL,
    FOREIGN KEY (customerNumber) REFERENCES customers(customerNumber)
);

CREATE TABLE products (
	productId INT PRIMARY KEY,
    productName VARCHAR(50) NOT NULL,
    productDescription VARCHAR(100) NOT NULL
);

CREATE TABLE orderDetails (
	orderDetailsId INT PRIMARY KEY,
    amount INT NOT NULL,
    price INT NOT NULL,
    productId INT NOT NULL,
    FOREIGN KEY (productId) REFERENCES products(productId)
);

CREATE TABLE orders (
	orderId INT PRIMARY KEY,
    orderDate DATE NOT NULL,
    customerNumber INT NOT NULL,
    additionalMessage VARCHAR(255),
    orderStatus VARCHAR(50) NOT NULL,
    orderDetailsId INT NOT NULL,
    FOREIGN KEY (customerNumber) REFERENCES customers(customerNumber),
    FOREIGN KEY (orderDetailsId) REFERENCES orderDetails(orderDetailsId)
);