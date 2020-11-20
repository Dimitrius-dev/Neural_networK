#include <string>
#include <math.h>
#include <fstream>
#include <iostream>

using namespace std;

void show_result(double* a,double *error,int n, int i1, bool ts) {//i1 счётчик
	double mx{}; int *i_mx = new int{};
	cout << "---------------------------------------------\n";
	cout << "out number = " << i1 + 1 << '\n';
	if (ts) {
		for (int i{}; i < n; i++) {
			cout << "\tresult output neuron nam." << i + 1 << " = " << a[i] << "\terror = " << error[i] << '\n';
		}
	}
	else{
		for (int i{}; i < n; i++) {
			cout << "\tresult output neuron nam." << i + 1 <<" number"<< i << " = " << a[i] << '\n';
		}

		for (int i{}; i < n; i++) {
			if (a[i] > mx) { mx = a[i]; *i_mx = i; }
		}

		cout << "\nmachine think that this number is =  " << *i_mx << '\n';
	}

	//нахождение максимального

	
}



void zero_1(double* p, int n) {
	for (int i{}; i < n; i++) { p[i] = 0; }
}

void zero_2(double** p, int m, int n) {
	for (int i{}; i < m; i++) {
		for (int j{}; j < n; j++) {
			p[i][j] = 0.;
		}
	}
}

void random_1(double* p, int n) {
	for (int i{}; i < n; i++) {
		p[i] = ((rand() % 10) / 10.) - 0.5;
	}
}

void random_2(double** p, int m, int n) {
	for (int i{}; i < m; i++) {
		for (int j{}; j < n; j++) {
			p[i][j] = ((rand() % 10) / 10.) - 0.5;
		}
	}
}

void show(double* p, int n){
	for (int i{}; i < n; i++) {
		cout << p[i] << '\n';
	}
}

void show_db_2(double** p, int m, int n) {
	for (int i{}; i < m; i++) {
		for (int j{}; j < n; j++) {
			cout<<p[j][i] << '\n';
		}
	}
}

double sigmoid(double x) {
	return (1 / (1 + exp(-x)));
}

void wr_from_script(double *p, int n, string name_input) {
	ifstream output; int I{0}; char buf{};
	output.open(name_input);
	if (output.is_open()) {
		while (output.get(buf)) {
			if (I == n) { break; }
			if (buf == '\n') { continue; }
			p[I] = (int)buf - 48; I++;
		}
	}
	else { cout << "\nERROR OPEN FILE\n"; }
	output.close();
}


void wr_to_weights(double* a, string name_weights) {
	ifstream in_wh; long int I{}; string buffer{};
	in_wh.open(name_weights);
	if (in_wh.is_open()) {
		while (!in_wh.eof()) {
			in_wh >> buffer;
			a[I] = atof(buffer.c_str()); I++;
		}
	}
	else { cout << "\nERROR OPEN FILE\n"; }
	in_wh.close();
}



void wr_weights(double* p, int n, string name_1) {
	ofstream file; char buf{};
	file.open(name_1);
	if (file.is_open()) {
		for (int i{}; i < n; i++) {
			file << p[i] << '\n';
		}
	}
	else { cout << "\nERROR OPEN FILE\n"; }
	file.close();
}

void tr_fl(string n, bool *a) {
	if ((n == "Yes") || (n == "yes") || (n == "YES") || (n == "y") || (n == "Y")) { *a = true; }
	if ((n == "No") || (n == "no") || (n == "NO") || (n == "n") || (n == "N")) { *a = false; }
}

void one_side_way(int* ner_hidd_layer, int *ner_input_layer, int* n_hidd_layer , int* ner_out_layer ,double **ner_n_hidd, double * ner_inp,double *ner_out, double *weight_input, double *weight_n_hidd, double *weight_output,long int * I1, long int * I2, long int *I3 ){
	for (int i1{}; i1 < *ner_hidd_layer; i1++) {//вход
	for (int j1{}; j1 < *ner_input_layer; j1++) {
		ner_n_hidd[i1][0] += (ner_inp[j1] * weight_input[*I1]);// cout << weight_input[I1]<<'\n';
		*I1 = *I1 + 1;
	}
	ner_n_hidd[i1][0] = sigmoid(ner_n_hidd[i1][0]);// cout << ner_n_hidd[i1][0] << '\n';
}

//cout << '\n';

	for (int i1{ 1 }; i1 < *n_hidd_layer; i1++) {//среднее //(int i1{ 1 }; i1 <= *n_hidd_layer; i1++)
	for (int j1{}; j1 < *ner_hidd_layer; j1++) {
		for (int k1{}; k1 < *ner_hidd_layer; k1++) {
			ner_n_hidd[j1][i1] += (ner_n_hidd[k1][i1 - 1] * weight_n_hidd[*I2]); //cout << weight_n_hidd[I2] << '\n';
			*I2 = * I2 + 1;
		}
		ner_n_hidd[j1][i1] = sigmoid(ner_n_hidd[j1][i1]); //cout << ner_n_hidd[j1][i1] << '\n';
	}
}

//cout << '\n';

	for (int i1{}; i1 < *ner_out_layer; i1++) {//выход
	for (int j1{}; j1 < *ner_hidd_layer; j1++) {
		ner_out[i1] += (ner_n_hidd[j1][(*n_hidd_layer) - 1] * weight_output[*I3]); ///cout << weight_output[I3] << '\n'; 
		*I3 = *I3 + 1;
	}
	ner_out[i1] = sigmoid(ner_out[i1]);// cout << ner_out[i1] << '\n';
}

}



void hello(int *ner_input_layer, int *n_hidd_layer, int* ner_hidd_layer, int *ner_out_layer,bool *a,double *b,int *training_number,int *number_of_examples) {
	string tr = "";
	cout << "--------------------------------------------------------------------\n";
	cout << "-----------------------------H-E-L-L-O------------------------------\n";
	cout << "--------------------------------------------------------------------\n";
	cout << "---------------------This-is-neuronet-by-Dmitrii-B.-----------------\n";
	cout << "--------------------------------------------------------------------\n";
	cout << "-----------------------------version-1.1----------------------------\n";
	cout << "--------------------------------------------------------------------\n";
	cout << "--------------------------------------------------------------------\n";

	cout << "Enter n  neurons of input_layer = "; cin >> *ner_input_layer;
	cout << "Enter n for hidden_layers = "; cin >> *n_hidd_layer;
	cout << "Enter n neurons of hidden_layer = "; cin >> *ner_hidd_layer;
	cout << "Enter n neurons of output_layer = "; cin >> *ner_out_layer;
	cout << "Enter mode(yes/no) = "; cin >> tr; tr_fl(tr,a);
	if (*a == true) {
		cout << "==============================================================\n";
		cout << "   Enter normal training(0.0 - 1.0) = "; cin >> *b;
		cout << "   Enter number of training = "; cin >> *training_number;
		cout << "   Enter number of examples = "; cin >> *number_of_examples;
	}
}
