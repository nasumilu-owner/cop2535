// Michael Lucas
// COP2535.DM1
// Build onto program 19-5 by adding a memeber function which takes a
// Person node and lists that node's cousins.
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
enum Gender { male, female };

// Person class represents a person participating in a genealogy
class Person
{
private:
    std::string name;
    Gender gender;
    std::vector<Person*> parents;
    std::vector<Person*> children;
    void addParent(Person* p) { parents.push_back(p); }
public:
    Person(std::string name, Gender g)
    {
        this->name = name;
        gender = g;
    }
    Person* addChild(std::string name, Gender g);
    Person* addChild(Person* p);

    // Member functions for getting various Person info
    std::string getName() const { return name; }
    Gender getGender() const { return gender; }
    int getNumChildren() const { return children.size(); }
    int getNumParents() const { return parents.size(); }
    bool hasParent(const Person*) const;
    bool hasChild(const Person*) const;
    Person* getChild(int k) const;
    Person* getParent(int k) const;
    // Static persons method for getting a list of cousins for a
    // Person
    static std::vector<Person*> getCousins(const Person*);
};

/**
 * Used to construct and delete test Person trees.
 */
class Project5
{
private:
    Person* lucas;
    Person* hoke;
    Person* masanate;
    Person* wynwright;
    Person* root;
public:
    Project5(){
        lucas = new Person{"Lucas", male}; // Lucas family root
        hoke = new Person{"Hoke", male}; // Hoke family root
        masanate = new Person{"Masanate", male}; // Masanate family root
        wynwright = new Person{"Wynwright", male}; //Waynwrite family root
        root = new Person{"Root", male}; // Another tree to represent step-childern
    }
    ~Project5(){
        delete lucas;
        delete hoke;
        delete masanate;
        delete wynwright;
        delete root;
    }
    void driver();
    void displayCousins(const Person* node);
};

//************************************************************
// Create a child with specified name and gender, and        *
// set one of the parents to be this person.                 *
// Add the new child to the list of children for this person *
//************************************************************
Person* Person::addChild(std::string name, Gender g)
{
    Person* child = new Person(name, g);
    child->addParent(this);   // I am a parent of this child
    children.push_back(child); // This is one of my children
    return child;
}

//************************************************************
// Add a child to the list of children for this person       *
//************************************************************
Person* Person::addChild(Person* child)
{
    child->addParent(this);  // I am a parent of this child
    children.push_back(child); // This is one of my children
    return child;
}


//*********************************************************
// Return a pointer to the specified parent               *
//*********************************************************
Person* Person::getParent(int k) const
{
    if (k < 0 || k >= parents.size())
    {
        std::cout << "Error indexing parents vector." << std::endl;
        exit(1);
    }
    return parents[k];
}

//**********************************************************
// Return a pointer to a specified child                   *
//**********************************************************
Person* Person::getChild(int k) const
{
    if (k < 0 || k >= children.size())
    {
        std::cout << "Error indexing children's vector." << std::endl;
        exit(1);
    }
    return children[k];
}

// Uses std::find
bool Person::hasParent(const Person* person) const
{
    return std::find(parents.begin(), parents.end(), person) != parents.end();
}

// Use std::find
bool Person::hasChild(const Person *person) const
{
    return std::find(children.begin(), children.end(), person) != children.end();
}

/**
 * Iterators up the the nodes parents, grandparents, to node's parent's siblings (aunts or uncle), and
 * finally iterates through the aunts or uncle nodes to display cousins.
 *
 * Up the tree to the right [or left] and down to equal level.
 */
std::vector<Person*> Person::getCousins(const Person *node)
{
    std::vector<Person*> cousins{};
    for(int k=0; k<node->getNumParents(); k++)
    {
        Person* kParent = node->getParent(k); // parent
        for(int l=0; l<kParent->getNumParents(); l++)
        {
            Person* lParent = kParent->getParent(l); // grandparent
            for(int m=0; m<lParent->getNumChildren(); m++)
            {
                Person* mChild = lParent->getChild(m); // aunt or uncle
                if(!mChild->hasChild(node)) // sibling
                {
                    for(int n=0; n<mChild->getNumChildren(); n++)
                    {
                        Person* nChild = mChild->getChild(n); // cousin
                        if(node != nChild)
                        {
                            cousins.push_back(nChild);
                        }
                     }
                }
           }
       }
    }
       return cousins;
}

void Project5::driver()
{
    // populate the family tree

    // Nancy family
    Person* nancy = lucas->addChild("Nancy", female);
    Person* richard = masanate->addChild("Richard", male);
    Person* emily = nancy->addChild("Emily", female);
    richard->addChild(emily);
    Person* kyle = nancy->addChild("Kyle", male);
    richard->addChild(kyle);


    //Susan family
    Person* susan = lucas->addChild("Susan", female);
    Person* billy = wynwright->addChild("William", male);
    Person* ann = susan->addChild("Ann", female);
    billy->addChild(ann);

    Person* liz = susan->addChild("Elizabeth", female);
    root->addChild(liz);
    root->addChild("Allen, Jr", male); //step-child shouldn't appear any where else


    //Michael family
    Person* michael = lucas->addChild("Michael", male);
    Person* mandy = hoke->addChild("Mandy", female);
    Person* kacey = michael->addChild("Kacey", male);
    Person* evan = michael->addChild("Evan", male);
    mandy->addChild(kacey);
    mandy->addChild(evan);

    Person* tasha = hoke->addChild("Tasha", female);
    tasha->addChild("Kenny", male);
    tasha->addChild("Colby", male);

    Person* misty = hoke->addChild("Misty", female);
    misty->addChild("Jake", male);
    Person* blake = misty->addChild("Blake", male);

    // display kacey's cousins
    displayCousins(kacey); // Emily, Kyle, Ann, Elizabeth, Kenny, Colby, Jake, Blake
    // display kyle's cousins
    displayCousins(kyle); // Ann, Elizabeth, Kacey, Evan
    // display Blake's cousins
    displayCousins(blake); // Kacey, Evan, Kenny, Colby
    // display Nancy's cousins
    displayCousins(nancy); // NONE
}

/**
 * Gets the list of cousin nodes and sends them to std::cout or indicates
 * no cousins where found.
 *
 * @param node
 */
void Project5::displayCousins(const Person *node)
{
    std::vector<Person*> cousins = Person::getCousins(node);
    if(cousins.size() != 0)
    {
        std::cout << node->getName() << "'s Cousins:" << std::endl;
        for(Person* p : cousins)
        {
            std::cout << "\t" << p->getName() << std::endl;
        }
    } else {
        std::cout << node->getName() << " doesn't have any cousins on record!" << std::endl;
    }
}

int main(int argc, char** argv)
{
    system("cls");
    Project5 proj{};
    proj.driver();
    system("pause");
    return 0;
}
