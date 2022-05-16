const x = document.getElementById("demo").value;

document.getElementById("not_editable").readonly = true;

console.log("x = " + x);
console.log(navigator);

function neofetch()
{
    if(x == " neofetch")
    {
        console.log("neofetch");
        document.getElementById("demo").value = navigator.userAgent;
        document.getElementById("demo").value = navigator.appVersion;
    }
}


function enterKeyPressed(event)
{
    if(event.keyCode == 13)
    {
        console.log("Enter key pressed");
        neofetch();
    }
}