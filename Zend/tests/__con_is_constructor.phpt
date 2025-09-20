--TEST--
Test that __con is treated as a constructor
--FILE--
<?php
class MyClass {
	public function __con() {
		echo "Constructor called\n";
	}
}

$obj = new MyClass;
?>
--EXPECT--
Constructor called
