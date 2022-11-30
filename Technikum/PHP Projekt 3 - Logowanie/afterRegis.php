<?php
	session_start();
	$login = $_SESSION['username'];
?>

<!DOCTYPE html>
<html>
    <head>
		<meta charset="UTF-8">
		<link rel="stylesheet" href="style.css">
		<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
		<script src="scriptSucc.js"></script>
		<link rel="shortcut icon" href="Grafika/zs1_logo_icon.png">

		<title>ZS1 Logowanie</title>
		<meta name="author" content="Piotr Pietrusewicz"/>
		<meta name="description" content="Logowanie i rejestracja ZS1"/>
		<meta name="keywords" content="logowanie, rejestracja, log-in, sign-up, ZS1"/>
		<meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no"/>
    </head>
    <body>
	    <div class="logo_szkoly"><img id="logo_szkoly" src="Grafika/zs1_logo.png" alt="Logo szkoly"></div>
		<div class="login_box">
            <div id="usernameTag" class="group">
                <?php
					echo "Witaj, " . $login;
				?>
            </div>
	    	<div id="welcomeTag" class="group welcomeTagRej"> 
                Zarejestrowano pomyślnie.
            </div>
	    </div>
    </body>
</html>