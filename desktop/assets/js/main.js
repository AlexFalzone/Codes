
var z = 1;

function creazione_Shell() {
    new Terminale();
}

function creazione_Calcolatrice() {
    new Calcolatrice();
}

function creazione_Browser() {
    new Browser();
}

function funzione(contenitore,stringa){
    contenitore.innerHTML += "<div class= layer  id = layer contenteditable= true>"+ stringa+"</div>";
    
 }

 function setFocus(){
    var len = document.getElementsByClassName("layer").length;
    document.getElementsByClassName("layer")[len -1].focus();
 }

class Terminale{
    blocco;
    terminale;
    barra;
    icone_red;
    icone_yellow;
    icone_green;
    icone_text;
    contenitore;
    layer;

    constructor(){
        let blocco  = document.createElement('div');
        blocco.className = "blocco";
        blocco.id = "blocco";
        let terminale = document.createElement('div');
        terminale.className = "terminale";
        let barra = document.createElement('div');
        barra.className = "barra";
        let icone_red = document.createElement('div');
        icone_red.className = "icone_red";
        let icone_yellow = document.createElement('div');
        icone_yellow.className = "icone_yellow";
        let icone_green = document.createElement('div');
        icone_green.className = "icone_green";
        let icone_text = document.createElement('div');
        icone_text.className = "icone_text";
        icone_text.id = "icone_text"
        let contenitore = document.createElement('div');
        contenitore.className = "contenitore";
        contenitore.id = "contenitore";
        let layer = document.createElement('div');
        layer.className = "layer";
        layer.id = "layer";

        blocco.appendChild(terminale);
        terminale.appendChild(barra);
        terminale.appendChild(contenitore);
        barra.appendChild(icone_red);
        barra.appendChild(icone_yellow);
        barra.appendChild(icone_green);
        barra.appendChild(icone_text);
        contenitore.appendChild(layer);
       
        layer.contentEditable = "true";

        blocco.style.position = "absolute";
        icone_green.innerText = "◻️";
        icone_red.innerText = "X";
        icone_yellow.innerText = "_";
        icone_text.innerText = "Terminale";
        layer.innerText = ">";
        layer.style.contenteditable = "true";

        icone_text.style.cursor = "pointer";

        this.blocco = blocco;
        this.terminale = terminale;
        this.barra = barra;
        this.icone_green = icone_green;
        this.icone_red = icone_red;
        this.icone_yellow = icone_yellow;
        this.icone_text = icone_text;
        this.contenitore = contenitore;
        this.layer = layer;

        this.blocco.onmousedown = function()
        {
            this.style.zIndex = z;
            z++;
        }

        this.barra.onmousedown = function()
        {
            var cursore;
            var offset = [0,0];
            var ogg;
            var ogg1;
            var click = false;
            ogg1 = this.parentNode.parentNode;

            ogg1.style.zIndex = z;
            z++;
            ogg = ogg1.getElementsByTagName("div")[5];
   
            ogg.addEventListener('mousedown', function(e) 
            {
                click = true;
                offset = [ogg1.offsetLeft - e.clientX, ogg1.offsetTop - e.clientY];
            }, true);
            document.addEventListener('mouseup', function() 
            {
                click = false;
            }, true);
            document.addEventListener('mousemove', function(event) 
            {
            event.preventDefault();
            if (click) 
            {
                cursore = {
                x : event.clientX,
                y : event.clientY
                };
                ogg1.style.left = (cursore.x + offset[0]) + 'px';
                ogg1.style.top  = (cursore.y + offset[1]) + 'px';
                console.log("cliccato");
            }
            }, true);
        };
       
        this.icone_red.onclick = function()
        {
            this.parentNode.parentNode.parentNode.remove();
            return null;
        }

        this.icone_green.onclick = function()
        {
            this.parentNode.parentNode.parentNode.style.width = "100%";
            this.parentNode.parentNode.parentNode.style.height = "100%";
            this.parentNode.parentNode.parentNode.style.left = "0%";
            this.parentNode.parentNode.parentNode.style.top = "0%";
            this.parentNode.parentNode.parentNode.style.bottom = "0%";
            this.parentNode.parentNode.parentNode.style.right = "0%";
       }

       this.icone_yellow.onclick = function()
       {
            this.parentNode.parentNode.parentNode.style.width = "40%";
            this.parentNode.parentNode.parentNode.style.height = "40%";
            this.parentNode.parentNode.parentNode.style.left = "50%";
            this.parentNode.parentNode.parentNode.style.bottom = "50%";
       }

       this.contenitore.onkeydown = function(e)
       {
            var codiceTasto = e.keyCode;
            if(codiceTasto === 13)
            {
                e.preventDefault();
                var layer  = this.childNodes[(this.childNodes.length)-1];
                stampa(this ,layer);
            }
        }
       
    
        function getOperazione(layer)
        {
            var layer_console = layer;
            var equazione = layer_console.innerHTML;

            return equazione;
        }
        
        function risultato(layer)
        {
            var riga = getOperazione(layer);

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
                return [1, "uname, saluto, data, calcolatrice, clear e ip"];
            } 
            if (riga.includes("clear"))
            {
                return [2, ">"];
            }
            if(riga.includes("uname"))
            {
                return[3, navigator.platform, ">"];
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
                }

                text('https://www.cloudflare.com/cdn-cgi/trace').then(data => {
                let ipRegex = /[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}/
                let ip = data.match(ipRegex)[0];
                console.log(ip);
                // document.getElementById("figlio").value = " " + ip;
                });
                return [6, ip, ">"];
            }
            else{
                console.log("Comando non valido");
                return[99, ">", "Comando non valido"];
            }
        }
        
        function stampa(contenitore, layer){
            var input = risultato(layer);

            funzione(contenitore);

            var layer_console = contenitore.getElementsByTagName("div")[(contenitore.getElementsByTagName("div").length)-1];
            
            if (input[0] == 0){
                // var output = input[3] + " " + input[2] +" = "+ input[1];
            }
            if(input[0] == 1){
                var output = input[1];
                layer_console.innerHTML = output;
            }
            if(input[0] == 2){
                var output = input[2];
                layer_console.innerHTML = output;
            }
            if(input[0] == 3){
                var output = input[3];
                layer_console.innerHTML = output;
            }
            if(input[0] == 4){
                var output = input[4];
                layer_console.innerHTML = output;
            }
            if(input[0] == 5){
                var output = input[5];
                layer_console.innerHTML = output;
            }
            if(input[0] == 6){
                var output = input[6];
                layer_console.innerHTML = output;
            }
            if(input[0] == 99){
                var output = input[1] +" "+input[2];
                layer_console.innerHTML = output;
            }
            layer_console.innerHTML = output;
            funzione(contenitore, ">");
            setFocus();
        }

       
        document.body.appendChild(this.blocco);
    }


};

