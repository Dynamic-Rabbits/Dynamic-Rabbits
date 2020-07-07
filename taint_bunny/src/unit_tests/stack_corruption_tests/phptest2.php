<?php



// base class with member properties and methods
class Vegetable {

   var $edible;
   var $color;

   function __construct($edible, $color="green")
   {
       $this->edible = $edible;
       $this->color = $color;
   }

   function is_edible()
   {
       return $this->edible;
   }

   function what_color()
   {
       return $this->color;
   }

} // end of class Vegetable

// extends the base class
class Spinach extends Vegetable {

   var $cooked = false;

   function __construct()
   {
       parent::__construct(true, "green");
   }

   function cook_it()
   {
       $this->cooked = true;
   }

   function is_cooked()
   {
       return $this->cooked;
   }

} // end of class Spinach


// utility functions

function print_vars($obj)
{
foreach (get_object_vars($obj) as $prop => $val) {
    echo "\t$prop = $val\n";
}
}

function print_methods($obj)
{
$arr = get_class_methods(get_class($obj));
foreach ($arr as $method) {
    echo "\tfunction $method()\n";
}
}

function class_parentage($obj, $class)
{
if (is_subclass_of($GLOBALS[$obj], $class)) {
    echo "Object $obj belongs to class " . get_class($GLOBALS[$obj]);
    echo ", a subclass of $class\n";
} else {
    echo "Object $obj does not belong to a subclass of $class\n";
}
}

// instantiate 2 objects

$veggie = new Vegetable(true, "blue");
$leafy = new Spinach();

// print out information about objects
echo "veggie: CLASS " . get_class($veggie) . "\n";
echo "leafy: CLASS " . get_class($leafy);
echo ", PARENT " . get_parent_class($leafy) . "\n";

// show veggie properties
echo "\nveggie: Properties\n";
print_vars($veggie);

// and leafy methods
echo "\nleafy: Methods\n";
print_methods($leafy);

echo "\nParentage:\n";
class_parentage("leafy", "Spinach");
class_parentage("leafy", "Vegetable");
?>
