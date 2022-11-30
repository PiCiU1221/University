<?php
    include('db_connect.php');
	include('insert.php');    
?>

<!DOCTYPE html>
<html>
    <head>
		<meta charset="UTF-8">
		<link rel="stylesheet" href="style.css">

		<title>PHP2</title>

		<meta name="author" content="Piotr Pietrusewicz"/>
		<meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no"/>
    </head>
    <body>
	    <h1>Dodawanie ucznia do bazy danych</h1>
		<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>" accept-charset="UTF-8">    
            <input id="imie" name="imie" type="text" placeholder="Imię" pattern=".{2,}" title="Wymagana długość imienia to 2 znaków" required>
            <input id="nazwisko" name="nazwisko" type="text" placeholder="Nazwisko" pattern=".{2,}" title="Wymagana długość nazwiska to 2 znaków" required>
			<input id="srednia" name="srednia" type="number" min="0" max="6" placeholder="Średnia" title="Średnia musi mieścić się w kryterium 0-6" required>
			
			<input id="klasa" name="klasa" list="klasy" required>
			<datalist id="klasy">
  				<option value="4TI">
  				<option value="4TLI">
  				<option value="3TI">
  				<option value="4H">
  				<option value="4TH">
			</datalist>

            <input type="submit" id="submit_post" name="submit" value="Dodaj do bazy">
        </form>
		
		<div class="footer">
			</br><p>@Piotr Pietrusewicz 2021</p></br>
		</div>

		<?php
    		include('display.php');   
		?>
    </body>
</html>