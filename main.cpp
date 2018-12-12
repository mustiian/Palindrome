#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

const int MAX_POSITION = 500;

class TTon{
public:
    TTon ( int pos ) : m_Position( pos )
    { }
    void InsertNeighbour (int neighbour, char ton){
        m_Neighbours.insert( {neighbour, ton} );
    }
    char GetNeighbourTon( int neighbour ){
        return m_Neighbours.at(neighbour);
    }

private:
    int m_Position;
    map<int, char> m_Neighbours;
};

class CKoledy{
public:
    CKoledy( int size, int start, int end ):
                m_Start(start), m_End(end)
    {
        for (int i = 0; i < size; ++i) {
            m_Song.emplace_back( TTon(i) );
        }
    }
    void InsertNeighbour( int position, int neighbour, char ton );
private:
    vector<TTon> m_Song;
    map<int, set<string>> m_Words;
    int m_Start;
    int m_End;
};

void CKoledy::InsertNeighbour(int position, int neighbour, char ton) {
    m_Song[position].InsertNeighbour(neighbour, ton);
}

int main(){
    int size, ignoreTon, size_of_neighbours;
    int start, end;

    cin >> size >> ignoreTon;
    cin >> start >> end;

    CKoledy koledy(size, start, end);

    for (int pos = 0; pos < size; ++pos) {
        cin >> size_of_neighbours;

        for (int j = 0; j < size_of_neighbours; ++j) {
            int neighbour; char ton;

            cin >> neighbour >> ton;
            koledy.InsertNeighbour(pos, neighbour, ton);
        }
    }

    return 0;
}