<?php

function run_benchmark($name, $array, $iterations) {
    $start = microtime(true);
    for ($i = 0; $i < $iterations; $i++) {
        $values = array_values($array);
    }
    $end = microtime(true);
    echo "$name: " . ($end - $start) . " seconds\n";
    // Keep the result to avoid optimization that removes the call
    return $values;
}

$iterations = 1000000;

// 1. Associative array
$associative_array = [];
for ($i = 0; $i < 1000; $i++) {
    $associative_array['key' . $i] = $i;
}

// 2. Packed array with holes
$packed_array_with_holes = [];
for ($i = 0; $i < 1000; $i++) {
    $packed_array_with_holes[$i] = $i;
}
unset($packed_array_with_holes[500]);

// 3. Vector-like packed array
$vector_array = [];
for ($i = 0; $i < 1000; $i++) {
    $vector_array[] = $i;
}

echo "Running array_values() benchmark with $iterations iterations...\n";

$result1 = run_benchmark('Associative Array', $associative_array, $iterations);
$result2 = run_benchmark('Packed Array with Holes', $packed_array_with_holes, $iterations);
$result3 = run_benchmark('Vector-like Packed Array', $vector_array, $iterations);

?>
