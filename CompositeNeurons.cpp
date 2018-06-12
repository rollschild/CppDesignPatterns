#include <iostream>
#include <vector>
using namespace std;

struct Neuron;

template<typename Self>
struct AllSortsOfNeurons
{
  template<typename T>
  void ConnectTo(T& other);
};

struct Neuron : AllSortsOfNeurons<Neuron>
{
  vector<Neuron*> incoming_;
  vector<Neuron*> outcoming_;
  unsigned int id_;
  Neuron() {
    static int id_ = 1;
    this->id_ = id_++;
  }

  Neuron* begin() {
    return this;
  }

  Neuron* end() {
    return this + 1;
  }

  friend ostream& operator<<(ostream& os, const Neuron& neuron) {
    for(Neuron* incoming_node : neuron.incoming_) {
      os << "[" << neuron.id_ << "]\t<--\t" << incoming_node->id_ << endl;
    }
    for(Neuron* outcoming_node : neuron.outcoming_) {
      os << "[" << neuron.id_ << "]\t-->\t" << outcoming_node->id_ << endl;
    }

    return os;
  }
};

template<typename Self>
template<typename T>
inline void AllSortsOfNeurons<Self>::ConnectTo(T& other) {
  for(Neuron& origin : *static_cast<Self*>(this)) {
    for(Neuron& destination : other) {
      origin.outcoming_.push_back(&destination);
      destination.incoming_.push_back(&origin);
    }
  }
}

struct NeuronLayer : vector<Neuron>, AllSortsOfNeurons<NeuronLayer>
{
  NeuronLayer(int number_of_neurons) {
    while(number_of_neurons-- > 0) {
      emplace_back(Neuron{});
    }
  }

  friend ostream& operator<<(ostream& os, const NeuronLayer& neuron_layer) {
    for(auto& neuron_node : neuron_layer) {
      os << neuron_node;
    }

    return os;
  }
};

int main() {
  Neuron node_1;
  Neuron node_2;
  Neuron node_3;

  node_1.ConnectTo(node_2);
  node_1.ConnectTo(node_3);
  node_2.ConnectTo(node_3);

  cout << node_1;
  cout << node_2;
  cout << node_3;


  cout << "Layer: \n";
  NeuronLayer layer_1(6);
  layer_1.ConnectTo(node_1);
  cout << layer_1;
  
  cout << "node_1 again: \n";
  node_1.ConnectTo(layer_1);
  cout << node_1;
  return 0;
}
