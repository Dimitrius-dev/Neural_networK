
#include <iostream>
#include <math.h>
#include <string>
//#include "add_func.cpp"


using namespace std;

//---------------------------------------------------------------------
//функции
void hello(int* ner_input_layer, int* n_hidd_layer, int* ner_hidd_layer, int* ner_out_layer, bool* a, double* b, int* training_number,int *number_of_examples);
void wr_from_script(double* p, int n, string name_input);
void tr_fl(string n, bool* a);
void zero_1(double* p, int n);
void zero_2(double** p, int m, int n);
void random_1(double* p, int n);
void random_2(double** p, int m, int n);
void show_result(double* a,double *error, int n, int i1,bool ts);
void show(double* p, int n);
void wr_weights(double* p, int n, string name_1);
void wr_to_weights(double* a, string name_weights);
void one_side_way(int* ner_hidd_layer, int* ner_input_layer, int* n_hidd_layer, int* ner_out_layer, double** ner_n_hidd, double* ner_inp, double* ner_out, double* weight_input, double* weight_n_hidd, double* weight_output, long  int* I1, long  int* I2, long  int* I3);

double sigmoid(double x);
//---------------------------------------------------------------------

string name = "E:/files/c++/neiros/build-image-Desktop_Qt_5_15_1_MinGW_32_bit-Debug/photo.txt";
string name_ad1 = "weights_1.txt";
string name_ad2 = "weights_2.txt";


//нужна библиотека
//3 нейрона 3 скрытых слоя с 3 нейронами и двумя выходами



