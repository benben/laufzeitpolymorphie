#include <iostream>
#include <vector>

using namespace std;

class Object
{
	public:
    Object(const Object&); //Kopieren verhindern
	  Object& operator=(const Object&);

    Object();
    virtual ~Object();
	  vector<int> input;
	  vector<int> output;
	  virtual void process();
};

Object::Object()
{
}

Object::~Object()
{
}

void Object::process()
{
  cout << "process from Object()\n";
}

class Multiply : public Object
{
  public:
    Multiply();
    ~Multiply();
    void process();
};

Multiply::Multiply()
{
  input.push_back(0);
  input.push_back(0);
  output.push_back(0);
}

Multiply::~Multiply()
{
}

void Multiply::process()
{
  cout << "process from Multiply()\n";
  
  output[0] = input[0] * input[1];
  cout << "output pin: " << output[0] << endl;
}

class Constant : public Object
{
  public:
    Constant(int _var);
    ~Constant();
    void process();
    int var;
};

Constant::Constant(int _var)
{
  var = _var;
}

Constant::~Constant()
{
}

void Constant::process()
{
  output.push_back(var);
  cout << "process from Constant()\n";
  cout << "output pin: " << output[0] << endl;
}

template <class fromT, class fromPinT, class toT, class toPinT>
class Connection : public Object
{
  public:
    Connection(fromT * & _from, fromPinT _fromPin, toT * & _to, toPinT _toPin);
    ~Connection();
    fromPinT fromPin;
    toPinT toPin;
    fromT * from;
    toT * to;
    void process();
};

template <class fromT, class fromPinT, class toT, class toPinT>
Connection<fromT, fromPinT, toT, toPinT>::Connection(fromT * & _from, fromPinT _fromPin, toT * & _to, toPinT _toPin)
{
  from = _from;
  to = _to;
  fromPin = _fromPin;
  toPin = _toPin;
}

template <class fromT, class fromPinT, class toT, class toPinT>
Connection<fromT, fromPinT, toT, toPinT>::~Connection()
{
}

template <class fromT, class fromPinT, class toT, class toPinT>
void Connection<fromT, fromPinT, toT, toPinT>::process()
{
  cout << "process from Connection()\n";
  cout << from->output[fromPin] << endl;
  to->input[toPin] = from->output[fromPin];
  cout << to->input[toPin] << endl;
}

int main()
{
  cout << "hallo welt\n";
  Constant * const1 = new Constant(5);
  Constant * const2 = new Constant(3);
  Multiply * mult = new Multiply();

  Connection<Constant, int, Multiply, int> * const1_to_mult = new Connection<Constant, int, Multiply, int>(const1, 0, mult, 0);
  Connection<Constant, int, Multiply, int> * const2_to_mult = new Connection<Constant, int, Multiply, int>(const2, 0, mult, 1);

  vector <Object*> objects;
  objects.push_back(const1);
  objects.push_back(const2);
  objects.push_back(const1_to_mult);
  objects.push_back(const2_to_mult);
  objects.push_back(mult);

  for(unsigned int i = 0; i < objects.size(); i++)
  {
    objects[i]->process();
  }
}

