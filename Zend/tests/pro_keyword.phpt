--TEST--
"pro" as a shorthand for "protected"
--FILE--
<?php
class A {
    pro $pro_prop = 'pro_prop';
    pro const PRO_CONST = 'pro_const';
    pro function pro_method() {
        return 'pro_method';
    }
}

$a = new A;
var_dump($a->pro_method());
var_dump(A::PRO_CONST);
var_dump($a->pro_prop);

?>
--EXPECTF--
string(10) "pro_method"
string(9) "pro_const"

Fatal error: Uncaught Error: Cannot access protected property A::$pro_prop in %s:%d
Stack trace:
#0 {main}
  thrown in %s on line %d
