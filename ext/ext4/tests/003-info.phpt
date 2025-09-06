--TEST--
ext4_info() function
--FILE--
<?php
$mount_output = shell_exec('mount');
$lines = explode("\n", $mount_output);
$root_device = '';
foreach ($lines as $line) {
    if (strpos($line, ' on / ') !== false) {
        $parts = explode(' ', $line);
        $root_device = $parts[0];
        break;
    }
}

if ($root_device) {
    $info = ext4_info($root_device);
    var_dump(is_array($info));
} else {
    echo "Could not find root device.\n";
}
?>
--EXPECT--
bool(true)
