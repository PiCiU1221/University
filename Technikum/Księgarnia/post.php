<?php
	//Piotr Pietrusewicz @2021
	//plik php wyswietlajacy wybrany post i jego komentarze
	include('db_connect.php');

	if(!empty($_GET["id"])){
		$i = $_GET["id"];
		$_SESSION["post_id"] = $i;
	} else {
		$i = $_SESSION["post_id"];
	}

	$username = $_SESSION['username'];
	$isReturned = 1;
					
	$isAvailable_s = mysqli_fetch_row(mysqli_query($conn,"SELECT MAX(ID) FROM Borrowed where book_id='".$i."'"));
	$isAvailable = $isAvailable_s[0];

	$isAvailable2_s = mysqli_fetch_row(mysqli_query($conn,"SELECT isReturned FROM Borrowed where ID='".$isAvailable."'"));
	$isAvailable2 = $isAvailable2_s[0];

	if ($isAvailable2 == 0) {
		$isReturned = 0;
	}

	$sql_query = "select count(*) as cntUser from Borrowed where book_id='".$i."'";
    $result = mysqli_query($conn,$sql_query);
    $row = mysqli_fetch_array($result);

    $count = $row['cntUser'];

	if ($count == 0) {
		$isReturned = 1;
	}

	if ($isReturned == 0) {
		$sql_query = "select count(*) as cntUser from Borrowed where book_id='".$i."' and Uzytkownik='".$_SESSION['username']."' and isReturned=0";
     	$result = mysqli_query($conn,$sql_query);
     	$row = mysqli_fetch_array($result);

     	$count = $row['cntUser'];

		if ($count == 1) {
			$isBorrowed = 1;
		}
	}
			
	//kiedy wynik kwerendy jest rowny "1" to zalogowano sie na administratora
	if($isAdminCheck == 1){
		$_SESSION['isAdmin'] = 1;
	}
	else {
		$_SESSION['isAdmin'] = 0;
	}

	if ((isset($_POST['submit'])) && (!empty($_POST['submit'])) && (empty($_POST['username_regis']))) {
		$login = mysqli_real_escape_string($conn,$_POST['username_login']);
    	$password = mysqli_real_escape_string($conn,$_POST['password']);

		$sql_query = "select count(*) as cntUser from Users where Username='".$login."' and Password='".$password."'";
        $result = mysqli_query($conn,$sql_query);
        $row = mysqli_fetch_array($result);

        $count = $row['cntUser'];

        if($count > 0){
            $_SESSION['username'] = $login;
			header("location: index.php");
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
		else {
			$_SESSION['wrong_login'] = "1";
    	}
	}

    if ((isset($_POST['submit'])) && (!empty($_POST['submit'])) && (!empty($_POST['username_regis']))) {
		$login_rej = mysqli_real_escape_string($conn,$_POST['username_regis']);
    	$pass_rej = mysqli_real_escape_string($conn,$_POST['pass']);

		$sql_query = "select count(*) as cntUser from Users where username='".$login_rej."'";
        $result = mysqli_query($conn,$sql_query);
        $row = mysqli_fetch_array($result);

        $count = $row['cntUser'];

        if($count > 0){
			$_SESSION['wrong_regis'] = "1";
        }
		else {
			$_SESSION['username'] = $login_rej;
            
			$sql = "INSERT INTO Users (Username, Password) VALUES ('".$login_rej."', '".$pass_rej."')";
			if(mysqli_query($conn, $sql)){
				header("location: index.php");
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

    if ((isset($_POST['submit_comment'])) && (!empty($_POST['submit_comment']))) {
		$comment_text = $_POST['comment_text'];
        $author = $_SESSION['username'];

        $sql = "INSERT INTO Comments (Author, post_id, text) VALUES ('".$author."', '".$i."', '".$comment_text."')";

        if(mysqli_query($conn, $sql)){
            header("location: http://www.ppie2018.s.zs1.stargard.pl/post.php?id=".$i);
        } else {
            echo "BŁAD: $sql. " . mysqli_error($link);
        }
	}

	if ((isset($_POST['search_word'])) && (!empty($_POST['search_word']))) {
		$search_word = mysqli_real_escape_string($conn,$_POST['search_word']);

		header('location: http://www.ppie2018.s.zs1.stargard.pl/search.php?search='.$search_word.'');
	}

	if (isset($_POST['wypozycz'])) {
        if ($isBorrowed == 1) {
			$sql = "UPDATE Borrowed SET isReturned=1, date_oddania=CURRENT_TIMESTAMP WHERE ID='".$isAvailable."'";

        	if(mysqli_query($conn, $sql)){
            	header("location: http://www.ppie2018.s.zs1.stargard.pl/post.php?id=".$i);
        	} else {
            	echo "BŁAD: $sql. " . mysqli_error($link);
        	}
		} else {
			$sql = "INSERT INTO Borrowed (book_id, Uzytkownik) VALUES ('".$i."', '".$username."')";

        	if(mysqli_query($conn, $sql)){
        	    header("location: http://www.ppie2018.s.zs1.stargard.pl/post.php?id=".$i);
        	} else {
         	   echo "BŁAD: $sql. " . mysqli_error($link);
        	}
		}
	}
?>

<!DOCTYPE html>
<html>
    <head>
		<meta charset="UTF-8">
		<link rel="stylesheet" href="style.css">
        <link rel="stylesheet" href="style_dodawanie.css">
        <link rel="shortcut icon" href="Grafika/Logo.png">

        <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
		<script src="script.js"></script>

        <script>
			var isLogged = "<?php echo $_SESSION['isLogged']; ?>";
			var wrong_login = "<?php echo $_SESSION['wrong_login']; ?>";
			var wrong_regis = "<?php echo $_SESSION['wrong_regis']; ?>";
			var username = "<?php echo $_SESSION['username']; ?>";
			var isReturned = "<?php echo $isReturned; ?>";
			var isBorrowed = "<?php echo $isBorrowed; ?>";
		</script>

		<script src="script_post.js"></script>

		<title>E-Biblioteka</title>
		<meta name="author" content="Piotr Pietrusewicz"/>
		<meta name="description" content="Najlepsze forum IT w Polsce!"/>
		<meta name="keywords" content="forum, IT, komputery, technologia, opinie, oceny, pomoc"/>
		<meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no"/>
    </head>
    <body>
	    <div class="top_strip">
            <img id="logo" src="Grafika/Logo_white.png" alt="logo" heigth="35px" width="35px" onclick="myFunction()">
            <img id="search_icon" src="Grafika/search_icon.png" alt="search_icon" heigth="10px" width="15px">
            <img id="logo_napis" src="Grafika/Logo_napis_white.png" alt="logo_napis" heigth="35px" width="120px" onclick="myFunction()">
            <form id="search_form" method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
				<input id="wyszukaj" type="text" name="search_word" placeholder="Wyszukaj posty...">
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
						<input type="hidden" id="isReturned" value="<?php echo $isReturned; ?>">
						<input type="hidden" id="isBorrowed" value="<?php echo $isBorrowed; ?>">
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
        <div class="main_part_post">
            <div class="main_panel">
                <div id="selected_post_display">
                    <?php
                        $title_s = mysqli_fetch_row(mysqli_query($conn,"SELECT Tytul FROM Books WHERE ID='".$i."'"));
    					$title = $title_s[0];
						$text_s = mysqli_fetch_row(mysqli_query($conn,"SELECT Autor FROM Books WHERE ID='".$i."'"));
    					$text = $text_s[0];
						$author_s = mysqli_fetch_row(mysqli_query($conn,"SELECT Gatunek FROM Books WHERE ID='".$i."'"));
    					$author = $author_s[0];
						$rok_s = mysqli_fetch_row(mysqli_query($conn,"SELECT Rok_wydania FROM Books WHERE ID='".$i."'"));
    					$rok = $rok_s[0];
						$wydawca_s = mysqli_fetch_row(mysqli_query($conn,"SELECT Wydawca FROM Books WHERE ID='".$i."'"));
    					$wydawca = $wydawca_s[0];
						$liczba_komentarzy_s = mysqli_fetch_row(mysqli_query($conn,"SELECT count(*) FROM Comments WHERE post_id='".$i."'"));
    					$liczba_komentarzy = $liczba_komentarzy_s[0];

						$okladka_s = mysqli_fetch_row(mysqli_query($conn,"SELECT Okladka FROM Books WHERE ID='".$i."'"));
    					$okladka = $okladka_s[0];

						echo '<div class="post_display2 wrapping">
							<table>
							<tr>
								<th class="th_class">
									<img id="okladka_post" src="'.$okladka.'">
								</th>
							</tr>
							<tr>
								<td class="td_class">
									<div id="post_display_title">'.$title.'</div>
									<div id="post_display_author">'.$text.'</div>
									<div id="post_display_genre">'.$author.'</div>
									<div id="post_display_genre">Wydawnictwo: '.$wydawca.'</div>
									<div id="post_display_genre">Rok wydania: '.$rok.'</div>
									<div id="post_display_time">Liczba komentarzy: '.$liczba_komentarzy.'</div>
								</td>
							</tr>
							</table>
							<a href="http://www.ppie2018.s.zs1.stargard.pl/post.php?id='.$i.'"></a>
							</div>';
                    ?>
                </div>
				<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>" accept-charset="UTF-8">    
                        <input id="wypozycz_button" type="submit" name="wypozycz" value="Wypożycz książkę">
                </form>
				<div id="newest_posts_information">
                	Komentarze:
            	</div>
				<?php		
					$ID_max_check = mysqli_fetch_row(mysqli_query($conn,"SELECT MAX(ID) FROM Comments"));
					$max_ID = $ID_max_check[0];
					
					for ($x = 1; $x <= $max_ID; $x++) {
						$sql_query = "select count(*) as cntComments from Comments where ID='".$x."' and post_id='".$i."'";
        				$result = mysqli_query($conn,$sql_query);
        				$row = mysqli_fetch_array($result);

        				$count = $row['cntComments'];

        				if($count > 0) {
							$text_s = mysqli_fetch_row(mysqli_query($conn,"SELECT text FROM Comments WHERE ID='".$x."'"));
    						$text = $text_s[0];
							$author_s = mysqli_fetch_row(mysqli_query($conn,"SELECT Author FROM Comments WHERE ID='".$x."'"));
    						$author = $author_s[0];
							$date_s = mysqli_fetch_row(mysqli_query($conn,"SELECT timestamp FROM Comments WHERE ID='".$x."'"));
    						$date = $date_s[0];

							echo '<div class="post_display2 wrapping margin-top">
									<div id="post_display_text">'.$text.'</div>
									<div id="post_display_author">Dodano przez: '.$author.'</div>
									<div id="post_display_time">'.$date.'</div>
								</div>';
        				}
					}
				?>
				<div id="add_comment">
                    <img id="avatar_add_new_post" src="Grafika/default_avatar.png" alt="avatar" height="34px" width="34px">
                    <form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>" accept-charset="UTF-8">    
                        <textarea rows="10" id="comment_text" name="comment_text" type="text" placeholder="Dodaj komentarz..." pattern=".{8,}" title="Wymagana długość tekstu to 8 znaków" required></textarea>
                        <input type="submit" id="submit_comment" name="submit_comment" value="Dodaj komentarz">
                    </form>
					<div id="alert_comment_container" class="alert_comment">
  						<span id="alert_comment" class="closebtn" onclick="myFunction()">&times;</span> 
  						<strong>Błąd!</strong> Musisz być zalogowany by móc dodawać posty.
					</div>
                </div>
				<div  class="spacer_post">.</div>
            </div>
            <div class="side_panel_dodawanie">
                <div id="popularne">
                    Zasady komentowania:<br>
                    <ol class="table_content">
                        <li>Nie postuj ofensywnych treści, linków, obrazków.</li>
                        <li>Nie spamuj (sprawdź czy nie ma podobnych odpowiedzi).</li>
                        <li>Nie postuj nie swoich treści bez podania źródła.</li>
                        <li>Nie reklamuj żadnych usług, produktów.</li>
                        <li>Szanuj innych użytkowników.</li>
                    </ol>
                </div>
            </div>
        </div>
		<div class="footer">
  			<p>@Piotr Pietrusewicz 2021</p>
		</div>
    </body>
</html>