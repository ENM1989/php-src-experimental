<?php
$array = range(0, 1000000);
$start = microtime(true);
$flipped = array_flip($array);
$end = microtime(true);
echo "Execution time: " . ($end - $start) . " seconds\n";
?>
