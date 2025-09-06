--TEST--
Check if ext4 is loaded
--EXTENSIONS--
ext4
--FILE--
<?php
echo 'The extension "ext4" is available';
?>
--EXPECT--
The extension "ext4" is available
