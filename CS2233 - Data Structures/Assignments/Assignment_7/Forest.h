class Forest {
public:
    class DisjointSet {
    public:
        DisjointSet *parent;
        int representative;
        int rank;
        DisjointSet(int value) {
            this->representative = value;
            this->parent = this;
            this->rank = 1;
        }
    };
    DisjointSet ** sets;
    int size;
    Forest(int n) {
        sets = new DisjointSet*[n+1];
        for(int i=1;i<n+1;i++)
            sets[i] = new DisjointSet(i);
        size = n;
    }
    ~Forest() {
        for(int i=1;i<size+1;i++)
            delete sets[i];
        delete[] sets;
    }

    int getRepresentative(int value) {
        if(value < 1 || value > size) return -1;
        DisjointSet *currentSetROOT = sets[value];
        while(currentSetROOT->parent != currentSetROOT) {
            currentSetROOT = currentSetROOT->parent;
        }
        return currentSetROOT->representative;
    }

    void unionSet( int a, int b) {

        if(a < 1 || b < 1 || a > size || b > size) return;
    
        DisjointSet *setA = sets[getRepresentative(a)];
        DisjointSet *setB = sets[getRepresentative(b)];
        DisjointSet *smaller, *larger;
        
        if(setA->rank >= setB->rank) {
            smaller = setB;
            larger = setA;
        }
        else {
            smaller = setA;
            larger = setB;
        }
        smaller -> parent = larger;
        if(smaller->rank + 1 > larger->rank) larger->rank = smaller -> rank + 1;
    }

};