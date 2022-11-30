$(document).ready(function () {
    $("#username_login").val('');
    $("#password").val('');
    $("#username_regis").val('');
    $("#pass").val('');
    $("#pass_conf").val('');
    
    $('html').css('display', 'none');
    $('html').fadeIn(1500);

    $("#hint_wrap").hide();

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

    setTimeout(function() {
        $("#btnRejestracjaID").attr("disabled", false); 
        $("#username_login").attr("disabled", false);
        $("#password").attr("disabled", false);
    }, 1000);

    $("#btnLogowanieID").click(function() {
        $("#btnLogowanieID").addClass("active");
        $("#btnLogowanieID").removeClass("btnLogRej");
        $("#btnRejestracjaID").addClass("btnLogRej");
        $("#btnRejestracjaID").removeClass("active");
        $("#username_regis").val('');
        $("#pass").val('');
        $("#pass_conf").val('');

        $("#logowanie").show("slow");
        $("#rejestracja").hide("slow");

        $("#btnLogowanieID").attr("disabled", true);
        $("#username_regis").attr("disabled", true);
        $("#pass").attr("disabled", true);
        $("#pass_conf").attr("disabled", true);

        setTimeout(function() {
            $("#btnRejestracjaID").attr("disabled", false); 
            $("#username_login").attr("disabled", false);
            $("#password").attr("disabled", false);
        }, 600);
    });

    $("#btnRejestracjaID").click(function() {
        $("#btnRejestracjaID").addClass("active");
        $("#btnRejestracjaID").removeClass("btnLogRej");
        $("#btnLogowanieID").addClass("btnLogRej");
        $("#btnLogowanieID").removeClass("active");
        $("#username_login").val('');
        $("#password").val('');

        $("#logowanie").hide("slow");
        $("#rejestracja").show("slow");
        $("#hint_wrap").fadeOut(300)

        $("#btnRejestracjaID").attr("disabled", true);
        $("#username_login").attr("disabled", true);
        $("#password").attr("disabled", true);

        setTimeout(function() {
            $("#btnLogowanieID").attr("disabled", false); 
            $("#username_regis").attr("disabled", false);
            $("#pass").attr("disabled", false);
            $("#pass_conf").attr("disabled", false);
        }, 600);
    });

    $("#btnHint").click(function() {
        if ($('#hint_wrap').is(':visible') ) {
            $("#hint_wrap").fadeOut(300);
        } else {
            $("#hint_wrap").fadeIn(300);
        }  
    });
});