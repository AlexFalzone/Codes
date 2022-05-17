var x; 
console.log("x = " + x);
console.log(navigator);

function neofetch()
{
    console.log("neofetch");
    document.getElementById("figlio").value = navigator.userAgent;
    // document.getElementById("figlio").value = navigator.appVersion;
}

function calcolatrice(equazione)
{
    console.log("calcolatrice");
    console.log("equazione = " + equazione);
    return equazione;
}


function enterKeyPressed(event)
{
    if(event.keyCode == 13)
    {
        console.log("Enter key pressed");
        x = document.getElementById("figlio").value;

        if(x == " neofetch")
        {
            console.log("x = " + x);
            neofetch();
        }
        else
        {
            console.log("x = " + x);
            calcolatrice(x);
            console.log("Calcolatrice = " + calcolatrice(x));
        }
    }
}