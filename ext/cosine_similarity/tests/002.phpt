--TEST--
test1() Basic test
--EXTENSIONS--
cosine_similarity
--FILE--
<?php
$ret = test1();

var_dump($ret);
?>
--EXPECT--
The extension cosine_similarity is loaded and working!
NULL
