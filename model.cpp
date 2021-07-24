#include "activations.hpp"
#include "conv2d.hpp"
#include "linear.hpp"
#include "loader.hpp"
#include <iostream>
#include <map>

class Model {
  Conv2d conv1, conv2;
  Linear fc1, fc2;

public:
  Model() {
    conv1 = Conv2d("conv1", 1, 32, 3);
    conv2 = Conv2d("conv2", 32, 64, 3);

    fc1 = Linear("fc1", 9216, 128);
    fc2 = Linear("fc2", 128, 10);
  }

  matrix1 operator()(matrix3 const &in) {
    matrix3 x = conv1(in);
    x = ReLU(x);
    x = conv2(x);

    x = ReLU(x);
    x = max_pool2d(x, 2);

    // linear
    matrix1 xx = x.flatten();
    matrix xxx = xx.unsqueeze(0);

    xxx = fc1(xxx);
    xxx = fc2(xxx);

    return xxx.flatten();
  }

  void load() {
    auto data = read_zip_file("mnist_cnn.pt");

    for (nn_parameters &d : data) {
      if (d.name.find("conv1") != std::string::npos) {
        matrix4 w;
        w.mat = d.weight_param;
        w.size(32, 1, 3, 3);
        if (d.weight_size != w.size()) {
          std::cerr << "conv1 size not match:" << w.size()
                    << "!=" << d.weight_size << "\n";
        }

        matrix1 b;
        b.mat = d.bias_param;
        b.m = d.bias_size;

        conv1 = Conv2d("conv1", w, b);
      }
      if (d.name.find("conv2") != std::string::npos) {
        matrix4 w;
        w.mat = d.weight_param;
        w.size(64, 32, 3, 3);
        if (d.weight_size != w.size()) {
          std::cerr << "conv2 size not match:" << w.size()
                    << "!=" << d.weight_size << "\n";
        }

        matrix1 b;
        b.mat = d.bias_param;
        b.m = d.bias_size;

        conv2 = Conv2d("conv2", w, b);
      }
      if (d.name.find("fc1") != std::string::npos) {
        matrix w;
        w.mat = d.weight_param;
        w.size(9216, 128);
        if (d.weight_size != w.size()) {
          std::cerr << "fc1 size not match:" << w.size()
                    << "!=" << d.weight_size << "\n";
        }

        matrix1 b;
        b.mat = d.bias_param;
        b.m = d.bias_size;

        fc1 = Linear("fc1", w, b);
      }
      if (d.name.find("fc2") != std::string::npos) {
        matrix w;
        w.mat = d.weight_param;
        w.size(128, 10);
        if (d.weight_size != w.size()) {
          std::cerr << "fc2 size not match:" << w.size()
                    << "!=" << d.weight_size << "\n";
        }

        matrix1 b;
        b.mat = d.bias_param;
        b.m = d.bias_size;

        fc2 = Linear("fc2", w, b);
      }
    }
  }
};

int main() {
  Model m;
  m.load();

  std::cout << "hello world\n";
  return 0;
}