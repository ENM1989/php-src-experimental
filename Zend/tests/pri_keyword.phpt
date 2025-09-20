--TEST--
Test "pri" as a short form for "private"
--FILE--
<?php
class MyClass {
    pri $property = 'Hello';
    pri function myFunction() {
        echo "This is a private method.";
    }
}

$instance = new MyClass();
try {
    echo $instance->property;
} catch (Error $e) {
    echo $e->getMessage(), "\n";
}

try {
    $instance->myFunction();
} catch (Error $e) {
    echo $e->getMessage(), "\n";
}
?>
--EXPECTF--
Cannot access private property MyClass::$property
Call to private method MyClass::myFunction() from context ''
