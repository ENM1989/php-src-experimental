--TEST--
Test that __des is treated as a destructor
--FILE--
<?php
class MyClass {
	public function __des() {
		echo "Destructor called\n";
	}
}

$obj = new MyClass;
unset($obj);
?>
--EXPECT--
Destructor called
