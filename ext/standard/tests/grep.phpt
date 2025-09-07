--TEST--
Test php_grep() function
--FILE--
<?php
$file = tempnam(sys_get_temp_dir(), 'grep_test');
file_put_contents($file, "hello world\nthis is a test\nhello again\n");
$result = php_grep('hello', $file);
var_dump($result);
unlink($file);
?>
--EXPECT--
array(2) {
  [0]=>
  string(12) "hello world
"
  [1]=>
  string(12) "hello again
"
}
