var x; 
console.log("x = " + x);
console.log(navigator);

function neofetch()
{
    console.log("neofetch");
    document.getElementById("figlio").value = " " + navigator.platform;
}

function sliceAndConvert(str)
{
    var str1 = str.slice(1,4);
    var str2 = str.slice(5,7);
    var str3 = str.slice(7,8);
    console.log("str1 = " + str1 + ", str2 = " + str2 + ", str3 = " + str3);

    var num1 = Number(str2);
    var num2 = Number(str3);

    console.log("num1 = " + num1 + ", num2 = " + num2);

    switch(str1)
    {
        case "sum":
            num1 += num2;
        break;
        case "sub":
            num1 -= num2;
        break;
        case "mul":
            num1 *= num2;
        break;
        case "div":
            num1 /= num2;
        break;
        default:
            console.log("error");
        break;
    }

    document.getElementById("figlio").value = " "+ num1;
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
        else if(x == " 👋")
        {
            if( navigator.userAgent.includes("Windows"))
            {
                console.log("Windows");
                document.getElementById("figlio").value = " Hello, I am a Windows machine";
            }
            else if( navigator.userAgent.includes("Linux"))
            {
                console.log("Linux");
                document.getElementById("figlio").value = " Hello, I am a Linux machine";
            }
            else if( navigator.userAgent.includes("Mac"))
            {
                console.log("Mac");
                document.getElementById("figlio").value = " Hello, I am a Mac machine";
            }
            else
            {
                console.log("Other");
                document.getElementById("figlio").value = " Hello, I am an unknown machine (probably a BSD system or mobile device)";
            }
        }
        else if(x == " data")
        {
            console.log("📅");
            document.getElementById("figlio").value = " " + new Date();
        }
        else if(x.length >= 8 && x != " bluethoot")
        {
            sliceAndConvert(x);
        }
        else if(x == " ip")
        {
            function text(url) {
                return fetch(url).then(res => res.text());
              }
              
              text('https://www.cloudflare.com/cdn-cgi/trace').then(data => {
                let ipRegex = /[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}/
                let ip = data.match(ipRegex)[0];
                console.log(ip);
                document.getElementById("figlio").value = " " + ip;
              });
        }
        else
        {
            document.getElementById("figlio").value = " Not a valid command";
        }
    }
}