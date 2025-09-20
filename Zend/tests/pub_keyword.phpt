--TEST--
Test that "pub" is a valid shorthand for "public".
--FILE--
<?php
class MyClass {
    pub $property = 'Hello';
    pub function myMethod() {
        return 'World';
    }
}

$instance = new MyClass();
echo $instance->property . ' ' . $instance->myMethod();
?>
--EXPECT--
Hello World
