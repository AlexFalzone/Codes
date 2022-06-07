function calcolatrice(a, operazione, b)
{
    

    function somma(a,b)
    {
        return a + b;
    }

    var sottrazione = (a,b) =>{
        return a - b;
    }

    function moltiplicazione(a,b)
    {
        return a * b;
    }

    function divisione(a,b)
    {
        return a /  b;
    }

    if( String(operazione) == "+")
    {
        return somma(a,b)
    }
    else if( operazione == "-")
    {
        return sottrazione(a,b)
    }
    else if( operazione == "*")
    {
        return moltiplicazione(a,b)
    }
    else if( operazione == "/")
    {
        return divisione(a,b)
    }
}


function calcolatrice2(equazione)
{
    index_operazione = (equazione.indexOf("+"));
    flag = false
    if (index_operazione == -1)
    {
        index_operazione = equazione.indexOf('-');
        if(index_operazione != -1)
        {
            flag = true;
        }
    }
    if(index_operazione == -1 && flag == false)
    {
        index_operazione = equazione.indexOf('*');
        if(index_operazione != -1)
        {
            flag = true;
        }
    }
    if(index_operazione == -1 && flag == false)
    {
        index_operazione = equazione.indexOf('/');
    }

    operazione = "";
    operazione = equazione[index_operazione];

    a = "";
    for(i = 0; i<index_operazione; i++)
    {
        a+= equazione[i];
    }
    a = parseFloat(a)

    b = "";
    for(i = index_operazione + 1; i<(equazione.length) ; i++)
    {
        b+= equazione[i];
    }
    b =  parseFloat(b)

    function somma(a,b)
    {
        return a + b;
    }

    var sottrazione = (a,b) =>{
        return a - b;
    }

    function moltiplicazione(a,b)
    {
        return a * b;
    }

    function divisione(a,b)
    {
        return a /  b;
    }

    if( String(operazione) == "+")
    {
        return somma(a,b)
    }
    else if( operazione == "-")
    {
        return sottrazione(a,b)
    }
    else if( operazione == "*")
    {
        return moltiplicazione(a,b)
    }
    else if( operazione == "/")
    {
        return divisione(a,b)
    }
}


function calcolatrice3(equazione)
{
    return equazione;
}
