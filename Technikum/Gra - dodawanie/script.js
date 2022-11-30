var a = Math.floor(Math.random()*9+1);
var b = Math.floor(Math.random()*9+1);

window.onload = function() {
	document.getElementById('liczba1').innerHTML = a;
	document.getElementById('liczba2').innerHTML = b;
}

var wynik = a + b;
var punkty = 0;
var table1 = 0, table2 = 0, table3 = 0, table4 = 0, table5 = 0;
var rozwiazanie = document.getElementById('rozwiazanie').value;

function przycisk() {
	rozwiazanie = document.getElementById('rozwiazanie').value;
	
	if(rozwiazanie == wynik) 
	{
		punkty = punkty + 1;
		document.getElementById('punkty').innerHTML = punkty;
		alert('Gratulacje, udało ci się!');
	} 
	else 
	{
		alert('Niestety, ale poprawna odpowiedź to: ' + wynik);
		if(punkty >= table1)
		{
			table5 = table4;
			table4 = table3;
			table3 = table2;
			table2 = table1;
			table1 = punkty;
		}
		else if(punkty >= table2)
		{
			table5 = table4;
			table4 = table3;
			table3 = table2;
			table2 = punkty;
		}
		else if(punkty >= table3)
		{
			table5 = table4;
			table4 = table3;
			table3 = punkty;
		}
		else if(punkty >= table4)
		{
			table5 = table4;
			table4 = punkty;
		}
		else if(punkty >= table5)
		{
			
			table5 = punkty;
		}
		document.getElementById('table1').innerHTML = table1;
		document.getElementById('table2').innerHTML = table2;
		document.getElementById('table3').innerHTML = table3;
		document.getElementById('table4').innerHTML = table4;
		document.getElementById('table5').innerHTML = table5;
			
		punkty = 0;
		document.getElementById('punkty').innerHTML = punkty;
	}
	
	document.getElementById('rozwiazanie').value = "";
	
	a = Math.floor(Math.random()*9+1);
	b = Math.floor(Math.random()*9+1);

	document.getElementById('liczba1').innerHTML = a;
	document.getElementById('liczba2').innerHTML = b;

	wynik = a + b;
}


