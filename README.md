# Reflectable #

A C++11 header only library built from code stolen from around the internet to allow compile-time reflection.

This whole thing is build on std::tuple.

### Much Thanks ###

Much thanks to the template wizards who really wrote this code. All I did was steal their code and glue it together :)

[Iterating through a std::tuple](http://stackoverflow.com/a/6894436 "Iterating through a std::tuple")

[Tagged tuples (The real heart and soul)](http://stackoverflow.com/a/13066078 "Tagged tuples (The real heart and soul)")

### Limitations ###

Member variable names use structs as tags for the compiler. This means that no other symbols can conflict with the variable names in your reflectable objects, which sucks. You can, however, reuse variable names across multiple reflectable objects.

### Benchmarks ###

Without compiler optimizations
	
	Raw for loop: 0.53s
	Regular access: 0.597s
	Reflectable access: 3.782s
	Reflectable with reference access: 0.559s

With compiler optimizations (-O)

	Raw for loop: 0.084s
	Regular access: 0.086s
	Reflectable access: 0.084s
	Reflectable with reference access: 0.104s

With compiler optimizations (-O1)

	Raw for loop: 0.085s
	Regular access: 0.085s
	Reflectable access: 0.085s
	Reflectable with reference access: 0.104s
