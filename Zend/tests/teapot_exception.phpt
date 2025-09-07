--TEST--
TeapotException test
--FILE--
<?php
try {
    throw new TeapotException("I'm a teapot!");
} catch (TeapotException $e) {
    echo $e->getMessage();
}
?>
--EXPECT--
I'm a teapot!
