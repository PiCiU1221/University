<?php    
    $ID_max_check = mysqli_fetch_row(mysqli_query($conn,"SELECT MAX(ID_uczen) FROM uczen"));
	$max_ID = $ID_max_check[0];

    echo '<table>
                <tr>
                    <th>Imię</th>
                    <th>Nazwisko</th>
                    <th>Średnia</th>
                    <th>Klasa</th>
                </tr>';
					
	for ($x = $max_ID; $x >= 1; $x--) {
		$imie_s = mysqli_fetch_row(mysqli_query($conn,"SELECT imie FROM uczen WHERE ID_uczen='".$x."'"));
    	$imie = $imie_s[0];
        $nazwisko_s = mysqli_fetch_row(mysqli_query($conn,"SELECT nazwisko FROM uczen WHERE ID_uczen='".$x."'"));
    	$nazwisko = $nazwisko_s[0];
		$srednia_s = mysqli_fetch_row(mysqli_query($conn,"SELECT srednia_ocen FROM uczen WHERE ID_uczen='".$x."'"));
    	$srednia = $srednia_s[0];
		$klasa_s = mysqli_fetch_row(mysqli_query($conn,"SELECT klasa FROM uczen WHERE ID_uczen='".$x."'"));
    	$klasa = $klasa_s[0];

		echo '<tr>
                <td>'.$imie.'</td>
                <td>'.$nazwisko.'</td>
                <td>'.$srednia.'</td>
                <td>'.$klasa.'</td>
            </tr>';
	}
    echo '</table>';
?>