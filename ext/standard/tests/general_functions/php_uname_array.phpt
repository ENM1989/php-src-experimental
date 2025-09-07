--TEST--
Test php_uname() function - array return
--SKIPIF--
<?php if (!function_exists("php_uname")) print "skip"; ?>
--FILE--
<?php
echo "*** Testing php_uname() - array return\n";
$uname_array = php_uname('A');
var_dump(is_array($uname_array));
var_dump(array_key_exists('sysname', $uname_array));
var_dump(array_key_exists('nodename', $uname_array));
var_dump(array_key_exists('release', $uname_array));
var_dump(array_key_exists('version', $uname_array));
var_dump(array_key_exists('machine', $uname_array));
?>
--EXPECT--
*** Testing php_uname() - array return
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
