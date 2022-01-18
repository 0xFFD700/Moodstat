<?php

// Filters out GET requests
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
	
    // Mood parameter
    $mood = $_GET["mood"];
    $ids = $_GET["ids"];

    // Validate SessionId
    if ($ids == 75982475702) {

        //Get date
        date_default_timezone_set('Europe/Berlin');
        $Date = date("Y-m-d");
        $Time = date("h:i");
        $File = date("Y").".csv";

        //Validate Userinput
        if ($mood === "0" || $mood === "1" || $mood === "2") {

            //Date,Time,Mood
            $stringData = $Date.",".$Time.",".$mood.PHP_EOL;

            //Append to File
            $fp = fopen($File, 'a') or die("can't open file");
            fwrite($fp, $stringData);  
            fclose($fp);  

        } else {

            echo "Wrong Input";
        }
    }
}

?>
