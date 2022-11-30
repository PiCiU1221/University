<?php
	//Piotr Pietrusewicz @2021
	//plik index.php forum

	//uzywamy kodu z pliku db_connect.php by polaczyc sie z baza danych
	include('db_connect.php');

	//sprawdzamy czy uzytkownik ma uprawnienia administratora
	$isAdminCheck_s = mysqli_fetch_row(mysqli_query($conn,"SELECT isAdmin FROM Users WHERE Username='".$_SESSION['username']."'"));
	$isAdminCheck = $isAdminCheck_s[0];
	
	//kiedy wynik kwerendy jest rowny "1" to zalogowano sie na administratora
	if($isAdminCheck == 1){
		$_SESSION['isAdmin'] = 1;
	}
	else {
		$_SESSION['isAdmin'] = 0;
	}

	//kod, ktory aktywuje sie w momencie logowania
	if ((isset($_POST['submit'])) && (!empty($_POST['submit'])) && (empty($_POST['username_regis']))) {
		$login = mysqli_real_escape_string($conn,$_POST['username_login']);
    	$password = mysqli_real_escape_string($conn,$_POST['password']);

		//liczymy czy liczba rekordow odpowiadajacym loginie i hasle jest wieksza od zera (czyli gdy podano dobre dane logowania)
		$sql_query = "select count(*) as cntUser from Users where Username='".$login."' and Password='".$password."'";
        $result = mysqli_query($conn,$sql_query);
        $row = mysqli_fetch_array($result);

        $count = $row['cntUser'];

		//gdy liczba rekordow wieksza niz zero (dobre dane logowania)
        if($count > 0){
            $_SESSION['username'] = $login;
            header('location: index.php');
			$_SESSION['wrong_login'] = "0";
			$_SESSION['isLogged'] = "1";
			
			//sprawdzamy czy uzytkownik ma uprawnienia administratora
			$isAdminCheck_s = mysqli_fetch_row(mysqli_query($conn,"SELECT isAdmin FROM Users WHERE Username='".$login."'"));
    		$isAdminCheck = $isAdminCheck_s[0];
			
			//kiedy wynik kwerendy jest rowny "1" to zalogowano sie na administratora
			if($isAdminCheck == 1){
				$_SESSION['isAdmin'] = 1;
			}
			else {
				$_SESSION['isAdmin'] = 0;
			}
        }
		//gdy liczba rekordow nie jest wieksza od zera (zle dane logowania)
		else {
			$_SESSION['wrong_login'] = "1";
    	}
	}

	//kod, ktory aktywuje sie w momencie rejestracji
    if ((isset($_POST['submit'])) && (!empty($_POST['submit'])) && (!empty($_POST['username_regis']))) {
		$login_rej = mysqli_real_escape_string($conn,$_POST['username_regis']);
    	$pass_rej = mysqli_real_escape_string($conn,$_POST['pass']);

		//liczymy czy w bazie danych znajduje sie uzytkownik z podanym username w rejestracji
		$sql_query = "select count(*) as cntUser from Users where username='".$login_rej."'";
        $result = mysqli_query($conn,$sql_query);
        $row = mysqli_fetch_array($result);

        $count = $row['cntUser'];

		//jesli tak, to flaga zlej rejestracji jest aktywna
        if($count > 0){
			$_SESSION['wrong_regis'] = "1";
        }
		//jesli nie, to znaczy ze username jest wolny i mozna sie rejestrowac
		else {
			$_SESSION['username'] = $login_rej;
            
			//wpisanie loginu i hasla do bazy danych
			$sql = "INSERT INTO Users (Username, Password) VALUES ('".$login_rej."', '".$pass_rej."')";
			if(mysqli_query($conn, $sql)){
				header('location: index.php');
				$_SESSION['wrong_regis'] = "0";
				$_SESSION['isLogged'] = "1";

				//sprawdzamy czy uzytkownik ma uprawnienia administratora
				$isAdminCheck_s = mysqli_fetch_row(mysqli_query($conn,"SELECT isAdmin FROM Users WHERE Username='".$login."'"));
    			$isAdminCheck = $isAdminCheck_s[0];
			
				//kiedy wynik kwerendy jest rowny "1" to zalogowano sie na administratora
				if($isAdminCheck == 1){
					$_SESSION['isAdmin'] = 1;
				}
				else {
					$_SESSION['isAdmin'] = 0;
				}
			}
			else {
    			echo "BŁAD: $sql. " . mysqli_error($link);
			}
			exit();
    	}
	}

	//kod aktywujacy sie gdy wyszukujemy cos w pasku wyszukiwania
	if ((isset($_POST['search_word'])) && (!empty($_POST['search_word']))) {
		$search_word = mysqli_real_escape_string($conn,$_POST['search_word']);

		//przenosimy sie na strone z parametrem GET naszego szukanego wyrazu
		header('location: http://www.ppie2018.s.zs1.stargard.pl/search.php?search='.$search_word.'');
	}
