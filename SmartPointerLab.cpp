#include <iostream>
#include <exception>
using namespace std;

template <typename T>
class SmartPointer
{
private:
    T* smptr = NULL;
public:
    SmartPointer(T* smptr)
    {
        this->smptr = smptr;
    }

    ~SmartPointer()
    {
        delete smptr;
    }

    SmartPointer(SmartPointer& orig)
    {
        smptr = orig.smptr;
        orig.smptr = NULL;
    }

    SmartPointer& operator= (SmartPointer& orig)
    {
        if (this != &orig)
        {
            delete smptr;
            smptr = orig.smptr;
            orig.smptr = NULL;
        }
        return *this;
    }

    T* operator->() const
    {
        if (smptr != NULL)
        {
            return smptr;
        }
        throw out_of_range("its null ptr!");
    }

    T& operator*() const
    {
        if (smptr != NULL)
        {
            return *smptr;
        }
    }
};

class Check
{
public:
    int f;
    void Testing()
    {
        cout << "checked" << endl;
    }
    ~Check() {};
};

int main()
{
    SmartPointer<Check> smptr1(new Check());

    SmartPointer<Check> smptr2(new Check());
    try
    {
        smptr1 = smptr2;
        smptr2->Testing();
        smptr2->f = 1;
    }
    catch (exception& excep)
    {
        cout << excep.what();
    }

    return 0;
}
