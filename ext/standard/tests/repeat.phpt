--TEST--
Test repeat() function
--FILE--
<?php
echo "Test with positive repetitions:\n";
$a = 0;
repeat(5, function($i) use (&$a) {
    echo "iteration: $i\n";
    $a += $i;
});
echo "Result: $a\n";

echo "\nTest with zero repetitions:\n";
repeat(0, function($i) {
    echo "This should not be printed.\n";
});
echo "Completed zero repetitions.\n";

echo "\nTest with negative repetitions:\n";
repeat(-5, function($i) {
    echo "This should not be printed.\n";
});
echo "Completed negative repetitions.\n";
?>
--EXPECT--
Test with positive repetitions:
iteration: 0
iteration: 1
iteration: 2
iteration: 3
iteration: 4
Result: 10

Test with zero repetitions:
Completed zero repetitions.

Test with negative repetitions:
Completed negative repetitions.
