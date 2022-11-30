<?php
    //Piotr Pietrusewicz @2021
    //plik php sluzacy do dodawnia postow
    include('db_connect.php');
    
    //przerzucenie na glowna strone gdy ktos nie jest zalogowany jako administrator
    if($_SESSION['isAdmin'] == 0){
        header('location: index.php');
    }
    
    if ((isset($_POST['submit'])) && (!empty($_POST['submit']))) {
		$tytul = $_POST['tytul'];
    	$autor = $_POST['autor'];
        $gatunek = $_POST['gatunek'];
    	$wydawnictwo = $_POST['wydawnictwo'];
        $rok = $_POST['rok'];

        $author = $_SESSION['username'];

        $file_get = $_FILES['image']['name'];
        $temp = $_FILES['image']['tmp_name'];

        $file_to_saved = "Ksiazki/".$file_get;
        move_uploaded_file($temp, $file_to_saved);

        $sql = "INSERT INTO Books (Tytul, Autor, Gatunek, Wydawca, Rok_wydania, Okladka) VALUES ('".$tytul."', '".$autor."', '".$gatunek."', '".$wydawnictwo."', '".$rok."', '".$file_to_saved."')";

        if(mysqli_query($conn, $sql)){
            //szukamy najnowszego postu autora i przenosimy go na strone postu
            $idSearch_s = mysqli_fetch_row(mysqli_query($conn,"SELECT ID FROM Books ORDER BY ID DESC"));
    		$idSearch = $idSearch_s[0];

            header('location: http://www.ppie2018.s.zs1.stargard.pl/post.php?id='.$idSearch.'');
        } else {
            echo "BŁAD: $sql. " . mysqli_error($link);
        }
	}

    if ((isset($_POST['search_word'])) && (!empty($_POST['search_word']))) {
		$search_word = mysqli_real_escape_string($conn,$_POST['search_word']);

		header('location: http://www.ppie2018.s.zs1.stargard.pl/search.php?search='.$search_word.'');
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
		<script src="script_dodawanie.js"></script>

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
				<input id="wyszukaj" type="text" name="search_word" placeholder="Wyszukaj książki po tytule, bądź autorze...">
				<input id="hide_search_submit" type="submit" name="">
			</form>
            
            <div class="login_box_main">
                <img id="avatar" src="Grafika/default_avatar.png" alt="avatar" height="26px" width="26px">
                <div id="username"><?php echo $_SESSION['username'];?></div>
                <img id="pointer" src="Grafika/pointer_down.png" alt="pointer" height="12px" width="12px">
                <div id="log_out_box">
                    <input id="borrowed_books_button" value="Wypożyczone książki">
                    <input id="log_out_button" value="Wyloguj się">
                </div>
            </div>
        </div>
        <div class="main_part_dodawanie">
            <div id="add_post_information">
                Dodawanie książki
            </div>
            <div class="main_panel">
                <div id="add_post">
                    <form method="post" enctype="multipart/form-data" action="<?php echo $_SERVER['PHP_SELF']; ?>" accept-charset="UTF-8">    
                        <textarea rows="1" id="adding_title" name="tytul" type="text" placeholder="Tytuł" pattern=".{8,}" title="Wymagana długość tytułu to 8 znaków" required></textarea>
                        <textarea rows="1" id="adding_title" name="autor" type="text" placeholder="Autor" pattern=".{8,}" title="Wymagana długość tytułu to 8 znaków" required></textarea>
                        <textarea rows="1" id="adding_title" name="gatunek" type="text" placeholder="Gatunek" pattern=".{8,}" title="Wymagana długość tytułu to 8 znaków" required></textarea>
                        <textarea rows="1" id="adding_title" name="wydawnictwo" type="text" placeholder="Wydawnictwo" pattern=".{8,}" title="Wymagana długość tytułu to 8 znaków" required></textarea>
                        <textarea rows="1" id="adding_title" name="rok" type="text" placeholder="Rok wydania" pattern=".{8,}" title="Wymagana długość tytułu to 8 znaków" required></textarea>
                        <input type="file" name="image" id="image">
                        <input type="submit" id="submit_post" name="submit" value="Dodaj książkę">
                    </form>
                </div>
            </div>
            <div class="side_panel_dodawanie">
                <!--<div id="popularne">
                    Zasady komentowania:<br>
                    <ol class="table_content">
                        <li>Nie postuj ofensywnych treści, linków, obrazków.</li>
                        <li>Nie spamuj (sprawdź czy nie ma podobnych odpowiedzi).</li>
                        <li>Nie postuj nie swoich treści bez podania źródła.</li>
                        <li>Nie reklamuj żadnych usług, produktów.</li>
                        <li>Szanuj innych użytkowników.</li>
                    </ol>
                </div>-->
            </div>
        </div>
        <div class="footer">
  			<p>@Piotr Pietrusewicz 2021</p>
		</div>
    </body>
</html>