class Calcolatrice{
    container;
    calculator;
    calculator_display;
    calculator__keys;
    key__operator_som;
    key__operator_sot;
    key__operator_molt;
    key__operator_div;

    bottone_0;
    bottone_1;
    bottone_2;
    bottone_3;
    bottone_4;
    bottone_5;
    bottone_6;
    bottone_7;
    bottone_8;
    bottone_9;
    bottone_decimal;
    bottone_clear;
    bottone_uguale;

    constructor(){
        let container = document.createElement('div');
        container.className = "container";
        container.id = "container";
        

        let calculator = document.createElement('div');
        calculator.id = "calculator";
        calculator.className = "calculator";
        

        let calculator_display = document.createElement('div');
        calculator_display.className = "calculator__display";
        calculator_display.id = "calculator__display";
        calculator_display.innerText = "0";

        let calculator__keys = document.createElement("div");
        calculator__keys.className = "calculator__keys";
        calculator__keys.id = "calculator__keys";

        let key__operator_som = document.createElement("button");
        key__operator_som.className = "key--operator";
        key__operator_som.dataset.action = "add";
        key__operator_som.innerText = "+";

        let key__operator_sot = document.createElement("button");
        key__operator_sot.className = "key--operator";
        key__operator_sot.innerText = "-";
        key__operator_sot.dataset.action = "subtract";

        let key__operator_div = document.createElement("button");
        key__operator_div.className = "key--operator";
        key__operator_div.dataset.action = "divide";
        key__operator_div.innerText = "÷";

        let key__operator_molt = document.createElement("button");
        key__operator_molt.className = "key--operator";
        key__operator_molt.dataset.action = "multiply";
        key__operator_molt.innerText = "×";

        let bottone_0 = document.createElement("button");
        bottone_0.innerText = "0";
        let bottone_1 = document.createElement("button");
        bottone_1.innerText = "1";
        let bottone_2 = document.createElement("button");
        bottone_2.innerText = "2";
        let bottone_3 = document.createElement("button");
        bottone_3.innerText = "3";
        let bottone_4 = document.createElement("button");
        bottone_4.innerText = "4";
        let bottone_5 = document.createElement("button");
        bottone_5.innerText = "5";
        let bottone_6 = document.createElement("button");
        bottone_6.innerText = "6";
        let bottone_7 = document.createElement("button");
        bottone_7.innerText = "7";
        let bottone_8 = document.createElement("button");
        bottone_8.innerText = "8";
        let bottone_9 = document.createElement("button");
        bottone_9.innerText = "9";

        let bottone_decimal = document.createElement("button");
        bottone_decimal.innerText = ".";
        bottone_decimal.dataset.action = "decimal";
        let bottone_clear = document.createElement("button");
        bottone_clear.innerText = "AC";
        bottone_clear.dataset.action = "clear";
        let bottone_uguale = document.createElement("button");
        bottone_uguale.className = "key--equal";
        bottone_uguale.innerText = "=";
        bottone_uguale.dataset.action = "calculate";

        container.appendChild(calculator);
        calculator.appendChild(calculator_display);
        calculator.appendChild(calculator__keys);
        calculator__keys.appendChild(key__operator_som);
        calculator__keys.appendChild(key__operator_sot);
        calculator__keys.appendChild(key__operator_molt);
        calculator__keys.appendChild(key__operator_div);
        calculator__keys.appendChild(bottone_7);
        calculator__keys.appendChild(bottone_8);
        calculator__keys.appendChild(bottone_9);
        calculator__keys.appendChild(bottone_4);
        calculator__keys.appendChild(bottone_5);
        calculator__keys.appendChild(bottone_6);
        calculator__keys.appendChild(bottone_1);
        calculator__keys.appendChild(bottone_2);
        calculator__keys.appendChild(bottone_3);
        calculator__keys.appendChild(bottone_0);
        calculator__keys.appendChild(bottone_decimal);
        calculator__keys.appendChild(bottone_clear);
        calculator__keys.appendChild(bottone_uguale);


        this.container = container;
        this.calculator = calculator;
        this.calculator_display = calculator_display;
        this.calculator__keys = calculator__keys;
        this.key__operator_som = key__operator_som;
        this.key__operator_sot = key__operator_sot;
        this.key__operator_molt = key__operator_molt;
        this.key__operator_div = key__operator_div;

        this.bottone_0 = bottone_0;
        this.bottone_1 = bottone_1;
        this.bottone_2 = bottone_2;
        this.bottone_3 = bottone_3;
        this.bottone_4 = bottone_4;
        this.bottone_5 = bottone_5;
        this.bottone_6 = bottone_6;
        this.bottone_7 = bottone_7;
        this.bottone_8 = bottone_8;
        this.bottone_9 = bottone_9;
        this.bottone_decimal = bottone_decimal;
        this.bottone_clear = bottone_clear;
        this.bottone_uguale = bottone_uguale;

        
        this.bottone_clear.ondblclick = function(){
            this.parentNode.parentNode.parentNode.remove();
            return null;
        }

        this.container.onmousedown = function(){
            this.style.zIndex = z;
            z++;
        }

        this.calculator_display.onmousedown = function(){
            var cursore;
            var offset = [0,0];
            var ogg;
            var ogg1;
            var click = false;
            ogg1 = this.parentNode.parentNode;
            ogg1.style.zIndex = z;
            z++;
            ogg = ogg1.getElementsByTagName("div")[5];

            this.addEventListener('mousedown', function(e) {
                click = true;
                offset = [ogg1.offsetLeft - e.clientX, ogg1.offsetTop - e.clientY];
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
                ogg1.style.left = (cursore.x + offset[0]) + 'px';
                ogg1.style.top  = (cursore.y + offset[1]) + 'px';
            }
            }, true);
        };



