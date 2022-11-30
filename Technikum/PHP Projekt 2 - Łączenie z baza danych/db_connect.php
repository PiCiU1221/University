<?php
	session_start();

	$dbServername = "localhost";
	$dbUsername = "ppie2018_testowanie";
	$dbPassword = "Br0gfaOoyt";
	$dbName = "ppie2018_testowanie";

	$conn = mysqli_connect($dbServername, $dbUsername, $dbPassword, $dbName);

	// Check connection
	/* if (!$conn) {
		die("Connection failed: " . mysqli_connect_error());
 	}
  		echo "Connected successfully"; */
?>