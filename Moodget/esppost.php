<?php

// Mood parameter
$Mood=$_POST["mood"];

//Print fata
$Write="<p> Mood: " + $Mood + "</p>";

//create html website
file_put_contents('sensor1.html', $Write);

?>