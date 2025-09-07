--TEST--
head() function basic test
--FILE--
<?php
$filename = __DIR__ . '/test.txt';
file_put_contents($filename, "line1\nline2\nline3\nline4\nline5\nline6\nline7\nline8\nline9\nline10\nline11\nline12");

var_dump(head($filename));
var_dump(head($filename, 5));

unlink($filename);
?>
--EXPECT--
array(10) {
  [0]=>
  string(6) "line1
"
  [1]=>
  string(6) "line2
"
  [2]=>
  string(6) "line3
"
  [3]=>
  string(6) "line4
"
  [4]=>
  string(6) "line5
"
  [5]=>
  string(6) "line6
"
  [6]=>
  string(6) "line7
"
  [7]=>
  string(6) "line8
"
  [8]=>
  string(6) "line9
"
  [9]=>
  string(7) "line10
"
}
array(5) {
  [0]=>
  string(6) "line1
"
  [1]=>
  string(6) "line2
"
  [2]=>
  string(6) "line3
"
  [3]=>
  string(6) "line4
"
  [4]=>
  string(6) "line5
"
}
