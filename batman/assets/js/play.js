
var audio = new Audio();
audio.src = "assets/audio/batman.mp3";
function PlaySound()
{
    audio.play();
}

var SpeechRecognition = window.SpeechRecognition || webkitSpeechRecognition;
var SpeechGrammarList = window.SpeechGrammarList || webkitSpeechGrammarList;
var SpeechRecognitionEvent = window.SpeechRecognitionEvent || webkitSpeechRecognitionEvent;

var recognition = new webkitSpeechRecognition();
recognition.lang = 'it-IT';
recognition.continuous = true;

var output = document.getElementById('output');
recognition.onresult = function(event) 
{
  output.textContent = event.results[0][0].transcript;
};
