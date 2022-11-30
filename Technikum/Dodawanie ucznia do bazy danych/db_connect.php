<?php
	//Piotr Pietrusewicz @2021
	//plik php sluzacy do polaczenia sie z baza danych

	$dbServername = "localhost";
	$dbUsername = "ppie2018_testowanie";
	$dbPassword = "testowanie1";
	$dbName = "ppie2018_testowanie";

	$conn = mysqli_connect($dbServername, $dbUsername, $dbPassword, $dbName);

	mysqli_set_charset($conn, "utf8");

	date_default_timezone_set("Europe/Warsaw");

	// Check connection
	/*if (!$conn) {
		die("Connection failed: " . mysqli_connect_error());
 	}
  		echo "Connected successfully";*/
?>