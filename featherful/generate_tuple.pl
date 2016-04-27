#!/usr/bin/env perl
use strict;
use warnings;

use feature 'say';


my $count = shift // die "maximum number of arguments required";

my %names = (
	1 => 'first',
	2 => 'second',
	3 => 'third',
	4 => 'fourth',
);

sub tuple_template {
	my ($count, $default) = @_;
	return join '', "template <", (join ', ', map "typename T$_", 1 .. $count - $default), ">";
}

sub tuple_class_name {
	my ($count, $default) = @_;
	return join '', "tuple<", (join ', ', (map "T$_", 1 .. $count - $default), (map 'void', 1 .. $default)), ">";
}

sub tuple_arg_array {
	my ($count, $default) = @_;
	return join ', ', (map "T$_ v$_", 1 .. $count - $default);
}

foreach my $default (0 .. $count - 1) {
	my $template_name = tuple_template($count, $default);
	my $class_name = tuple_class_name($count, $default);
	my $arg_array = tuple_arg_array($count, $default);
	if ($default == 0) {
		say "template <", (join ', ', map "typename T$_=void", 1 .. $count - $default), ">
class tuple";
	} else {
		say "$template_name";
		say "class $class_name";
	}
	say "{\npublic:";
	say "\ttuple($arg_array);";
	say "";

	foreach (1 .. $count - $default) {
		if (exists $names{$_}) {
			say "\tT$_ $names{$_}() const;";
		}
	}
	say "";

	foreach (1 .. $count - $default) {
		my $n = $_ - 1;
		say "\tT$_ arg$n() const;";
	}
	say "";

	say "private:\n";
	
	foreach (1 .. $count - $default) {
		say "\tconst T$_ v$_;";
	}

	say "\n};\n";

	say "$template_name\n${class_name}::tuple($arg_array)";
	say ": ", join ', ', map "v$_(v$_)", 1 .. $count - $default;
	say "{}\n";


	foreach (1 .. $count - $default) {
		if (exists $names{$_}) {
			say "$template_name\nT$_ ${class_name}::$names{$_}() const";
			say "{\n\treturn this->v$_;\n}";
		}
	}

	foreach (1 .. $count - $default) {
		my $n = $_ - 1;
		say "$template_name\nT$_ ${class_name}::arg$n() const";
		say "{\n\treturn this->v$_;\n}";
	}

	say "\n\n\n";
}


