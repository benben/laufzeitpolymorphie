#include <iostream>
#include <vector>

using namespace std;


/******************/
/* Base Class     */
/******************/
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

/******************/
/* Multiply Class */
/******************/
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

/******************/
/* Constant Class */
/******************/
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

/********************/
/* Connection Class */
/********************/
template <class fromT, class toT>
class Connection : public Object
{
  public:
    Connection(fromT * & _from, int _fromPin, toT * & _to, int _toPin);
    ~Connection();
    int fromPin;
    int toPin;
    fromT * from;
    toT * to;
    void process();
};

template <class fromT, class toT>
Connection<fromT, toT>::Connection(fromT * & _from, int _fromPin, toT * & _to, int _toPin)
{
  from = _from;
  to = _to;
  fromPin = _fromPin;
  toPin = _toPin;
}

template <class fromT, class toT>
Connection<fromT, toT>::~Connection()
{
}

template <class fromT, class toT>
void Connection<fromT, toT>::process()
{
  cout << "process from Connection()\n";
  to->input[toPin] = from->output[fromPin];
}

/******************/
/* Main           */
/******************/
int main()
{
  //Create Objects
  Constant * const1 = new Constant(5);
  Constant * const2 = new Constant(3);
  Multiply * mult = new Multiply();

  //Create Connections between Objects
  Connection<Constant, Multiply> * const1_to_mult = new Connection<Constant, Multiply>(const1, 0, mult, 0);
  Connection<Constant, Multiply> * const2_to_mult = new Connection<Constant, Multiply>(const2, 0, mult, 1);
  
  //Save all Objects in a vector
  vector <Object*> objects;
  objects.push_back(const1);
  objects.push_back(const2);
  objects.push_back(const1_to_mult);
  objects.push_back(const2_to_mult);
  objects.push_back(mult);

  //Run the process() method of all Objects
  for(unsigned int i = 0; i < objects.size(); i++)
  {
    objects[i]->process();
  }
}

