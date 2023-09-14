#include<string>
#include<algorithm>
#include<iostream>
#include<fstream>

#include <adios2.h>

template <typename T>
int convert_adios2_var(std::string input_file,
                          std::string var_name,
                          std::string output_binary_file) {
  std::cout << "Opening ADIOS2 file: " << input_file << "\n";
  std::vector<T> original_data;
  adios2::ADIOS adios;
  adios2::IO read_io = adios.DeclareIO("Input Data");
  read_io.SetEngine("BP5");
  adios2::Engine reader = read_io.Open(input_file, adios2::Mode::Read);
  reader.BeginStep();
  adios2::Variable<T> org_var = read_io.InquireVariable<T>(var_name);
  adios2::Dims shape = org_var.Shape();
  std::cout << "Reading variable " << var_name << " with shape ("; 
  size_t original_size = 1;
  for (int i = 0; i < shape.size(); i++) {
    original_size *= shape[i];
    std::cout << shape[i] << " ";
  }
  std::cout << ")\n";
  reader.Get<T>(org_var, original_data);
  original_data.resize(original_size);
  reader.EndStep();
  reader.Close();
  std::cout << "Converting to binary: " << output_binary_file << "\n";
  std::ofstream wf(output_binary_file, std::ios::out | std::ios::binary | std::ios::trunc);
  wf.write((char *) original_data.data(), sizeof(T) * original_data.size());
  wf.close();
  if(!wf.good()) {
    std::cout << "Error occurred at writing time!" << std::endl;
    return -1;
  }
  return 0;
}

int main(int argc, char **argv)
{
  if (argc < 5) {
    std::cout << "usage ./adios2binary <input adios2 file> <variable name> <single or double> <output binary file>\n";
    return -1;
  }
  std::string input_file(argv[1]);
  std::string var_name(argv[2]);
  std::string data_type(argv[3]);
  std::string output_binary_file(argv[4]);
  if (data_type == "single") {
    return convert_adios2_var<float>(input_file, var_name, output_binary_file);
  } else if (data_type == "double") {
    return convert_adios2_var<double>(input_file, var_name, output_binary_file);
  } else {
    std::cout << "wrong data type\n";
    return -1;
  }

}