        const calculate = (n1, operator, n2) => {
            const firstNum = parseFloat(n1)
            const secondNum = parseFloat(n2)
            if (operator === 'add') return firstNum + secondNum
            if (operator === 'subtract') return firstNum - secondNum
            if (operator === 'multiply') return firstNum * secondNum
            if (operator === 'divide') return firstNum / secondNum
        }


        const display = this.calculator_display;
        const calculators = this.calculator;
        const keys = calculators.getElementsByTagName("div")[1];

        keys.addEventListener('click', e => {
            if (e.target.matches('button')) {
                const key = e.target;
                const action = key.dataset.action;
                const keyContent = key.textContent;
                const displayedNum = display.textContent;
                const previousKeyType = calculators.dataset.previousKeyType
                
                if (!action) 
                {
                    if (
                      displayedNum === '0' ||
                      previousKeyType === 'operator' ||
                      previousKeyType === 'calculate'
                    ) {
                      display.textContent = keyContent
                    } else {
                      display.textContent = displayedNum + keyContent
                    }
                    calculators.dataset.previousKeyType = 'number'
                }
                  
                if (action === 'decimal') 
                {
                    if (!displayedNum.includes('.')) 
                    {
                      display.textContent = displayedNum + '.'
                    } else if (
                      previousKeyType === 'operator' ||
                      previousKeyType === 'calculate'
                    ) {
                      display.textContent = '0.'
                    }
                  
                    calculators.dataset.previousKeyType = 'decimal'
                }
        
    
                if (action === 'add' || action === 'subtract' || action === 'multiply' || action === 'divide')
                {
                    const firstValue = calculators.dataset.firstValue
                    const operator = calculators.dataset.operator
                    const secondValue = displayedNum
        
                    if (firstValue && operator && previousKeyType !== 'operator' && previousKeyType !== 'calculate') 
                    {
                      const calcValue = calculate(firstValue, operator, secondValue)
                      display.textContent = calcValue
                      calculators.dataset.firstValue = calcValue
                    } 
                    else 
                    {
                      calculators.dataset.firstValue = displayedNum
                    }
        
                    key.classList.add('is-depressed')
                    calculators.dataset.previousKeyType = 'operator'
                    calculators.dataset.operator = action
                }
        
                if (action === 'calculate') 
                {
                    let firstValue = calculators.dataset.firstValue
                    const operator = calculators.dataset.operator
                    const secondValue = displayedNum
                    if (firstValue) 
                    {
                        if (previousKeyType === 'calculate') 
                        {
                          firstValue = displayedNum
                          secondValue = calculators.dataset.modValue
                        }
                        
                        display.textContent = calculate(firstValue, operator, secondValue)
                    }
                   
                    calculators.dataset.modValue = secondValue
                    calculators.dataset.previousKeyType = 'calculate'
                }

                  
                if (action === 'clear') 
                {
                    if (key.textContent === 'AC') 
                    {
                        calculators.dataset.firstValue = ''
                        calculators.dataset.modValue = ''
                        calculators.dataset.operator = ''
                        calculators.dataset.previousKeyType = ''
                    } 
                    else 
                    {
                    key.textContent = 'AC'
                    }
                
                    display.textContent = 0
                    calculators.dataset.previousKeyType = 'clear';
                }
            }
        })



