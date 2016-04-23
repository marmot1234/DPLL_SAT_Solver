#pragma once

#include<iostream>
#include<string>
#include<vector>
#include <algorithm>

extern "C" {
	#include"blif_common.h"
	#include"cubical_function_representation.h"
}

using namespace std;

enum literal_type { LITERAL0, LITERAL1, LITERALX };

class clause {
	friend class CNF_function;
	friend class logic_circuit;
private:
	vector<literal_type> literals;
	bool is_DC;
public:
	clause() {}
	clause(t_blif_cube* c, int input_count);
	~clause();
	literal_type int_2_literal(int i);
	//int read_variable();
	//void write_variable();
	void print();
};

//enum signal_type { SIGNAL_LOCAL = 0, SIGNAL_EXTERNAL_IN, SIGNAL_EXTERNAL_OUT, SIGNAL_LOCAL_OTHER };

class CNF_variable {
	friend class clause;
	friend class CNF_function;
	friend class logic_circuit;
private:
	string name;
	int index;
	int occurance = 0;
	bool curr_valuation = true;	// current valuation of the variable, default is true
	t_signal_type type;
public:
	CNF_variable() {}
	CNF_variable(t_blif_signal *s, string n);
	~CNF_variable();
};

class CNF_function {
	friend class logic_circuit;
private:
	vector<CNF_variable*> inputs;	/* List of input variables */
	vector<CNF_variable*> sorted_variables;	//sorted based on occurance, from high to low

	CNF_variable* output;	/* Logic function output */

	vector<clause*> set_of_clauses; /* Set of clauses */

	int value;	/* If there are no clause then this stores the constant value the function evaluates to. Otherwise, should be < 0 */
public:
	CNF_function();
	CNF_function(char * filename);
	~CNF_function();
	void sort_occurance();
	void print();
	void DPLL_init();
	void DPLL_recursively(int curr_var_ind);
};