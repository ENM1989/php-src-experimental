--TEST--
Test for invalid date exception
--FILE--
<?php
try {
    new DateTime('2023-02-30');
} catch (Exception $e) {
    echo $e->getMessage();
}
?>
--EXPECT--
Failed to parse time string (2023-02-30) at position 0 (2): The parsed date was invalid
