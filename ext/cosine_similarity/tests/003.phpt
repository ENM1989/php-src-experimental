--TEST--
test2() Basic test
--EXTENSIONS--
cosine_similarity
--FILE--
<?php
var_dump(test2());
var_dump(test2('PHP'));
?>
--EXPECT--
string(11) "Hello World"
string(9) "Hello PHP"
