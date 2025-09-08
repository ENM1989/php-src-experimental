--TEST--
Check if elephant is loaded
--EXTENSIONS--
elephant
--FILE--
<?php
echo 'The extension "elephant" is available';
?>
--EXPECT--
The extension "elephant" is available
