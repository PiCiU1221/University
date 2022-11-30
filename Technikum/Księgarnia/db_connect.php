<?php
	//Piotr Pietrusewicz @2021
	//plik php sluzacy do polaczenia sie z baza danych
	session_start();

	$dbServername = "localhost";
	$dbUsername = "ppie2018_ksiegarnia";
	$dbPassword = "zGR6FFaIG";
	$dbName = "ppie2018_ksiegarnia";

	$conn = mysqli_connect($dbServername, $dbUsername, $dbPassword, $dbName);

	mysqli_set_charset($conn, "utf8");

	date_default_timezone_set("Europe/Warsaw");

	// Check connection
	/*if (!$conn) {
		die("Connection failed: " . mysqli_connect_error());
 	}
  		echo "Connected successfully";*/
?>