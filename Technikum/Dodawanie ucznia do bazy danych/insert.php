<?php
    if (isset($_POST['submit'])) {
	    $imie = $_POST['imie'];
        $nazwisko = $_POST['nazwisko'];
        $srednia = $_POST['srednia'];
	    $klasa = $_POST['klasa'];

        $sql = "INSERT INTO uczen (imie, nazwisko, srednia_ocen, klasa) VALUES ('".$imie."','".$nazwisko."','".$srednia."','".$klasa."')";

        if(mysqli_query($conn, $sql)){
            header('location: index.php');
        } else {
            echo "BŁAD: $sql. " . mysqli_error($link);
        }
    }
?>