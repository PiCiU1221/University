var number = Math.floor(Math.random()*5)+1;
var check = number;

var zart1 = "Lekarz mówi pacjentowi:<br>- Zdiagnozowano u pana poważną chorobę.<br>- Tylko nie to!<br>- Ale dzięki zdrowej diecie i regularnym ćwiczeniom można ją pokonać.<br>- TYLKO NIE TO!";
var zart2 = "Szukam pracy.<br>- Ok. Oto miotła, zacznij zamiatać.<br>- Przepraszam, ale ja skończyłem Uniwersytet Warszawski.<br>- Uuu, to daj, pokażę ci jak.";
var zart3 = "Rozmowa kwalifikacyjna:<br>- Pije pan?<bR>- Skądże. Ja czuję wstręt do samego zapachu alkoholu.<br>- Wygląda na to, że nie jest pan gotowy do pracy w zespole.";
var zart4 = "Rozmawia dwóch lekarzy:<br>- Wiesz, że na koronawirusa najlepszy jest czosnek?<br>- Podnosi odporność?<br>- Nie, ale sprawia, że nikt się do ciebie nie zbliży na mniej niż metr.";
var zart5 = "W małym miasteczku rozmawiają dwie kobiety:<br>- Mam kłopot, mąż nie wrócił na noc, więc wysłałam do pięciu jego kolegów depeszę z zapytaniem, czy nocował u nich.<br>- I co?<br>- Dostałam pięć odpowiedzi na tak.";

window.onload = function() {
	if(number == 1)
	document.getElementById('zart_text').innerHTML = zart1;
	else if(number == 2)
	document.getElementById('zart_text').innerHTML = zart2;
	else if(number == 3)
	document.getElementById('zart_text').innerHTML = zart3;
	else if(number == 4)
	document.getElementById('zart_text').innerHTML = zart4;
	else if(number == 5)
	document.getElementById('zart_text').innerHTML = zart5;
}
	
	
function przycisk() {
	
	while(number == check)	{
		number = Math.floor(Math.random()*5)+1;
	}
	
	check = number;
	
	if(number == 1)
	document.getElementById('zart_text').innerHTML = zart1;
	else if(number == 2)
	document.getElementById('zart_text').innerHTML = zart2;
	else if(number == 3)
	document.getElementById('zart_text').innerHTML = zart3;
	else if(number == 4)
	document.getElementById('zart_text').innerHTML = zart4;
	else if(number == 5)
	document.getElementById('zart_text').innerHTML = zart5;
}