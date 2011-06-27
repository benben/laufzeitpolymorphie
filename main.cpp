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
    //vector<void*> ?????? / http://www.boost.org/doc/libs/1_46_1/doc/html/any/s02.html
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
};

Constant::Constant(int _var)
{
  output.push_back(_var);
}

Constant::~Constant()
{
}

void Constant::process()
{
  cout << "process from Constant()\n";
  cout << "output pin: " << output[0] << endl;
}

/********************/
/* Connection Class */
/********************/
template <class T>
class Connection : public Object
{
  public:
    Connection(T * _in, T * _out);
    ~Connection();
    T * in;
    T * out;
    void process();
};

template <class T>
Connection<T>::Connection(T * _in, T * _out)
{
  in = _in;
  out = _out;
}

template <class T>
Connection<T>::~Connection()
{
}

template <class T>
void Connection<T>::process()
{
  cout << "process from Connection()\n";
  *out = *in;
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
  Connection<int> * const1_to_mult = new Connection<int>(&const1->output[0], &mult->input[0]);
  Connection<int> * const2_to_mult = new Connection<int>(&const2->output[0], &mult->input[1]);
  
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

