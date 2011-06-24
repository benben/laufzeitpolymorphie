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
}

Multiply::~Multiply()
{
}

void Multiply::process()
{
  cout << "process from Multiply()\n";
}

int main()
{
  cout << "hallo welt\n";
  Object * obj = new Object();
  //obj->process();
  Multiply * mult = new Multiply();
  //mult->process();
  vector <Object*> objects;
  objects.push_back(mult);
  objects.push_back(obj);

  for(int i = 0; i < objects.size(); i++)
  {
    objects[i]->process();
  }
}

