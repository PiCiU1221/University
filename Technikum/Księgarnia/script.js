//Piotr Pietrusewicz @2021
//glowny plik javascript dla forum
$(document).ready(function() {
    $('html').css('display', 'none');
    $('html').fadeIn(200);
    
    $("#add_new_post").click(function(){
        if (isLogged == 1) {
            window.location.href = "dodawanie.php";
        } else {
            $('#alert_container').fadeIn(300);
        }
    }); 

    $("#alert").click(function(){
        $('#alert_container').fadeOut(300);
    });

    $("#alert_close_resolution").click(function(){
        $('#alert_container_resolution').fadeOut(300);
    });

    $("#logo").click(function(){
        window.location.href = "http://www.ppie2018.s.zs1.stargard.pl";
    });
    $("#logo_napis").click(function(){
        window.location.href = "http://www.ppie2018.s.zs1.stargard.pl";
    });

    //$('.post_display').on( "click", function() {
    //    window.location.href = "http://www.ppie2018.s.zs1.stargard.pl/post.php?id=10";
    //});

    $("#login_box").hide();
    $("#log_out_box").hide();
    $(".wrong_login").hide();
    $(".wrong_regis").hide();
    $("#alert_container").hide();
    $("hide_search_submit").hide();

	if (isLogged == '1') {
		$("#pointer").click(function(){
            $("#log_out_box").slideToggle(200);
        }); 
					
	    $("#log_out_button").click(function(){
            document.location = 'logout.php';
    	});

        $("#mybooks_button").click(function(){
            document.location = 'mojeksiazki.php';
    	}); 

        $("#borrowed_books_button").click(function(){
            document.location = 'wypozyczone.php';
    	}); 
	} else {
		$("#pointer").click(function(){
            $("#login_box").slideToggle(200);
        }); 

        if (wrong_login == '1') {
    	    $('.wrong_login').show();
            $("#login_box").show();
        }
        if (wrong_regis == '1') {
    	    $('.wrong_regis').show();
            $("#login_box").show();
        }
	}

    $("#username_login").val('');
    $("#password").val('');
    $("#username_regis").val('');
    $("#pass").val('');
    $("#pass_conf").val('');

    $("#btnLogowanieID").addClass("active");
    $("#btnRejestracjaID").addClass("btnLogRej");
    $("#rejestracja").hide();
    $("#logowanie").show();

    $("#btnRejestracjaID").attr("disabled", true);
    $("#username_login").attr("disabled", true);
    $("#password").attr("disabled", true);

    $("#btnLogowanieID").attr("disabled", true);
    $("#username_regis").attr("disabled", true);
    $("#pass").attr("disabled", true);
    $("#pass_conf").attr("disabled", true);

    $("#btnRejestracjaID").attr("disabled", false); 
    $("#username_login").attr("disabled", false);
    $("#password").attr("disabled", false);

    $("#btnLogowanieID").click(function() {
        $("#btnLogowanieID").addClass("active");
        $("#btnLogowanieID").removeClass("btnLogRej");
        $("#btnRejestracjaID").addClass("btnLogRej");
        $("#btnRejestracjaID").removeClass("active");
        $("#username_regis").val('');
        $("#pass").val('');
        $("#pass_conf").val('');

        $("#logowanie").show(250);
        $("#rejestracja").hide(250);

        $("#btnLogowanieID").attr("disabled", true);
        $("#username_regis").attr("disabled", true);
        $("#pass").attr("disabled", true);
        $("#pass_conf").attr("disabled", true);

        $("#btnRejestracjaID").attr("disabled", false); 
        $("#username_login").attr("disabled", false);
        $("#password").attr("disabled", false);
    });

    $("#btnRejestracjaID").click(function() {
        $("#btnRejestracjaID").addClass("active");
        $("#btnRejestracjaID").removeClass("btnLogRej");
        $("#btnLogowanieID").addClass("btnLogRej");
        $("#btnLogowanieID").removeClass("active");
        $("#username_login").val('');
        $("#password").val('');

        $("#logowanie").hide(250);
        $("#rejestracja").show(250);

        $("#btnRejestracjaID").attr("disabled", true);
        $("#username_login").attr("disabled", true);
        $("#password").attr("disabled", true);

        $("#btnLogowanieID").attr("disabled", false); 
        $("#username_regis").attr("disabled", false);
        $("#pass").attr("disabled", false);
        $("#pass_conf").attr("disabled", false);
    });

    $(".post_display").click(function() {
        window.location = $(this).find("a").attr("href"); 
        return false;
      });

    $(".post_display_moje").click(function() {
        window.location = $(this).find("a").attr("href"); 
        return false;
    });

    $(".popularne_posty").click(function() {
        window.location = $(this).find("a").attr("href"); 
        return false;
      });
});