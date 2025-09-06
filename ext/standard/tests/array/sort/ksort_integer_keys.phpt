--TEST--
ksort() with integer keys
--FILE--
<?php
$array = [2 => 'two', 1 => 'one', 0 => 'zero'];
ksort($array);
var_dump($array);

$array = [10 => 'ten', 5 => 'five', 15 => 'fifteen'];
ksort($array);
var_dump($array);

$array = [];
ksort($array);
var_dump($array);

$array = [0 => 'a', 1 => 'b', 2 => 'c'];
ksort($array);
var_dump($array);

$array = [PHP_INT_MAX => 'max', 0 => 'zero', PHP_INT_MIN => 'min'];
ksort($array);
var_dump($array);
?>
--EXPECT--
array(3) {
  [0]=>
  string(4) "zero"
  [1]=>
  string(3) "one"
  [2]=>
  string(3) "two"
}
array(3) {
  [5]=>
  string(4) "five"
  [10]=>
  string(3) "ten"
  [15]=>
  string(7) "fifteen"
}
array(0) {
}
array(3) {
  [0]=>
  string(1) "a"
  [1]=>
  string(1) "b"
  [2]=>
  string(1) "c"
}
array(3) {
  [-9223372036854775808]=>
  string(3) "min"
  [0]=>
  string(4) "zero"
  [9223372036854775807]=>
  string(3) "max"
}