int main() {
	//доп переменные
	long int *I1 = new long int{}, *I2 = new long int{}, *I3 = new long int{};//для входа средней и выхода
	bool* training = new bool{};
	int* training_number = new int{}; //training_number == number_of_examples?
	int* number_of_examples = new int{};
	long int T1{}, T1_1{};//для поседовательного считавания нужной части результатов
	bool ts{true};//делает так, чтобы в втором главном вложенном массиве четко T1 переходило до номера считвания следующих элементов(неактуально)

	//количества элементов массивов
	int* ner_input_layer = new int{}, *n_hidd_layer = new int{}, *ner_hidd_layer = new int{}, *ner_out_layer = new int{};
	double* normal_training = new double{};
	
	hello(ner_input_layer, n_hidd_layer, ner_hidd_layer, ner_out_layer, training, normal_training, training_number,number_of_examples);

	//массивы нейронов
	double* ner_inp = new double[*ner_input_layer], * ner_out = new double[*ner_out_layer];
	double** ner_n_hidd = new double*[*ner_hidd_layer ];
	for (int i{}; i < * ner_hidd_layer; i++) {
		ner_n_hidd[i] = new double[*n_hidd_layer];
	}

	double* result = new double[(*ner_out_layer)*(*number_of_examples)];

	//--------------------------------------------------------
	//массивы весов
	double* weight_input = new double[(*ner_input_layer) * (*ner_hidd_layer)], * weight_output = new double[(*ner_hidd_layer)*(*ner_out_layer)];
	double* weight_n_hidd = new double [(*ner_hidd_layer) * (*ner_hidd_layer) * ((*n_hidd_layer)-1) ];
	/*
	for (int i{}; i < ((*n_hidd_layer)-1); i++) {
		weight_n_hidd[i] = new double[(*ner_hidd_layer)* (*ner_hidd_layer)];
	}
	*/
	//массивы весов поправок - delta
	//	double* delta_weight_n_hidd = new double[1];
	//ошибки каждого нейрона
		double* error_ner_inp = new double[*ner_input_layer], * error_ner_out = new double[*ner_out_layer];
		double** error_ner_n_hidd = new double*[*ner_hidd_layer];
		for (int i{}; i < *ner_hidd_layer; i++) {
			error_ner_n_hidd[i] = new double[*n_hidd_layer];
		}
	//	for (int i{}; i <  * ner_hidd_layer; i++) {
	//	error_ner_n_hidd[i] = new double[*n_hidd_layer];
	//}

		zero_1(ner_out, *ner_out_layer);
		zero_2(ner_n_hidd, *ner_hidd_layer, *n_hidd_layer);//обнуление выхода, входа, и средней части

		zero_1(error_ner_inp, *ner_input_layer);
		zero_1(error_ner_out, *ner_out_layer);
		zero_2(error_ner_n_hidd, *ner_hidd_layer, *n_hidd_layer);
	
		random_1(weight_input, (*ner_input_layer) * (*ner_hidd_layer));//первые значения весов
		random_1(weight_output, (*ner_hidd_layer) * (*ner_out_layer));
		random_1(weight_n_hidd, (*ner_hidd_layer) * (*ner_hidd_layer) * ((*n_hidd_layer) - 1));
	//--------------------------------------------------------
	if (*training) {
		
		wr_from_script(ner_inp, *ner_input_layer,"photo_massive_0.txt");

		//show(ner_inp, *ner_input_layer);


		wr_from_script(result, (*ner_out_layer) * (*number_of_examples), "results.txt");
		//show(result, (*ner_out_layer) * (*number_of_examples)); 
		for (int i_i{}; i_i < *number_of_examples; i_i++) {

			switch (i_i) {
				// case 0 уже есть до начала цикла
				case 1:
					wr_from_script(ner_inp, *ner_input_layer, "photo_massive_1.txt");
					break;
				case 2:
					wr_from_script(ner_inp, *ner_input_layer, "photo_massive_2.txt");
					break;
				case 3:
					wr_from_script(ner_inp, *ner_input_layer, "photo_massive_3.txt");
					break;
				case 4:
					wr_from_script(ner_inp, *ner_input_layer, "photo_massive_4.txt");
					break;
				case 5:
					wr_from_script(ner_inp, *ner_input_layer, "photo_massive_5.txt");
					break;
				case 6:
					wr_from_script(ner_inp, *ner_input_layer, "photo_massive_6.txt");
					break;
				case 7:
					wr_from_script(ner_inp, *ner_input_layer, "photo_massive_7.txt");
					break;
				case 8:
					wr_from_script(ner_inp, *ner_input_layer, "photo_massive_8.txt");
					break;
				case 9:
					wr_from_script(ner_inp, *ner_input_layer, "photo_massive_9.txt");
					break;
			}

			for (int i{}; i < *training_number; i++) {

				//----------------------------------------------------------------------------------------------------
				//прямой проход

				/*
				for (int i1{}; i1 < *ner_hidd_layer; i1++) {//вход
					for (int j1{}; j1 < *ner_input_layer; j1++) {
						ner_n_hidd[i1][0] += (ner_inp[j1] * weight_input[I1]);// cout << weight_input[I1]<<'\n';
						I1++;
					}
					ner_n_hidd[i1][0] = sigmoid(ner_n_hidd[i1][0]);// cout << ner_n_hidd[i1][0] << '\n';
				}

				//cout << '\n';

				for (int i1{ 1 }; i1 < *n_hidd_layer; i1++) {//среднее //(int i1{ 1 }; i1 <= *n_hidd_layer; i1++)
					for (int j1{}; j1 < *ner_hidd_layer; j1++) {
						for (int k1{}; k1 < *ner_hidd_layer; k1++) {
							ner_n_hidd[j1][i1] += (ner_n_hidd[k1][i1 - 1] * weight_n_hidd[I2]); //cout << weight_n_hidd[I2] << '\n';
							I2++;
						}
						ner_n_hidd[j1][i1] = sigmoid(ner_n_hidd[j1][i1]); //cout << ner_n_hidd[j1][i1] << '\n';
					}
				}

				//cout << '\n';

				for (int i1{}; i1 < *ner_out_layer; i1++) {//выход
					for (int j1{}; j1 < *ner_hidd_layer; j1++) {
						ner_out[i1] += (ner_n_hidd[j1][(*n_hidd_layer) - 1] * weight_output[I3]); ///cout << weight_output[I3] << '\n'; 
						I3++;
					}
					ner_out[i1] = sigmoid(ner_out[i1]);// cout << ner_out[i1] << '\n';
				}

				*/

				one_side_way(ner_hidd_layer, ner_input_layer, n_hidd_layer, ner_out_layer, ner_n_hidd, ner_inp, ner_out, weight_input, weight_n_hidd, weight_output, I1, I2, I3);
				//----------------------------------------------------------------------------------------------------
				//обратный проход( вычисление ошибки)
				
				//могут быть ошибки в коде ниже<><><><><><><><><><><><><><><>
				
				for (int i1{}; i1 < (*ner_out_layer); i1++) {
					error_ner_out[i1] = (result[i1+T1] - ner_out[i1])*(ner_out[i1])*(1- ner_out[i1]);
					//cout << T1 << '\n';
				}
			
				show_result(ner_out, error_ner_out, *ner_out_layer, i,true);
				
				
				

				
				//распространение ошибки
				for (int i1{ (*ner_out_layer)-1 }; i1 >= 0 ; i1--) {//выход
					for (int j1{(*ner_hidd_layer)-1}; j1 >=0 ; j1--) {
						*I3 = *I3-1;
						error_ner_n_hidd[j1][*n_hidd_layer-1] += error_ner_out[i1] * weight_output[*I3] * (ner_n_hidd[j1][ (*n_hidd_layer) - 1])*(1 - (ner_n_hidd[j1][ (*n_hidd_layer) - 1]) );
					}
					//ner_out[i1] = sigmoid(ner_out[i1]);
				}
				
				for (int i1{ *n_hidd_layer - 1 }; i1 >= 1; i1--) {//среднее
					for (int j1{ *ner_hidd_layer - 1}; j1 >=0 ; j1--) {
						for (int k1{ *ner_hidd_layer - 1}; k1 >= 0; k1--) {
							*I2 = *I2 - 1;
							error_ner_n_hidd[k1][i1 - 1] += error_ner_n_hidd[j1][i1] * weight_n_hidd[*I2] * (ner_n_hidd[k1][i1 - 1])*(1 - (ner_n_hidd[k1][i1 - 1]) );//ner_n_hidd[j1][i1] += (ner_n_hidd[k1][i1 - 1] * weight_n_hidd[I2]); I2++;
						}
						//ner_n_hidd[j1][i1] = sigmoid(ner_n_hidd[j1][i1]);
					}
				}
				*I1 = 0; *I2 = 0; *I3 = 0;
				//cout << "I1 = " << I1 << '\n';
				//cout << "I2 = " << I2 << '\n';
				//cout << "I3 = " << I3 << '\n';
				
				//-----------------------------------------------
				//изменение значений весов
				for (int i1{}; i1 < *ner_hidd_layer; i1++) {//вход
					for (int j1{}; j1 < *ner_input_layer; j1++) {
						weight_input[*I1] += ner_inp[j1] * error_ner_n_hidd[i1][0] * (*normal_training); *I1 = *I1 + 1;; //ner_n_hidd[i1][0] += (ner_inp[j1] * weight_input[I1]); I1++;
					}
					//ner_n_hidd[i1][0] = sigmoid(ner_n_hidd[i1][0]);
				}

				for (int i1{ 1 }; i1 < *n_hidd_layer; i1++) {//среднее //(int i1{ 1 }; i1 <= *n_hidd_layer; i1++)
					for (int j1{}; j1 < *ner_hidd_layer; j1++) {
						for (int k1{}; k1 < *ner_hidd_layer; k1++) {
							weight_n_hidd[*I2] += ner_n_hidd[k1][i1 - 1] * error_ner_n_hidd[j1][i1] * (*normal_training); *I2 = *I2 + 1;;//ner_n_hidd[j1][i1] += (ner_n_hidd[k1][i1 - 1] * weight_n_hidd[I2]); I2++;
						}
						//ner_n_hidd[j1][i1] = sigmoid(ner_n_hidd[j1][i1]);
					}
				}

				for (int i1{}; i1 < *ner_out_layer; i1++) {//выход
					for (int j1{}; j1 < *ner_hidd_layer; j1++) {
						weight_output[*I3] += ner_n_hidd[j1][(*n_hidd_layer) - 1] * error_ner_out[i1] * (*normal_training); *I3 = *I3 + 1;;
					}
					//ner_out[i1] = sigmoid(ner_out[i1]);
				}
				
				
				//-----------------------------------------------
				zero_1(error_ner_inp, *ner_input_layer);
				//zero_1(error_ner_out, *ner_out_layer);
				zero_2(error_ner_n_hidd, *ner_hidd_layer, *n_hidd_layer);

				zero_1(ner_out, *ner_out_layer);
				zero_2(ner_n_hidd, *ner_hidd_layer, *n_hidd_layer);

				*I1 = 0; *I2 = 0; *I3 = 0;
			}
			
			cout << "==================================================================================\n";
			cout << "==================================================================================\n";
			cout << "==================================================================================\n";
			T1 += (*ner_out_layer);

		}

		wr_weights(weight_input, (*ner_input_layer)* (*ner_hidd_layer),"weights_1.txt");
		wr_weights(weight_n_hidd, (*ner_hidd_layer)* (*ner_hidd_layer)* ((*n_hidd_layer) - 1),"weights_2.txt");
		wr_weights(weight_output, (*ner_hidd_layer)*(*ner_out_layer),"weights_3.txt");

		cout << "-----------------------------------------------------------------------\n";
		cout << "updated weights saved in txt files: weights_1.txt  weights_2.txt  weights_3.txt\n";
		cout << "-----------------------------------------------------------------------\n";

	}
	else {
		//готовая - проверка


		wr_from_script(ner_inp, *ner_input_layer, "photo_massive_test.txt");
		
		wr_to_weights(weight_input, "weights_1.txt");
		wr_to_weights(weight_n_hidd, "weights_2.txt");
		wr_to_weights(weight_output, "weights_3.txt");

		one_side_way(ner_hidd_layer, ner_input_layer, n_hidd_layer, ner_out_layer, ner_n_hidd, ner_inp, ner_out, weight_input, weight_n_hidd, weight_output, I1, I2, I3);




		show_result(ner_out, error_ner_out, *ner_out_layer, 0,false);

	}

	
	system("pause");
	return 0;
}

