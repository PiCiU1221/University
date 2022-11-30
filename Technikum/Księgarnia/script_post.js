//Piotr Pietrusewicz @2021
//plik javascript dla pliku post.php
$(document).ready(function() {

    $("#alert_comment_container").hide();

    $("#alert_comment").click(function(){
        $('#alert_comment_container').fadeOut(300);
    });

    if (isLogged == '1') {
        $("#comment_text").click(function(){
            $("#comment_text").height("114px");
    	}); 
	} else {
		$("#comment_text").click(function(){
            $('#alert_comment_container').fadeIn(300);
    	}); 

        $("#submit_comment").click(function(){
            $('#alert_comment_container').fadeIn(300);
        }); 
	}

    if (isLogged != '1') {
        $("#wypozycz_button").attr("disabled", true);
        $('#wypozycz_button').val("Zaloguj się, by móc wypożyczyć");
    }
    
    if (isBorrowed == '1') {
        $("#wypozycz_button").attr("disabled", false);
        $("#wypozycz_button").css("background-color", "#008000");
        $('#wypozycz_button').val("Zwróć książkę");
    } else if (isReturned == '0') {
        $("#wypozycz_button").attr("disabled", true);
        $("#wypozycz_button").css("background-color", "#999");
        $('#wypozycz_button').val("Książka już wypożyczona");
	}
});