        document.body.appendChild(this.container);
    }
    
};

class Browser{

    Struttura;
    Testa;
    Pulsanti;
    kill;
    resize;
    fullScreen;
    link;
    Schermo;

    constructor(){

        let Struttura = document.createElement("div");
        Struttura.id = "Struttura";
        let Testa = document.createElement("div");
        Testa.id = "Testa";
        let Pulsanti = document.createElement("div");
        Pulsanti.id = "Pulsanti";
        let kill  = document.createElement("button");
        kill.id = "kill";
        kill.style.left = "5px";
        let resize  = document.createElement("button");
        resize.id = "resize";
        resize.style.left = "10px";
        let fullScreen  = document.createElement("button");
        fullScreen.id = "fullScreen";
        fullScreen.style.left = "15px";
        let link  = document.createElement("div");
        link.id = "link";
        link.style.textAlignLast = "center";
        let Schermo  = document.createElement("iframe");
        Schermo.id = "Schermo";
        Schermo.src = "https://www.ismycomputeronfire.com/";

        Struttura.appendChild(Testa);
        Testa.appendChild(Pulsanti);
        Pulsanti.appendChild(kill);
        Pulsanti.appendChild(resize);
        Pulsanti.appendChild(fullScreen);
        Testa.appendChild(link);
        Struttura.appendChild(Schermo);



        this.Struttura = Struttura;
        this.Testa = Testa;
        this.Pulsanti = Pulsanti;
        this.kill = kill;
        this.resize = resize;
        this.fullScreen = fullScreen;
        this.link = link;
        this.Schermo = Schermo;

        

        this.kill.onclick = function(){
            this.parentNode.parentNode.parentNode.remove();
            return null;
        }

        this.Struttura.onmousedown = function(){
            this.style.zIndex = z;
            z++;
        }

        this.Testa.onmousedown = function(){
            var cursore;
            var offset = [0,0];
            var ogg;
            var ogg1;
            var click = false;
            ogg1 = this.parentNode;
            ogg1.style.zIndex = z;
            z++;
            this.addEventListener('mousedown', function(e) {
                click = true;
                offset = [ogg1.offsetLeft - e.clientX, ogg1.offsetTop - e.clientY];
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
                ogg1.style.left = (cursore.x + offset[0]) + 'px';
                ogg1.style.top  = (cursore.y + offset[1]) + 'px';
            }
            }, true);
        };

        this.fullScreen.onclick = function(){
            this.parentNode.parentNode.parentNode.style.width = "100%";
            this.parentNode.parentNode.parentNode.style.height = "100%";
            this.parentNode.parentNode.parentNode.style.left = "0%";
            this.parentNode.parentNode.parentNode.style.top = "0%";
            this.parentNode.parentNode.parentNode.style.bottom = "0%";
            this.parentNode.parentNode.parentNode.style.right = "0%";
       }

       this.resize.onclick = function(){
            this.parentNode.parentNode.parentNode.style.width = "40%";
            this.parentNode.parentNode.parentNode.style.height = "40%";
            this.parentNode.parentNode.parentNode.style.left = "50%";
            this.parentNode.parentNode.parentNode.style.bottom = "50%";
       }

        document.body.appendChild(this.Struttura);
    }

};