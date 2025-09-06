--TEST--
ext4_mount_options() function
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
    $options = ext4_mount_options($root_device);
    var_dump(is_array($options));
} else {
    echo "Could not find root device.\n";
}
?>
--EXPECT--
bool(true)
