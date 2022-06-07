window.onload = function() 
{ 
	exit();
    movimento();
} 

function getOperazione()
{
    var layer_console = document.getElementsByTagName("div")[((document.getElementsByTagName("div")).length)-1];
    console.log(layer_console);
    var equazione = layer_console.innerHTML;
    console.log("----> ",equazione)
    console.log(typeof(equazione))
    return equazione;
}

function risultato()
{
    var riga = getOperazione();
    console.log(typeof(riga))
    console.log(riga);
 
    if (riga.includes("calcolatrice"))
    {
        var index = riga.indexOf("calcolatrice");
        var len = ("calcolatrice".length) + 1;
    
        var equazione = riga.substring(index+ len, riga.indexOf(")"));
        equazione = equazione.replace(/ /g, '').replace(/"/g, '');
    
        return [0,calcolatrice2(equazione), riga.substring(index, (riga.indexOf(")"))+1), ">"];
    }
    if (riga.includes("help"))
    {
        return ["uname, saluto, data, calcolatrice, clear e ip", , ">"];
    } 
    if (riga.includes("clear"))
    {
        return [2, ">"];
    }
    if(riga.includes("uname"))
    {
        return[navigator.platform, ">"];
    }
    if(riga.includes("👋"))
    {
        if( navigator.userAgent.includes("Windows"))
        {
            return[4, "Hello, I am a Windows machine", ">"];
        }
        else if(navigator.userAgent.includes("Linux"))
        {
            return[4, "Hello, I am a Linux machine", ">"];
        }
        else if(navigator.userAgent.includes("Mac"))
        {
            return[4, "Hello, I am a Mac machine", ">"];
        }
        else
        {
            return[4, "Hello, I am a machine", ">"];
        }
    }
    if(riga.includes("data"))
    {
        return[5, new Date().toLocaleString(), ">"];
    }
    if(riga.includes("ip"))
    {
        function text(url) 
        {
            return fetch(url).then(res => res.text());
        
        text('https://www.cloudflare.com/cdn-cgi/trace').then(data => {
        let ipRegex = /[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}/
        let ip = data.match(ipRegex)[0];
        console.log(ip);
        document.getElementById("figlio").value = " " + ip;
        });
        }
    }
    else{
        console.log("Comando non valido");
        return[99, ">", "Comando non valido"];
    }
    
}

function stampa(){
    var input = risultato();
    console.log("STAMPA input --->", input);
    funzione();
    var layer_console = document.getElementsByTagName("div")[((document.getElementsByTagName("div")).length)-1];
    
    if (input[0] == 0)
    {
        var output = input[3] + " " + input[2] +" = "+ input[1];
        console.log(output)
        // funzione(input[3]);
    }
    if(input[0] == 1)
    {
        var output = input[3] + " " + input[2] +" "+ input[1];
        console.log(output)
        // funzione(input[3]);
    }
    if(input[0] == 2)
    {
        window.location.reload();
    }
    if(input[0] == 3)
    {
        var output = "uname";
        layer_console.innerHTML = output;
        window.close();
    }
    if(input[0] == 99)
    {
        var output = input[1] +" "+input[2];
        layer_console.innerHTML = output;
    }
    if(input[0] == 4)
    {
        var output = input[1] +"saluto";
        layer_console.innerHTML = output;
    }
    console.log(layer_console);
    layer_console.innerHTML = output;
    funzione(">");
    setFocus();
}



function invio(event){
    // ottengo il codice unicode del tasto premuto sfruttando la proprietà keyCode dell'oggetto event
    var codiceTasto = event.keyCode;
    if(codiceTasto === 13){
        event.preventDefault();
        stampa()
    }
}



function exit(e){
    console.log("Mi hanno fatto parite");
    var chiusura = document.getElementById("kill");
    chiusura.ondblclick = function(e) {
	    // e.target.innerHTML = "Hai fatto doppio click sul paragrafo!";
        window.close();
    }
}

function funzione(stringa, id){
    // "<div class="layer" contenteditable="true"></div>"
    // "<div id='"+id+"' contenteditable= '"+true+"' >"+stringa+"</div>"
    document.getElementById('contenitore').innerHTML += "<div class= layer  id = nuovoDiv contenteditable= true>"+ stringa+"</div>";
    
 }

 function setFocus(){
    var len = document.getElementsByClassName("layer").length;
    document.getElementsByClassName("layer")[len -1].focus();
 }


function movimento(){
    console.log("Sono dentro");
    var cursore;
    var offset = [0,0];
    var ogg;
    var click = false;
    ogg = document.getElementById("Blocco");
    document.body.appendChild(ogg);
    ogg.addEventListener('mousedown', function(e) {
      click = true;
      offset = [
        ogg.offsetLeft - e.clientX,
        ogg.offsetTop - e.clientY
      ];
    }, true);
    document.addEventListener('mouseup', function() {
      click = false;
    }, true);
    document.addEventListener('mousemove', function(event) {
      event.preventDefault();
      if (click) {
        cursore = {
          x : event.clientX,
          y : event.clientY
        };
        ogg.style.left = (cursore.x + offset[0]) + 'px';
        ogg.style.top  = (cursore.y + offset[1]) + 'px';
      }
    }, true);
    console.log("Sto uscendo");
}

function fullScreen(){
    
}