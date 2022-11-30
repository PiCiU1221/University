//Piotr Pietrusewicz @2021
//drugi plik javascript dla pliku dodawanie.php
$(document).ready(function() {
    $('html').css('display', 'none');
    $('html').fadeIn(200);

    $("#logo").click(function(){
        window.location.href = "http://www.ppie2018.s.zs1.stargard.pl";
    });
    $("#logo_napis").click(function(){
        window.location.href = "http://www.ppie2018.s.zs1.stargard.pl";
    });

    $("#login_box").hide();
    $("#log_out_box").hide();
    $(".wrong_login").hide();
    $(".wrong_regis").hide();
    $(".alert").hide();

    $("#pointer").click(function(){
        $("#log_out_box").slideToggle(200);
    }); 
					
	$("#log_out_button").click(function(){
        document.location = 'logout.php';
    }); 
});