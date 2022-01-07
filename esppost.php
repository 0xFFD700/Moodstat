<?php

// Mood parameter
$mood = $_GET["mood"];
$Id=$_GET["id"];

//Get date
date_default_timezone_set('Europe/Berlin');
$Date = date("Y-m-d");
$Time = date("h:i");
$Space = ";";

//Print fata
//Date;Time;Mood
$stringData = $Date.$Space.$Time.$Space.$mood.$Space.PHP_EOL;


//Append to File
$fp = fopen('moodstat.csv', 'a') or die("can't open file");
fwrite($fp, $stringData);  
fclose($fp);  

?>
