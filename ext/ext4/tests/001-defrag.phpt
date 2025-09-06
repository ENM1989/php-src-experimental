--TEST--
ext4_defrag() function
--FILE--
<?php
// This test expects false because the test environment is not running on ext4.
// The function correctly reports that it cannot defragment the file.
$file = tempnam(sys_get_temp_dir(), 'defrag_test');
file_put_contents($file, 'test data');
var_dump(ext4_defrag($file));
unlink($file);
?>
--EXPECT--
bool(false)
