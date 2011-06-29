#include <iostream>
#include <vector>
#include <string.h>
#include "boost/variant.hpp"

typedef boost::variant<float, int> Type;

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
    vector<Type> input;
    vector<Type> output;
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
  output[0] = boost::get<float>(input[0]) * boost::get<float>(input[1]);
  cout << "output pin: " << output[0] << endl;
}

/******************/
/* Constant Class */
/******************/
class Constant : public Object
{
  public:
    Constant(float _var);
    ~Constant();
    void process();
};

Constant::Constant(float _var)
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
class Connection : public Object
{
  public:
    Connection(void * _in, void * _out, unsigned long _size);
    ~Connection();
    void * in;
    void * out;
    unsigned long size;
    void process();
};

Connection::Connection(void * _in, void * _out, unsigned long _size)
{
  in = _in;
  out = _out;
  size = _size;
}

Connection::~Connection()
{
}

void Connection::process()
{
  cout << "process from Connection()\n";
  memcpy(out, in, size);
}

/******************/
/* Main           */
/******************/
int main()
{
  //Create Objects
  Constant * const1 = new Constant(5.5);
  Constant * const2 = new Constant(3.2);
  Multiply * mult = new Multiply();
  
  //Create Connections between Objects
  Connection * const1_to_mult = new Connection(&const1->output[0], &mult->input[0], sizeof(const1->output[0]));
  Connection * const2_to_mult = new Connection(&const2->output[0], &mult->input[1], sizeof(const2->output[0]));
  
  //Save all Objects in a vector
  // http://www.boost.org/doc/libs/1_46_1/libs/ptr_container/doc/tutorial.html
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

