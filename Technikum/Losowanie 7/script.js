var zawiera_siedem = false;
var i = 0;
var j = 0;
var numer = Math.floor(Math.random() * 100+1);

const sleep = (delay) => new Promise((resolve) => setTimeout(resolve, delay));

async function przycisk() {
	document.getElementById("button").disabled = true;
	var tablica = Array.from({length: 5}, () => Math.floor(Math.random() * 100+1));
	
	for (i = 1; i < 6; i++) {
		document.getElementById('liczba' + i + '_text').innerHTML = "?";
	}
	
	for (i = 1; i < 6; i++) {
		for (j = 0; j < 5; j++) {
			numer = Math.floor(Math.random() * 100+1);
			document.getElementById('liczba' + i + '_text').innerHTML = numer;
			await sleep(100);
		}
		document.getElementById('liczba' + i + '_text').innerHTML = tablica[i-1];
		if (i < 5) await sleep(100);
	}
	
	for (i = 0; i < 5; i++) {
		var tablica_check = Array.from(tablica[i].toString()).map(Number);
		var check_boolean = tablica_check.includes(7);
		if (check_boolean == true) {
			zawiera_siedem = true;
		}
	}
	
	setTimeout(() => {
	if (zawiera_siedem == true) {
		alert("BOOOM!!!")
		zawiera_siedem = false;
		document.getElementById("button").disabled = false;
	}
	else {
		alert("Nie wylosowano siódemki");
		document.getElementById("button").disabled = false;
	}
	}, 100);
}
