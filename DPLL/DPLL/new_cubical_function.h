#pragma once

#include<iostream>
#include<string>
#include<vector>

extern "C" {
	#include"blif_common.h"
	#include"cubical_function_representation.h"
}

using namespace std;

enum literal_type { LITERAL0, LITERAL1, LITERALX };

class cube {
	friend class cubical_function;
	friend class logic_circuit;
private:
	vector<literal_type> literals;
	bool is_DC;
public:
	cube() {}
	cube(t_blif_cube* c, int input_count);
	~cube();
	literal_type int_2_literal(int i);
	//int read_variable();
	//void write_variable();
	void print();
};

//enum signal_type { SIGNAL_LOCAL = 0, SIGNAL_EXTERNAL_IN, SIGNAL_EXTERNAL_OUT, SIGNAL_LOCAL_OTHER };

class cubical_signal {
	friend class cube;
	friend class cubical_function;
	friend class logic_circuit;
private:
	string name;
	int index;
	t_signal_type type;
public:
	cubical_signal() {}
	cubical_signal(t_blif_signal *s);
	~cubical_signal();
};

class cubical_function {
	friend class logic_circuit;
private:
	vector<cubical_signal*> inputs;	/* List of input signals */

	cubical_signal* output;	/* Logic function output */

	vector<cube*> set_of_cubes; /* Set of cubes */

	int value;	/* If there are no cubes then this stores the constant value the function evaluates to. Otherwise, should be < 0 */
public:
	cubical_function() {}
	cubical_function(s_blif_cubical_function* f);
	~cubical_function();
	void print();
};

class logic_circuit {
private:
	string name;	/* Circuit name */

	vector<cubical_signal*> primary_inputs;	

	vector<cubical_signal*> primary_outputs;

	vector<cubical_signal*> internal_signals;

public:vector<cubical_function*> list_of_functions;
	logic_circuit() {}
	logic_circuit(char* filename);
	~logic_circuit();
	void read_file(char* filename);
};