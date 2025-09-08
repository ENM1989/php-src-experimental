--TEST--
test1() Basic test
--EXTENSIONS--
elephant
--FILE--
<?php
$ret = test1();

var_dump($ret);
?>
--EXPECT--
The extension elephant is loaded and working!
NULL
