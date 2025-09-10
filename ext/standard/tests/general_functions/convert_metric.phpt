--TEST--
Test convert_metric() function
--FILE--
<?php
var_dump(convert_metric(1, 'kg', 'g'));
var_dump(convert_metric(1000, 'g', 'kg'));
var_dump(convert_metric(1, 'g', 'mg'));
var_dump(convert_metric(1, 'kg', 'mg'));

var_dump(convert_metric(1, 'km', 'm'));
var_dump(convert_metric(1000, 'm', 'km'));
var_dump(convert_metric(1, 'm', 'cm'));
var_dump(convert_metric(1, 'km', 'cm'));

var_dump(convert_metric(1, 'kl', 'l'));
var_dump(convert_metric(1000, 'l', 'kl'));
var_dump(convert_metric(1, 'l', 'ml'));
var_dump(convert_metric(1, 'kl', 'ml'));

try {
    convert_metric(1, 'foo', 'bar');
} catch (ValueError $e) {
    echo $e->getMessage() . "\n";
}

try {
    convert_metric(1, 'kg', 'bar');
} catch (ValueError $e) {
    echo $e->getMessage() . "\n";
}

try {
    convert_metric(1, 'kg', 'm');
} catch (ValueError $e) {
    echo $e->getMessage() . "\n";
}
?>
--EXPECTF--
float(1000)
float(1)
float(1000)
float(1000000)
float(1000)
float(1)
float(100)
float(100000)
float(1000)
float(1)
float(1000)
float(1000000)
convert_metric(): Argument #2 ($from) is not a valid metric unit
convert_metric(): Argument #3 ($to) is not a valid metric unit
convert_metric(): Argument #2 ($from) and argument #3 ($to) must be of the same metric type (mass, length, or volume)
