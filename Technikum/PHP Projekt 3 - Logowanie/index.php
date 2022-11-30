<?php
	include('db_connect.php');
	
	session_start();
	if ((isset($_POST['submit'])) && (!empty($_POST['submit'])) && (empty($_POST['username_regis']))) {
		$login = mysqli_real_escape_string($conn,$_POST['username_login']);
    	$password = mysqli_real_escape_string($conn,$_POST['password']);

		$sql_query = "select count(*) as cntUser from Users where username='".$login."' and password='".$password."'";
        $result = mysqli_query($conn,$sql_query);
        $row = mysqli_fetch_array($result);

        $count = $row['cntUser'];

        if($count > 0){
            $_SESSION['username'] = $login;
            header('location: afterLogin.php');
			exit();
        }
		else {
            header('location: badLogin.php');
            exit();
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
            header('location: badRegis.php');
			exit();
        }
		else {
			$_SESSION['username'] = $login_rej;
            header('location: afterRegis.php');
            
			$sql = "INSERT INTO Users (USERNAME, PASSWORD) VALUES ('".$login_rej."', '".$pass_rej."')";
			if(mysqli_query($conn, $sql)){
				header('location: afterRegis.php');
    			echo "Rekordy prowadzono pomyślnie.";
			}
			else {
    			echo "BŁAD: $sql. " . mysqli_error($link);
			}
    	}
		exit();
	}
?>

<!DOCTYPE html>
<html>
    <head>
		<meta charset="UTF-8">
		<link rel="stylesheet" href="style.css">
		<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
		<script src="script.js"></script>
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
	    	<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
		    	<input id="btnLogowanieID" class="btnLogowanie active" type="button" value="Logowanie"><input id="btnRejestracjaID" class="btnRejestracja" type="button" value="Rejestracja">
                <div id="logowanie">
					<div class="group">
						<input type="button" id="btnHint" value="Zobacz jak się zalogować!">
						<div id="hint_wrap">
							<div id="hint_box">
								<div id="hint_content">
									Login: "1234" </br></br> Hasło: "12345678"
								</div>
							</div>
						</div>
					</div>
			    	<div class="group">
			    		<label for="username_login" class="label">Nazwa użytkownika</label>
			    		<input id="username_login" name="username_login" type="text" placeholder="Nazwa użytkownika" class="input" pattern=".{4,}" title="Wymagana długość nazwy użytkownika to 4 znaki" required>
			    	</div>
			    	<div class="group">
			    		<label for="password" class="label">Hasło</label>
			    		<input id="password" name="password" type="password" placeholder="Hasło" class="input" data-type="password" pattern=".{8,}" title="Wymagana długość hasła to 8 znaków" required>
			    	</div>
			    	<div class="group">
			    		<input type="submit" id="submit" name="submit" class="button" value="Zaloguj się">
			    	</div>
		    	</div>
		    	<div id="rejestracja">
			    	<div class="group">
			    		<label for="username_regis" class="label">Nazwa użytkownika</label>
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

			    	<div class="group">
			    		<input type="submit" id="submit" name="submit" class="button" value="Zarejestruj się">
			    	</div>
			    </div>
			</form>
	    </div>
    </body>
</html>