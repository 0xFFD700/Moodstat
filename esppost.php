<?php

//if ($_SERVER['REQUEST_METHOD'] === 'POST') {
	
// Mood parameter
$mood = $_GET["mood"];
//$ids = $_GET["ids"];

// Validate SessionId
//if (strcmp($ids, "75982475702")) {

//Get date
date_default_timezone_set('Europe/Berlin');
$Date = date("Y-m-d");
$Time = date("h:i");
$Space = ";";

//Validate Userinput
if (strcmp($mood, "0") || strcmp($mood, "1") || strcmp($mood, "2"))
{

//Print fata
//Date;Time;Mood
$stringData = $Date.$Space.$Time.$Space.$mood.$Space.PHP_EOL;


//Append to File
$fp = fopen('moodstat.csv', 'a') or die("can't open file");
fwrite($fp, $stringData);  
fclose($fp);  

} else {
    echo "Wrong Input";
}

//}} 

?>