?>

<!DOCTYPE html>
<html>
    <head>
		<meta charset="UTF-8">
		<link rel="stylesheet" href="style.css">
        <link rel="shortcut icon" href="Grafika/Logo.png">
        
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
		<script>
			var isLogged = "<?php echo $_SESSION['isLogged']; ?>";
			var wrong_login = "<?php echo $_SESSION['wrong_login']; ?>";
			var wrong_regis = "<?php echo $_SESSION['wrong_regis']; ?>";
			var username = "<?php echo $_SESSION['username']; ?>";
		</script>
		<script src="script.js"></script>

		<title>E-Biblioteka</title>
		<meta name="author" content="Piotr Pietrusewicz"/>
		<meta name="description" content="E-Biblioteka dla Ciebie!"/>
		<meta name="keywords" content="biblioteka, ksiazki, opinie, wypozyczanie"/>
		<meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no"/>
    </head>
    <body>
	    <div class="top_strip">
            <img id="logo" src="Grafika/Logo_white.png" alt="logo" heigth="35px" width="35px" onclick="myFunction()">
            <img id="search_icon" src="Grafika/search_icon.png" alt="search_icon" heigth="10px" width="15px">
            <img id="logo_napis" src="Grafika/Logo_napis_white.png" alt="logo_napis" heigth="35px" width="120px" onclick="myFunction()">
            <form id="search_form" method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
				<input id="wyszukaj" type="text" name="search_word" placeholder="Wyszukaj książki po tytule, bądź autorze...">
				<input id="hide_search_submit" type="submit" name="">
			</form>
			<div class="login_box_main">
                <img id="avatar" src="Grafika/default_avatar.png" alt="avatar" height="26px" width="26px">
                <div id="username">Zaloguj się
					<script>
						if (isLogged != '1') {
							$("#username").text("Zaloguj się");
						} else {
							$("#username").text(username);
						}
					</script>
				</div>
                <img id="pointer" src="Grafika/pointer_down.png" alt="pointer" height="12px" width="12px" onclick="myFunction()">
                <div id="login_box" class="login_box">
					<div id="hidden_variables_to_debug">
						<input type="hidden" id="wrong_login" value="<?php echo $_SESSION['wrong_login']; ?>">
						<input type="hidden" id="wrong_regis" value="<?php echo $_SESSION['wrong_regis']; ?>">
						<input type="hidden" id="isLogged" value="<?php echo $_SESSION['isLogged']; ?>">
						<input type="hidden" id="username" value="<?php echo $_SESSION['username']; ?>">
					</div>
					<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
		    	        <input id="btnLogowanieID" class="btnLogowanie active" type="button" value="Logowanie"><input id="btnRejestracjaID" class="btnRejestracja" type="button" value="Rejestracja">
                        <div id="logowanie">
			            	<div class="group">
			        	    	<label id="label_username_login" for="username_login" class="label">Nazwa użytkownika</label>
			        	    	<input id="username_login" name="username_login" type="text" placeholder="Nazwa użytkownika" class="input" pattern=".{4,}" title="Wymagana długość nazwy użytkownika to 4 znaki" required>
			        	    </div>
			        	    <div class="group">
			    	    	    <label for="password" class="label">Hasło</label>
			    	    	    <input id="password" name="password" type="password" placeholder="Hasło" class="input" data-type="password" pattern=".{8,}" title="Wymagana długość hasła to 8 znaków" required>
			    	        </div>
    						<div class="wrong_login"> Podano błędne dane logowania</div>
			    	        <div class="group">
			    	    	    <input type="submit" id="submit" name="submit" class="button" value="Zaloguj się">
			    	        </div>
		    	        </div>
		    	        <div id="rejestracja">
			    	        <div class="group">
			    	    	    <label id="label_regis_login" for="username_regis" class="label">Nazwa użytkownika</label>
			    	    	    <input id="username_regis" name="username_regis" type="text" placeholder="Nazwa użytkownika" class="input" pattern=".{4,}" title="Wymagana długość nazwy użytkownika to 4 znaki" required>
			    	        </div>
			    	        <div id="RejHaslo" class="group">
			    	    	    <label for="pass" class="label">Hasło</label>
			    	    	    <input id="pass" name="pass" type="password" placeholder="Hasło" class="input" data-type="password" pattern=".{8,}" title="Wymagana długość hasła to 8 znaków" required>
			    	        </div>
			    	        <div id="RejHasloPow" class="group">
			    	    	    <label for="pass_conf" class="label">Powtórz hasło</label>
			    	    	    <input id="pass_conf" name="pass_conf" type="password" placeholder="Powtórz hasło" class="input" data-type="password" pattern=".{8,}" title="Wymagana długość hasła to 8 znaków" required>
			    	        </div>

					        <script>
					    	    var password = document.getElementById("pass") ,
 					    	    	confirm_password = document.getElementById("pass_conf");
					    	    function validatePassword(){
  					        	if(pass.value != pass_conf.value) {
   					        		 	pass_conf.setCustomValidity("Hasła nie są identyczne");
  					        		} else {
   					        			pass_conf.setCustomValidity('');
 					        	 	}
					        	}
					        	pass.onchange = validatePassword;
					        	pass_conf.onkeyup = validatePassword;
					        </script>

    						<div class="wrong_regis"> Nazwa użytkownika jest zajęta</div>
			    	        <div class="group">
			    		        <input type="submit" id="submit2" name="submit" class="button" value="Zarejestruj się">
                            </div>
                        </div>
			        </form>
                </div>
                <div id="log_out_box">
					<?php
						if ($_SESSION['isAdmin'] == 1) {
							echo '<input id="borrowed_books_button" value="Wypożyczone książki">';
						} else {
							echo '<input id="mybooks_button" value="Moje książki">';
						}
					?>
                    <input id="log_out_button" value="Wyloguj się">
                </div>
            </div>
	    </div>
        <div class="main_part">
			<div id="alert_container_resolution" class="alert_resolution">
  				<span id="alert_close_resolution" class="closebtn" onclick="myFunction()">&times;</span> 
  				<strong>Powiadomienie</strong><br>Zaleca się używanie monitora o rozdzielczości 1920x1080 wraz z przeglądarką Google Chrome.
			</div>
			<div class="main_panel">
				<!--<div id="alert_container" class="alert">
  					<span id="alert" class="closebtn" onclick="myFunction()">&times;</span> 
  					<strong>Błąd!</strong>Musisz być zalogowany by móc dodawać posty.
				</div>-->
				<?php
					if ($_SESSION['isAdmin'] == 1) {
						echo '<div id="add_post">
							<img id="avatar_add_new_post" src="Grafika/default_avatar.png" alt="avatar" height="34px" width="34px">
							<button id="add_new_post" onclick="myFunction()">Dodaj książkę</button>
							</div>';
					}
				?>
				<div id="newest_posts_information">
                	Najnowsze dodane książki:
            	</div>
				<?php 
					//wyciagamy najwieksze id z tablicy z postami (najwieksze id=najnowszy wpis)
					$ID_max_check = mysqli_fetch_row(mysqli_query($conn,"SELECT MAX(ID) FROM Books"));
					$max_ID = $ID_max_check[0];
					$ID_minus = $max_ID - 20;
					
					//petla wyswietlajaca 20 najnowszych postow
					for ($i = $max_ID; $i > $ID_minus; $i--) {
						$title_s = mysqli_fetch_row(mysqli_query($conn,"SELECT Tytul FROM Books WHERE ID='".$i."'"));
    					$title = $title_s[0];
						$text_s = mysqli_fetch_row(mysqli_query($conn,"SELECT Autor FROM Books WHERE ID='".$i."'"));
    					$text = $text_s[0];
						$author_s = mysqli_fetch_row(mysqli_query($conn,"SELECT Gatunek FROM Books WHERE ID='".$i."'"));
    					$author = $author_s[0];

						$okladka_s = mysqli_fetch_row(mysqli_query($conn,"SELECT Okladka FROM Books WHERE ID='".$i."'"));
    					$okladka = $okladka_s[0];

						//element kontrolny sprawdzajacy, czy dany rekord jest ostatnim
						if ($i > $ID_minus+1) {
							echo '<div class="post_display wrapping">
									<table>
										<tr>
											<th>
												<img id="okladka_index" src="'.$okladka.'">
											</th>
										</tr>
										<tr>
											<td>
												<div id="post_display_title">'.$title.'</div>
												<div id="post_display_author">'.$text.'</div>
												<div id="post_display_genre">'.$author.'</div>
											</td>
										</tr>
									</table>
									<a href="http://www.ppie2018.s.zs1.stargard.pl/post.php?id='.$i.'"></a>
								</div>';
						} else {
						//ostatni id z dodana klasa "last"
							echo '<div class="post_display wrapping last">
									<table>
										<tr>
											<th>
												<img id="okladka_index" src="'.$okladka.'">
											</th>
										</tr>
										<tr>
											<td>
												<div id="post_display_title">'.$title.'</div>
												<div id="post_display_author">'.$text.'</div>
												<div id="post_display_genre">'.$author.'</div>
											</td>
										</tr>
									</table>
									<a href="http://www.ppie2018.s.zs1.stargard.pl/post.php?id='.$i.'"></a>
								</div>';
						}
					}
				?>
            </div>
            <div class="side_panel">
                <div id="popularne">
                    Najpopularniejsze książki:<br>
					<div id="popularne_content">
						<?php						
							//petla wyswietlajaca 10 najpopularniejszych postow
							for ($y = 0; $y <= 9; $y++) {
								//select wybierajacy najnowszego posta z najwieksza iloscia komentarzy
								$id_popularny_post_check = mysqli_fetch_row(mysqli_query($conn,"SELECT post_id from (select post_id, count(*) as wystapienia from Comments group by post_id order by wystapienia desc, post_id desc LIMIT 1 OFFSET ".$y.") as wynik;"));
								$id_popularny_post = $id_popularny_post_check[0];

								$title_s = mysqli_fetch_row(mysqli_query($conn,"SELECT Tytul FROM Books WHERE ID='".$id_popularny_post."'"));
								$title = $title_s[0];
								$author_s = mysqli_fetch_row(mysqli_query($conn,"SELECT Autor FROM Books WHERE ID='".$id_popularny_post."'"));
								$author = $author_s[0];
								$liczba_komentarzy_s = mysqli_fetch_row(mysqli_query($conn,"SELECT count(*) FROM Comments WHERE post_id='".$id_popularny_post."'"));
								$liczba_komentarzy = $liczba_komentarzy_s[0];
								
								//wyswietlenie tych komentarzy
								echo '<div class="popularne_posty">
										<div id="popularne_posty_title">'.$title.'</div>
										<div id="popularne_posty_author">Dodano przez: '.$author.'</div>
										<div id="popularne_posty_liczba_komentarzy">Liczba komentarzy: '.$liczba_komentarzy.'</div>
										<a href="http://www.ppie2018.s.zs1.stargard.pl/post.php?id='.$id_popularny_post.'"></a>
									</div>';
								
								//nowy element, ktory nie moze byc dodany pod ostatnim komentarzem ze wzgledow estetycznych
								if ($y != 9) {
									echo '<hr class="rounded">';
								}
							}							
						?>
					</div>
                </div>
            </div>
        </div>
		<div class="footer">
  			<p>@Piotr Pietrusewicz 2021</p>
		</div>
    </body>
</html>